#include <iostream>
#include <climits> 
using namespace std;
typedef long long ll; 

constexpr int MAX_PRICE = 100005;
constexpr int MAX_N = 1005; 
ll dp[MAX_PRICE]; 
int price[MAX_N]; 
int page[MAX_N]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n, x; 
    cin >> n >> x; 

    for(int i = 0; i < n; ++i) cin >> price[i];

    for(int i = 0; i < n; ++i) cin >> page[i]; 

    for(int i = 0; i < n; ++i) {
        for(int j = x; j >= price[i]; --j) {
            dp[j] = max(dp[j], dp[j - price[i]] + page[i]); 
        }
    }

    cout << dp[x] << endl; 
    return 0; 
}