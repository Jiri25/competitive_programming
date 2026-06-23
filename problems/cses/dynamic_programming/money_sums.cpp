#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    vector<int> coin(n); 

    int sum = 0; 
    for(int i = 0; i < n; ++i) {
        cin >> coin[i]; 
        sum += coin[i]; 
    }

    vector<bool> dp(sum + 1); 
    dp[0] = true; 

    int cnt = 0; 
    for(int c : coin) {
        for(int i = sum; i >= 0; --i) {
            if(dp[i] == true) {
                if(dp[i + c] == false) ++cnt; 
                dp[i + c] = true; 
            }
        }
    }

    cout << cnt << '\n'; 
    
    for(int i = 1; i <= sum; ++i) {
        if(dp[i]) cout << i << ' '; 
    }

    return 0; 
}