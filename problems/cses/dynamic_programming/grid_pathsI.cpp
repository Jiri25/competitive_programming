#include <iostream>
#include <vector> 
using namespace std;
typedef long long ll;

constexpr int mod = 1e9 + 7; 
char str[1005]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n; 

    vector<ll> dp(n + 1); 
    dp[1] = 1; 

    for(int i = 0; i < n; ++i) {
        cin >> str; 
        
        for(int j = 0; str[j]; ++j) {
            if(str[j] != '*') {
                dp[j + 1] = (dp[j + 1] + dp[j]) % mod; 
            }
            else dp[j + 1] = 0; 
        }
    }

    cout << dp[n] << endl; 
    return 0; 
}