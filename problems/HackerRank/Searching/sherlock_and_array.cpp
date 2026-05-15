#include <iostream>
using namespace std;
typedef long long ll; 

constexpr int MAX = 100005; 
ll prefix[MAX]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n; 
    cin >> t; 

    while(t--) {
        cin >> n; 
        for(int i = 1; i <= n; ++i) {
            cin >> prefix[i]; 
            prefix[i] += prefix[i - 1]; 
        }

        bool ans = false; 
        for(int i = 1; i <= n; ++i) {
            if(prefix[i - 1] == prefix[n] - prefix[i]) {
                ans = true; break; 
            }
        }

        cout << (ans? "YES" : "NO") << '\n'; 
    }
    return 0; 
}