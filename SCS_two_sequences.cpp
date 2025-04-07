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
