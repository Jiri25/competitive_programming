#include <iostream>
#include <algorithm> 
#include <cstring> 
using namespace std;
typedef long long ll; 
 
constexpr int mod = 1e9 + 7; 
ll dp[2][105]; 
 
void init(int num, int m) {
    if(num == 0) {
        fill(dp[1] + 1, dp[1] + m + 1, 1); 
    }
    else dp[1][num] = 1; 
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
 
    int n, m; 
    cin >> n >> m; 
 
    int num; 
    cin >> num; 
    init(num, m); 
 
    bool flag = 0; 
 
    while(--n) {
        memset(dp[flag] + 1, 0, m * sizeof(ll)); 
 
        cin >> num; 
        if(num == 0) {
            for(int i = 1; i <= m; ++i) {
                dp[flag][i] = dp[flag ^ 1][i - 1] + dp[flag ^ 1][i] + dp[flag ^ 1][i + 1]; 
                if(dp[flag][i] >= mod) dp[flag][i] %= mod; 
            }
        }
        else {
            dp[flag][num] = dp[flag ^ 1][num - 1] + dp[flag ^ 1][num] + dp[flag ^ 1][num + 1];
            if(dp[flag][num] >= mod) dp[flag][num] %= mod; 
        }
 
        flag ^= 1; 
    }
 
    ll sum = 0; 
    for(int i = 1; i <= m; ++i) {
        sum += dp[flag ^ 1][i]; 
        if(sum >= mod) sum %= mod; 
    }
 
    cout << sum << endl; 
    return 0; 
}