#include <iostream>
using namespace std;
using ll = long long; 

constexpr int mod = 1e9 + 7, MAX = 200005; 
char str[MAX]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> str; 

    ll ans = 0, curr_substr = 0; 
    for(int i = 0; str[i]; ++i) {
        curr_substr = (curr_substr * 10 + (str[i] - '0') * (i + 1)) % mod; 
        ans = (ans + curr_substr) % mod; 
    }

    cout << ans << endl; 
    return 0; 
}