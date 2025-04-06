#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <vector>

using namespace std;


struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t seed = v.size();
        for (int num : v) {
            seed ^= hash<int>()(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

void increase_idxs_by_one(vector<int>& p, vector<string>& strings){
    for (int i = 0; i < p.size(); i++)
    {
        p[i]++;
    }
}

void increase_idxs_of_same_char(vector<int>& p, vector<string>& strings, char c){
    for (int i = 0; i < p.size(); i++)
    {
        if(p[i] < strings[i].size() && strings[i][p[i]] == c){
            p[i]++;
        }
    }
}

bool all_same_char(vector<int>& p, vector<string>& strings){
    char c = strings[0][p[0]];
    for (int i = 1; i < p.size(); i++)
    {
        if(p[i] >= strings[i].size() || strings[i][p[i]] != c){
            return false;
        }
    }
    return true;
}

string scs(vector<string>& strings){
    queue<vector<int>> q;
    unordered_map<vector<int>, vector<int>, VectorHash> visited;
    
    int k = strings.size();
    const int n = strings[0].size();
    vector<int> p(k, 0);
    visited[p] = vector<int>(k, -1); // Value is from where we came to this point

    while(*min_element(p.begin(), p.end()) < n){
        while(*max_element(p.begin(), p.end()) < n &&
                all_same_char(p, strings))
        {
            vector<int> p1 = p;
            increase_idxs_by_one(p1, strings);
            
            if(visited.find(p1) == visited.end()){
                
                visited[p1] = p;
                p = p1;
            }
            else{
                break;
            }
        }

        if (*min_element(p.begin(), p.end()) >= n)
        {
            break;
        }

        unordered_map<char, bool> visited_chars;
        for (int i = 0; i < k; i++)
        {
            char c = strings[i][p[i]];
            if(visited_chars.find(c) == visited_chars.end()){
                visited_chars[c] = true;
                vector<int> p1 = p;
                increase_idxs_of_same_char(p1, strings, c);
                if(visited.find(p1) == visited.end()){
                    visited[p1] = p;
                    q.push(p1);
                }
            }
        }
        p = q.front();
        q.pop();
    }

    string s;
    while(*max_element(p.begin(), p.end()) > 0){
        vector<int> prev_p = visited[p];
        for(int i = 0; i < k; i++){
            if(prev_p[i] == p[i] - 1){
                s = strings[i][p[i]-1] + s;
                break;
            }
        }
        p = prev_p;
    }
    return s;
}


int main(){

    vector<string> strings = {"AB", "BB", "BA"};
    string res = scs(strings);
    std::cout << "input = {\"AB\", \"BB\", \"BA\"} , output:" << res << endl;
    // Input = {"AB", "BB", "BA"}
    // Output = ABBA

    strings = {"BB", "AB", "BA"};
    res = scs(strings);
    std::cout << "input = {\"BB\", \"AB\", \"BA\"} , output:" << res << endl;
    // Input = {"BB", "AB", "BA"}
    // Output: BAB

    strings = {"AB", "BA", "BB"};
    res = scs(strings);
    std::cout << "input = {\"AB\", \"BA\", \"BB\"} , output:" << res << endl;
    // Input: {"AB", "BA", "BB"}
    // Output: ABAB

    // Expected output: BAB

    return 0;
}