#include <iostream>
#include <vector>
#include <climits> 
using namespace std;
typedef long long ll; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    vector<int> list(n); 
    ll sum = 0; 
    for(int i = 0; i < n; ++i) {
        cin >> list[i]; 
        sum += list[i]; 
    }

    vector<ll> dp(n); //dp[i] = max difference between s1 and s2 (s1 - s2) 
    for(int i = 0; i < n; ++i) {
        dp[i] = list[i]; 
    }

    for(int len = 2; len <= n; ++len) {
        for(int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1; 
            dp[i] = max(list[i] - dp[i + 1], list[j] - dp[i]); 
        }
    }

    cout << (dp[0] + sum) / 2LL << endl; 
    return 0; 
}