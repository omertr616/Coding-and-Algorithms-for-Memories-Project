#include <iostream>
#include <string>
#include <queue>

using namespace std;
 
string scs(string& str1, string& str2);  // regular_dp
string scs(vector<string>& strings);   // bfs0-1 

int main() {
    std::string a, b;
    std::cin >> a >> b;  
    std::cout << scs(a, b) << std::endl;  
    return 0;
}
