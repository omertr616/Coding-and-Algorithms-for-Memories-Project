
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

string scs(vector<string> s);

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


