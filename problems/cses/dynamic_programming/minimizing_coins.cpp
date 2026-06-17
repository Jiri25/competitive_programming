#include <iostream>
#include <vector> 
#include <climits> 
using namespace std;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n, x; 
    cin >> n >> x; 

    vector<int> coin(n); 
    for(int i = 0; i < n; ++i) cin >> coin[i]; 

    vector<int> dp(x + 1, 1e9); 
    dp[0] = 0; 

    for(int val : coin) {
        for(int i = val; i <= x; ++i) {
            dp[i] = min(dp[i], dp[i - val] + 1); 
        }
    }

    cout << (dp[x] == 1e9? -1 : dp[x]) << endl; 
    return 0; 
}