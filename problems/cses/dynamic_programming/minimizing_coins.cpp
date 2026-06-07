#include <iostream>
#include <algorithm> 
#include <climits> 
using namespace std;
typedef long long ll;

constexpr int MAX = 1000005; 
ll dp[MAX]; 
int coin[100]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x; 
    cin >> n >> x; 

    for(int i = 0; i < n; ++i) cin >> coin[i]; 

    fill(dp + 1, dp + x + 1, 1e9); 

    for(int i = 0; i <= x; ++i) {
        if(dp[i] == 1e9) continue; 

        for(int j = 0; j < n; ++j) {
            int next = i + coin[j]; 
            if(next <= x) {
                dp[next] = min(dp[next], dp[i] + 1); 
            }
        }
    }

    cout << (dp[x] != 1e9? dp[x] : -1) << endl; 
    return 0; 
}