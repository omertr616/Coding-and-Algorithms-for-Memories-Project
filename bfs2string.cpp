// #include <iostream>
// #include <string>
// #include <queue>
// #include <unordered_set>

// using namespace std;

// class path{
//     public:
//         string s;
//         int i1;
//         int i2;
//         path(string s, int i1, int i2): s(s), i1(i1), i2(i2){}
// };

// struct PairHash {
//     size_t operator()(const pair<int, int>& p) const {
//         return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
//     }
// };

// string scs(string& str1, string& str2){
//     queue<path> q;
//     unordered_set<pair<int, int>, PairHash> visited;

//     path p = path("", 0, 0);
//     visited.insert({0, 0});
//     while(p.i1 < str1.size() || p.i2 < str2.size()){
//         while(p.i1 < str1.size()
//             && p.i2 < str2.size()
//             && str1[p.i1] == str2[p.i2]
//             && visited.find({p.i1+1, p.i2+1}) == visited.end())
//         {
//             p.s += str1[p.i1];
//             p.i1++;
//             p.i2++;
//             visited.insert({p.i1, p.i2});
//         }

//         if (p.i1 == str1.size() && p.i2 == str2.size())
//         {
//             break;
//         }

//         if (p.i1 < str1.size()){
//             path p1 = p;
//             p1.s += str1[p1.i1];
//             p1.i1++;
//             if (visited.find({p1.i1, p1.i2}) == visited.end())
//             {
//                 q.push(p1);
//                 visited.insert({p1.i1, p1.i2});
//             }
//         }
//         if (p.i2 < str2.size()){
//             path p2 = p;
//             p2.s += str2[p2.i2];
//             p2.i2++;
//             if (visited.find({p2.i1, p2.i2}) == visited.end())
//             {
//                 q.push(p2);
//                 visited.insert({p2.i1, p2.i2});
//             }
//         }
        
//         p = q.front();
//         q.pop();
//     }
//     return p.s;
// }

// int main(){
//     string str1 = "abac", str2 = "cab";
//     string res = scs(str1, str2);
//     cout << res << endl;
//     return 0;
// }


// #include <iostream>
// #include <string>
// #include <queue>
// #include <unordered_set>

// using namespace std;

// class path{
//     public:
//         path* prev;
//         char c;
//         int i1;
//         int i2;
//         path(path* prev, char c, int i1, int i2): prev(prev), c(c), i1(i1), i2(i2){}
// };

// struct PairHash {
//     size_t operator()(const pair<int, int>& p) const {
//         return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
//     }
// };

// string scs(string& str1, string& str2){
//     queue<path*> q;
//     unordered_set<pair<int, int>, PairHash> visited;

//     path *p = new path(nullptr,'\0', 0, 0);
//     visited.insert({0, 0});
//     while(p->i1 < str1.size() || p->i2 < str2.size()){
//         while(p->i1 < str1.size()
//             && p->i2 < str2.size()
//             && str1[p->i1] == str2[p->i2]
//             && visited.find({p->i1+1, p->i2+1}) == visited.end())
//         {
//             p = new path(p, str1[p->i1], p->i1+1, p->i2+1);
//             visited.insert({p->i1, p->i2});
//         }

//         if (p->i1 == str1.size() && p->i2 == str2.size())
//         {
//             break;
//         }

//         if (p->i1 < str1.size()){
//             path* p1 = new path(p, str1[p->i1], p->i1+1, p->i2);
//             if (visited.find({p1->i1, p1->i2}) == visited.end())
//             {
//                 q.push(p1);
//                 visited.insert({p1->i1, p1->i2});
//             }
//         }
//         if (p->i2 < str2.size()){
//             path* p2 = new path(p, str2[p->i2], p->i1, p->i2+1);
//             if (visited.find({p2->i1, p2->i2}) == visited.end())
//             {
//                 q.push(p2);
//                 visited.insert({p2->i1, p2->i2});
//             }
//         }
        
//         p = q.front();
//         q.pop();
//     }
//     string res = "";
//     while(p->prev != nullptr){
//         res = p->c + res;
//         p = p->prev;
//     }

//     return res;
// }

// int main(){
//     string str1 = "bbbaaaba", str2 = "bbababbb";
//     string res = scs(str1, str2);
//     cout << res << endl;
//     return 0;
// }


#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>


using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        // return hash<int>()(p.first) ^ (hash<int>()(p.second) << 16);
        return static_cast<size_t>(p.first) | (static_cast<size_t>(p.second) << (sizeof(int)));
    }
};

typedef pair<int, int> pii;

string scs(string& str1, string& str2){
    queue<pii> q;
    unordered_map<pii, pii, PairHash> visited;

    pii p = {0, 0};
    visited[p] = {-1, -1}; // value is from where we came to this point
    while(p.first < str1.size() || p.second < str2.size()){
        while(p.first < str1.size()
            && p.second < str2.size()
            && str1[p.first] == str2[p.second]
            && visited.find({p.first+1, p.second+1}) == visited.end())
        {
            visited[{p.first+1, p.second+1}] = p;
            p.first++;
            p.second++;
        }

        if (p.first == str1.size() && p.second == str2.size())
        {
            break;
        }

        if (p.first < str1.size() && visited.find({p.first+1, p.second}) == visited.end()){
            visited[{p.first+1, p.second}] = p;
            q.push({p.first+1, p.second});
        }
        if(p.second < str2.size() && visited.find({p.first, p.second+1}) == visited.end()){
            visited[{p.first, p.second+1}] = p;
            q.push({p.first, p.second+1});
        }
        p = q.front();
        q.pop();
    }

    string s;
    while(p.first != 0 || p.second != 0){
        pii prev_p = visited[p];
        if(prev_p.first == p.first - 1 && prev_p.second == p.second - 1){
            s = str1[p.first-1] + s;
        }
        else if(prev_p.first == p.first - 1){
            s = str1[p.first-1] + s;
        }
        else{
            s = str2[p.second-1] + s;
        }
        p = prev_p;
    }
    return s;
}

int main(){
    string str1 = "abc", str2 = "cabc";
    string res = scs(str1, str2);
    cout << res << endl;
    return 0;
}
