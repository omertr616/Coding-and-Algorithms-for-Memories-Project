#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>


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

// int main(){
//     vector<string> strings = {"1236789","0234567","0126789",};
//     string res = scs(strings);
//     cout << res << endl;
//     return 0;
// }


#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

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
        int n = rand() % 20 + 2;
        int t = rand() % (n/2) + 1;
        int k = rand() % 10 + 1;
        cout << "Test " << i+1 << ": n = " << n << ", t = " << t << ", k = " << k << endl;  
        string original = generateRandomString(n);
        vector<string> strings(k);
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
    // CVC
    vector<string> strings = {"VC",
                                "CC",
                                "CC",
                                "CV",
                                "CV",
                                "VC",
                                "CC",
                                "VC",
                                "CV"
                            };
    strings = {"AB", "BB", "BA"};
    string res = scs(strings);
    cout << res << endl;
    // test();
    return 0;
}