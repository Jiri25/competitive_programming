#include <iostream>
#include <vector> 
#include <climits> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int a, b; 
    cin >> a >> b; 

    //dp[i][j] : min number of cuts to transform into squares
    vector<vector<int>> dp(a + 1, vector<int>(b + 1, 1e9)); 

    for(int i = 1; i <= a; ++i) {
        for(int j = 1; j <= b; ++j) {
            if(i == j) {
                dp[i][j] = 0; 
                continue; 
            }

            //vertical cut
            for(int cut = 1; cut <= i / 2; ++cut) {
                dp[i][j] = min(dp[i][j], 1 + dp[i - cut][j] + dp[cut][j]); 
            }

            //horizontal cut 
            for(int cut = 1; cut <= j / 2; ++cut) {
                dp[i][j] = min(dp[i][j], 1 + dp[i][j - cut] + dp[i][cut]); 
            }
        }
    }

    cout << dp[a][b] << endl; 
    return 0; 
}