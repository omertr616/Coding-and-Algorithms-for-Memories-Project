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
    // Measure over varing n
    vector<int> n = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000};
    vector<int> k = {10};
    vector<int> t = {10};
    test_empirical(n, t, k) ;
    system("python3 plot_results.py --test_condition n");  // run python
    
    // Measure over varing k
    n = {10000};
    k = {};
    for (int i = 50; i <= 750; i+=50)
    {
        k.push_back(i);
    }
    t = {10};
    test_empirical(n, t, k);
    system("python3 plot_results.py --test_condition k");  // run python

    // Measure over varing t
    n = {10000};
    k = {10};
    t = {};
    for (int i = 10; i <= 60; i+=5)
    {
        t.push_back(i);
    }
    test_empirical(n, t, k) ;
    system("python3 plot_results.py --test_condition t");  // run python 


    return 0;
}