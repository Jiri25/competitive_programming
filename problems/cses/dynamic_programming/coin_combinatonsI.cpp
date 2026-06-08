#include <iostream>
using namespace std;
typedef long long ll; 

constexpr int MAX = 1000005; 
constexpr int mod = 1e9 + 7; 
ll dp[MAX]; 
int coin[100]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n, x; 
    cin >> n >> x; 

    for(int i = 0; i < n; ++i) cin >> coin[i]; 

    dp[0] = 1; 
    for(int i = 0; i <= x; ++i) {
        for(int j = 0; j < n; ++j) {
            int next = i + coin[j]; 
            if(next <= x) {
                dp[next] = (dp[next] + dp[i]) % mod; 
            }
        }
    }

    cout << dp[x] << endl; 
    return 0; 
}