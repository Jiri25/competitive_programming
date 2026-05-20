#include <iostream>
using namespace std;

typedef long long ll;
constexpr int mod = 1e9 + 7; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x; 
    cin >> n >> k >> x; 
    ll prev, curr, tmp; 

    if(x == 1) { prev = 1, curr = 0; } 
    else { prev = 0, curr = 1; } 

    while(--n) {
        tmp = curr; 
        curr = (prev * (k - 1) + curr * (k - 2)) % mod; 
        prev = tmp; 
    }

    cout << prev << endl; 
    return 0; 
}