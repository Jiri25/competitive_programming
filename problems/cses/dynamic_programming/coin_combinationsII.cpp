#include <iostream>
using namespace std;
typedef long long ll; 
 
constexpr int MAX = 1000005; 
constexpr int mod = 1e9 + 7; 
ll dp[MAX]; 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
 
    int n, x; 
    cin >> n >> x; 
 
    dp[0] = 1; 
 
    int coin; 
    while(n--) {
        cin >> coin; 
        for(int i = coin; i <= x; ++i) {
            int need = i - coin; 
            dp[i] += dp[need]; 
            if(dp[i] >= mod) dp[i] -= mod; 
        }
    }
 
    cout << dp[x] << endl; 
    return 0; 
}