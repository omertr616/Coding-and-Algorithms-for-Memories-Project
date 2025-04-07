#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include "SCS_multiple_sequences.cpp"

using namespace std;

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


int main() {

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
