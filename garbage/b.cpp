#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>


using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

typedef pair<int, int> pii;

string scs(string& str1, string& str2){
    queue<pii> q;
    unordered_map<pii, pii, PairHash> prev;

    pii p = {0, 0};
    prev[p] = {-1, -1};
    while(p.first < str1.size() || p.second < str2.size()){
        while(p.first < str1.size()
            && p.second < str2.size()
            && str1[p.first] == str2[p.second]
            && prev.find({p.first+1, p.second+1}) == prev.end())
        {
            prev[{p.first+1, p.second+1}] = p;
            p.first++;
            p.second++;
        }

        if (p.first == str1.size() && p.second == str2.size())
        {
            break;
        }

        if (p.first < str1.size() && prev.find({p.first+1, p.second}) == prev.end()){
            prev[{p.first+1, p.second}] = p;
            q.push({p.first+1, p.second});
        }
        if(p.second < str2.size() && prev.find({p.first, p.second+1}) == prev.end()){
            prev[{p.first, p.second+1}] = p;
            q.push({p.first, p.second+1});
        }
        p = q.front();
        q.pop();
    }

    string s;
    while(p.first != -1){
        pii prev_p = prev[p];
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
    string str1 = "abac", str2 = "cab";
    string res = scs(str1, str2);
    cout << res << endl;
    return 0;
}
