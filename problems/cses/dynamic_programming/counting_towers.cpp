#include <iostream>
using namespace std;
typedef long long ll; 

constexpr int mod = 1e9 + 7; 
constexpr int MAX = 1000005; 
ll dp[MAX][2]; 

void compute() {
    dp[1][0] = dp[1][1] = 1; 

    for(int i = 2; i <= 1000000; ++i) {
        dp[i][0] = (dp[i - 1][0] * 4 + dp[i - 1][1]) % mod; 
        dp[i][1] = (dp[i - 1][1] * 2 + dp[i - 1][0]) % mod; 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    compute(); 

    int t; 
    cin >> t; 

    int n; 
    while(t--) {
        cin >> n; 
        cout << (dp[n][0] + dp[n][1]) % mod << '\n'; 
    }

    return 0; 
}