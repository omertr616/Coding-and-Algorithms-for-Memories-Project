#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    public:
        string shortestCommonSupersequence(string str1, string str2) {
            vector<vector<int>> dp(str1.size()+1, vector<int>(str2.size()+1));
            for (int i = 0; i <= str1.size(); i++)
            {
                dp[i][0] = i;
            }
            for (int j = 0; j <= str2.size(); j++)
            {
                dp[0][j] = j;
            }
            for (int i = 1; i <= str1.size(); i++)
            {
                for (int j = 1; j <= str2.size(); j++)
                {
                    if(str1[i-1] == str2[j-1]){
                        dp[i][j] = dp[i-1][j-1] + 1;
                    }
                    else{
                        dp[i][j] = min(dp[i-1][j], dp[i][j-1])+1;
                    }
                }
            }

            int i = str1.size(), j = str2.size();
            string scs = "";
            while(i > 0 && j > 0){
                if(str1[i-1] == str2[j-1])
                {
                    scs = str1[i-1] + scs;
                    i--;
                    j--;
                }
                else if(dp[i][j] == dp[i-1][j]+1){
                    scs = str1[i-1] + scs;
                    i--;
                }
                else{
                    scs = str2[j-1] + scs;
                    j--;
                }
            }
            scs = str1.substr(0, i) + str2.substr(0, j) + scs;
            return scs;
        }
};

int main(){
    Solution s;
    string str1 = "abac", str2 = "cab";
    string scs = s.shortestCommonSupersequence(str1, str2);
    cout << scs << endl;
    return 0;
}