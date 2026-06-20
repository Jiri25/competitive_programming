#include <iostream>
#include <vector> 
#include <climits> 
using namespace std;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n, m; 
    cin >> n >> m; 

    vector<int> a(n + 1); 
    vector<int> b(m + 1); 

    for(int i = 1; i <= n; ++i) cin >> a[i]; 
    for(int i = 1; i <= m; ++i) cin >> b[i]; 

    vector<vector<int>> dp(n + 1, vector<int>(m + 1)); 

    //O(n * m) 
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i] != b[j]) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); 
            }
            else dp[i][j] = 1 + dp[i - 1][j - 1]; 
        }
    }

    cout << dp[n][m] << '\n';

    vector<int> ans(dp[n][m]); 

    //O(n + m)
    int row = n, col = m; 
    for(int i = ans.size() - 1; i >= 0; --i) {
        while(a[row] != b[col]) {
            if(dp[row - 1][col] >= dp[row][col - 1]) {
                --row; 
            }
            else --col; 
        }
        ans[i] = a[row]; 
        --row, --col; 
    }

    for(int i : ans) cout << i << ' '; 
    return 0; 
}