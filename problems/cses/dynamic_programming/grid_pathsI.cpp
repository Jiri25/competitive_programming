#include <iostream>
using namespace std; 
typedef long long ll; 

constexpr int mod = 1e9 + 7; 
constexpr int MAX = 1005; 
char str[MAX]; 
ll dp[2][MAX]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n;
    cin >> n; 

    dp[1][0] = 1; 

    bool flag = 0;
    for(int i = 0; i < n; ++i) {
        cin >> str; 
        for(int j = 0; str[j]; ++j) {
            dp[flag][j] = 0; 

            if(str[j] == '.') {
                if(j - 1 >= 0) dp[flag][j] += dp[flag][j - 1]; 
                dp[flag][j] += dp[flag ^ 1][j]; 
                if(dp[flag][j] >= mod) dp[flag][j] -= mod; 
            }
        }
        flag ^= 1; 
    }

    cout << dp[flag ^ 1][n - 1] << endl; 
    return 0; 
}