#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>


using namespace std;

vector<string> strings = {"BB", "AB", "BA"};

class Vertex {
    public:
    vector<int> idxs;
    int CLB;

    int calc_MS() {
        int MS = strings[0].size()-idxs[0];
        for (int i = 1; i < idxs.size(); i++) {
            MS = max(MS, static_cast<int>(strings[i].size()-idxs[i]));
        }
        return MS;
    }

    
    Vertex(const vector<int>& idxs, int path_len) : idxs(idxs) {  
        CLB = path_len + calc_MS();
    }

    Vertex() : idxs(), CLB() {}

    bool operator==(const Vertex& other) const {
        return idxs == other.idxs;
    }

    bool operator<(const Vertex& other) const {
        if (CLB != other.CLB) {
            return CLB < other.CLB;
        }
        return idxs < other.idxs;
    }

    // Check if all indices are at the end of their respective strings
    // This function is used to check if we have reached the end of all strings
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

    /// Function to increase the index of the character 'c' in the strings
    /// This function is called when we progress to the next vertex in the graph
    void icrease_char_idx(char c) {
        int prev_MS = calc_MS();
        for (int i = 0; i < idxs.size(); i++) {
            if (idxs[i] < strings[i].size() && strings[i][idxs[i]] == c) {
                idxs[i]++;
            }
        }
        int MS = calc_MS();
        CLB += 1 + MS - prev_MS;
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

/// Function to find the shortest common supersequence (SCS) of multiple strings
string scs(vector<string> _strings){
    strings = _strings;

    // visited is used to store the vertices which are already visited in the BFS.
    // The key is the vertex and the value is the vertex from where we came to this point.
    unordered_map<Vertex, Vertex, Hash> visited;

    // dist0 and dist1 are used to store the vertices in the graph
    // dist0 is used for vertices which are in the same layer in the BFS.
    // dist1 is used for vertices which are in the next layer in the BFS.
    queue<Vertex> dist0;
    queue<Vertex> dist1;

    int k = strings.size();

    Vertex v(vector<int>(k, 0), 0);
    visited[v] = Vertex(vector<int>(k, -1), -1); // value is from where we came to this point
    queue<Vertex> *_dist0 = &dist0;
    queue<Vertex> *_dist1 = &dist1;
    while (!v.at_end())
    {
        // Adding every char to the current vertex
        unordered_set<char> visited_chars;
        for (int i = 0; i < k; i++)
        {   
            if (v[i] >= strings[i].size()) continue;
            char c = strings[i][v[i]];

            if(visited_chars.find(c) == visited_chars.end())
            {
                visited_chars.insert(c);

                Vertex v1 = v;
                v1.icrease_char_idx(c);
                if(visited.find(v1) == visited.end())
                {
                    visited[v1] = v;
                    if (v1.CLB - v.CLB == 1)
                    {
                        _dist1->push(v1);
                    }
                    else // CLB - prev CLB = 0
                    {
                        _dist0->push(v1);
                    }
                
                }
                else if (v1.CLB - v.CLB == 0 && visited[v1].CLB >= v.CLB)
                {
                    _dist0->push(v1);
                    visited[v1] = v;
                }
            }
        }
    
        if (_dist0->empty())
        {
            swap(_dist0, _dist1);
        }

        v = _dist0->front();
        _dist0->pop();
    }

    // Recontructing the SCS from the visited map
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