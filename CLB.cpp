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

    
    Vertex(vector<int>& idxs, int path_len) : idxs(idxs) {
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

string scs(vector<string>& strings){
    unordered_map<Vertex, Vertex, Hash> visited;
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
        // while(!_dist0->empty() && visited.find(_dist0->front()) != visited.end()){
        //     _dist0->pop();
        // }
        // if (_dist0->empty())
        // {
        //     swap(_dist0, _dist1);
        // }
        v = _dist0->front();
        _dist0->pop();
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












#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <iostream>



// Function to generate a random string of length 'n'
string generateRandomString(int n) {
    const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, charset.size() - 1);

    string result;
    for (int i = 0; i < n; ++i) {
        result += charset[distribution(generator)];
    }
    return result;
}

// Function to delete 't' random characters from the string
string deleteRandomChars(const string &s, int t) {
    if (t >= s.size()) {
        return ""; // If t is greater or equal to the string length, return empty string
    }

    random_device rd;
    mt19937 generator(rd());
    vector<int> indices(s.size());
    for (int i = 0; i < s.size(); ++i) {
        indices[i] = i;
    }

    // Shuffle the indices to select t random positions
    shuffle(indices.begin(), indices.end(), generator);

    // Sort the first t indices to delete them in order
    sort(indices.begin(), indices.begin() + t);

    string result = s;
    // Delete characters from the highest index to avoid shifting issues
    for (int i = t - 1; i >= 0; --i) {
        result.erase(indices[i], 1);
    }
    return result;
}

int test() {
    
    int tests = 100;
    for(int i = 0; i < tests; i++){
        int n = rand() % 2000000 + 2;
        int t = rand() % 10 + 1;
        int k = rand() % 5 + 1;

        cout << "Test " << i+1 << ": n = " << n << ", t = " << t << ", k = " << k << endl;  
        string original = generateRandomString(n);
        strings = vector<string>(k);
        for(int j = 0; j < k; j++){
            strings[j] = deleteRandomChars(original, t);
        }
        string res = scs(strings);
        cout << "SCS length: " << res.length() << endl;
        if (res.length() <= n)
        {
            cout << "Test passed" << endl;
        }
        else{
            cout << "Test failed" << endl;
            cout << "SCS length is greater than n" << endl;
            cout << "Original string: " << original << endl;
            cout << "SCS: " << res << endl;
            cout << "Strings: " << endl;
            for(int j = 0; j < k; j++){
                cout << strings[j] << endl;
            }
            return 0;
        }
    }
    cout << "All tests passed" << endl;
    return 0;
}





int main(){
    // strings = {"01234789", "2345678", "0345689"};
    // string res = scs(strings);
    // cout << res << endl;
    
    // USROAEWKXJHXQDXBWK
    // strings = {"USOXJXQDK",
    //             "SOAEXJHXW",
    //             "SOWKJXQDK",
    //             "AWJHDXBWK",
    //             "SRAKJXXBW",
    //             "SAEXHQXBW"};

    // string res = scs(strings);
    // cout << res << endl;


    /*
    Original string: QLISLM
    SCS: QSLILMS
    QLL
    SLM
    QIS
    QLI
    */
    // strings = {"QLL", "SLM", "QIS", "QLI"};
    // string res = scs(strings);
    // cout << res << endl;

    /*
    Original string: ELILQ
    SCS: EILIQL
    Strings:
    ELI
    EIL
    ILQ
    ELL
    ELQ
    */

    test();
    return 0;
}