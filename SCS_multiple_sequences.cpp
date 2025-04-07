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

string scs(vector<string> _strings){
    strings = _strings;
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

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>


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


bool is_supersequence(string s1, string s2){   // checks if s1 superseq of s2
    int i=0;
    int j=0;
    
    while (i < s1.length() && j < s2.length()){
        if(s1[i]==s2[j])
        	    j++;
        i++;
    }

    return j == s2.length();
}


void run_test(string orig_str, vector<string> strings, int t, int exp_len){
    cout << "Original string: " << orig_str << " , t=" << t << " , k=" << strings.size() << endl;
    cout << "k sequences: " << endl ;
    for (int i=0; i<strings.size(); i++){
        cout << strings[i] << " " << endl ;
    }
    string res = scs(strings);
    cout << "Expected SCS length: " << exp_len << endl;
    cout << "Output SCS: " << res << endl;

    // check length
    if(res.length() != exp_len){
        cout << "Test failed" << endl ;
        return;
    }

    // check if all k strings are in res 
    for (int i=0; i<strings.size(); i++){
        if(! is_supersequence(res, strings[i])){
            cout << "Test failed" << endl ;
            return;
        }
    }
    cout << "Test passed" << endl;
}


int test2() {

    // Test #1
    cout << "Test 1: " << endl;
    string orig_str = "QLISLM";
    int t = 3; 
    vector<string> strings = {"QLL", "SLM", "QIS", "QLI"};  // k = 4
    int expected_scs_len = 6;  // "QLISLM"
    run_test(orig_str, strings, t, expected_scs_len);
    
    // Test #2
    cout << "Test 2: " << endl;
    orig_str = "ABABB";
    t = 3; 
    strings = {"BA", "BB", "AB"};  // k = 3
    expected_scs_len = 3;  // "BAB"
    run_test(orig_str, strings, t, expected_scs_len);

    // Test #3
    cout << "Test 3: " << endl;
    orig_str = "EILILQ";
    t = 3; 
    strings = {"ELI", "EIL", "ILQ", "ELL", "ELQ"};  // k = 5
    expected_scs_len = 5;  // "ELILQ"
    run_test(orig_str, strings, t, expected_scs_len);

    // Test #4
    cout << "Test 4: " << endl;
    orig_str = "CODING";
    t = 6; 
    strings = {""};  // k = 1
    expected_scs_len = 0;  // ""
    run_test(orig_str, strings, t, expected_scs_len);

    
    // Test #5
    cout << "Test 5: " << endl;
    orig_str = "XXYY";
    t = 2; 
    strings = {"X", "Y"};  // k = 2
    expected_scs_len = 2;  // "XY" or "YX"
    run_test(orig_str, strings, t, expected_scs_len);

     // Test #6
     cout << "Test 6: " << endl;
     orig_str = "ABCABC";
     t = 2; 
     strings = {"ABCA", "BCAB", "CABC"};  // k = 3
     expected_scs_len = 6;  // "ABCABC" or "CABCAB" or ...
     run_test(orig_str, strings, t, expected_scs_len);
     
    // Test #7
    cout << "Test 7: " << endl;
    orig_str = "12344321";
    t = 2; 
    strings = {"234432", "134431", "124421", "123321"};  // k = 4
    expected_scs_len = 8;  // "12344321"
    run_test(orig_str, strings, t, expected_scs_len);

   return 0;
}

int test_empirical(vector<int> n, vector<int> t, vector<int> k) {
    
    std::ofstream outfile("results.csv");
        outfile << "n,t,k,Time(s)\n"; 

    for(int i = 0; i < n.size(); i++){  // n values
        for(int j = 0; j < t.size(); j++){  // t values
            for(int l = 0; l < k.size(); l++){  // k values
                cout << "n = " << n[i] << ", t = " << t[j] << ", k = " << k[l] << endl;  
                // Take average:
                int times = 10;
                chrono::duration<long long, std::nano> duration = chrono::duration<long long, std::nano>(0);
                for (int idx = 0; idx < times; idx++)
                {
                    string original = generateRandomString(n[i]);
                    vector<string> strings(k[l]);
                    for(int m = 0; m < k[l]; m++){
                        strings[m] = deleteRandomChars(original, t[j]);
                    }

                    // Timing the function
                    auto start = std::chrono::high_resolution_clock::now();
                    string res = scs(strings);
                    auto end = std::chrono::high_resolution_clock::now();

                    duration += end - start;  // nanoseconds
                }
                duration = duration/ times;


                // Store n, t, k, and the time taken
                outfile << n[i] << "," << t[j] << "," << k[l] << "," << duration.count() << "\n";

            }
        }       
    }

    outfile.close();
    std::cout << "Results saved in 'empirical_results' folder." << std::endl;
  
    return 0;
    }


int main(){

    // test();
    //test2(); 
    
    vector<int> n = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000};
    vector<int> k = {5};
    vector<int> t = {5};
    // test_empirical(n, t, k) ;
    // system("python3 plot_results.py --test_condition n");  // run python
    
    n = {100000};
    k = {5};
    // t = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    t = {100,200,300,400,500};
    test_empirical(n, t, k) ;
    system("python3 plot_results.py --test_condition t");  // run python 

    return 0;
}