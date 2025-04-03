#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>


using namespace std;

vector<string> strings;

class Vertex {
    public:
    vector<int> idxs;
    int CLB;
    
    Vertex(vector<int>& idxs, int path_len) : idxs(idxs) {
        CLB = path_len + calc_MS();
    }

    int calc_MS() {
        int MS = strings[0].size()-idxs[0];
        for (int i = 1; i < idxs.size(); i++) {
            MS = max(MS, static_cast<int>(strings[i].size()-idxs[i]));
        }
        return MS;
    }

    bool operator==(const Vertex& other) const {
        return idxs == other.idxs;
    }

    bool operator<(const Vertex& other) const {
        if (CLB != other.CLB) {
            return CLB < other.CLB;
        }
        return idxs < other.idxs;
    }

    bool at_end() const {
        for (int i = 0; i < idxs.size(); i++) {
            if (idxs[i] < strings[i].size()) {
                return false;
            }
        }
        return true;
    }

    int& operator[](int i) {
        return idxs[i];
    } 

    void icrease_char_idx(char c, vector<string>& strings) {
        int prev_MS = calc_MS();
        for (int i = 0; i < idxs.size(); i++) {
            if (idxs[i] < strings[i].size() && strings[i][idxs[i]] == c) {
                idxs[i]++;
            }
        }
        int MS = calc_MS();
        CLB = 1 + MS - prev_MS;
    }
};

struct Hash {
    size_t operator()(const Vertex& v) const {
        size_t seed = v.idxs.size();
        for (int num : v.idxs) {
            seed ^= hash<int>()(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

// Dijakstra:
string scs(vector<string>& strings){
    set<Vertex> wave;
    unordered_map<Vertex, Vertex, Hash> visited;
    int k = strings.size();

    Vertex v(vector<int>(k, 0), 0);
    visited[v] = Vertex(vector<int>(k, -1), 0); // Value is from where we came to this point
    Vertex prev = v;
    while(!v.at_end())
    {
        unordered_set<char> visited_chars;
        for (int i = 0; i < k; i++) {
            char c = strings[i][v[i]];
            if (visited_chars.find(c) == visited_chars.end()) {
                visited_chars.insert(c);
                Vertex v1 = v;
                v1.icrease_char_idx(c, strings);
                if (visited.find(v1) == visited.end()) {
                    wave.insert(v1);
                    visited[v1] = v;
                }
            }
        }
        v = *wave.begin();
        wave.erase(wave.begin());
        visited[v] = prev; 
    }

    string res = "";
    while (visited[v][0] != -1)
    {
        Vertex prev_v = visited[v];
        for(int i = 0; i < k; i++){
            if(prev_v[i] == v[i] - 1){
                res = strings[i][v[i]-1] + res;
                break;
            }
        }
        v = prev_v;
    }
    return res;
}

int main(){
    vector<string> strings = {"AB", "BB", "BA"};
    string res = scs(strings);
    cout << res << endl;
    // test();
    return 0;
}