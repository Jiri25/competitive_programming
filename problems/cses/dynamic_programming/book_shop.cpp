#include <iostream>
#include <vector>
#include <climits> 
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x; 
    cin >> n >> x; 

    vector<int> price(n); 
    for(int i = 0; i < n; ++i) cin >> price[i]; 

    vector<int> page(n); 
    for(int i = 0; i < n; ++i) cin >> page[i]; 

    vector<ll> dp(x + 1); 
    for(int i = 0; i < n; ++i) {
        for(int j = x; j >= price[i]; --j) {
            dp[j] = max(dp[j], dp[j - price[i]] + page[i]); 
        }
    }

    cout << dp[x] << endl; 
    return 0; 
}