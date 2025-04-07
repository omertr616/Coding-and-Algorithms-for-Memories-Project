
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include "SCS_multiple_sequences.cpp"

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

// Function to test the SCS function with random strings
// and check if the SCS length is less than or equal to n.
// This is only senity check since the SCS maight need be less than n
// but not equal to n.
int test(int _n, int _t, int _k) {
    if (_t > _n) {
        cout << "t cannot be greater than n" << endl;
        return 0;
    }
    
    int tests = 100;
    for(int i = 0; i < tests; i++){
        int n = rand() % _n + 2;
        int t = rand() % _t + 1;
        int k = rand() % _k + 1;
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
            cout << "Test passed \n" << endl;
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
            cout << " " << endl;
            return 0;
        }
    }
    cout << "All tests passed" << endl;
    return 0;
}

int main() {
    // Test the SCS function with random strings
    int n = 1000; // Maximum length of the original string
    int t = 10;   // Number of characters to delete
    int k = 5;    // Number of strings to generate

    test(n, t, k);

    return 0;
}
