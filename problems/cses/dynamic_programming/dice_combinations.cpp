#include <iostream>
using namespace std;
using ll = long long; 

constexpr int mod = 1e9 + 7; 
constexpr int MAX = 1000005; 
ll mem[MAX]; 

void init() {
    int prefix = 0; 
    for(int i = 1; i <= 6; ++i) {
        mem[i] = prefix + 1; 
        prefix += mem[i]; 
    }
}

void solve(int n) {
    init(); 
    for(int i = 7; i <= n; ++i) {
        mem[i] = (mem[i] + mem[i - 1] + mem[i - 2] + mem[i - 3] 
            + mem[i - 4] + mem[i - 5] + mem[i - 6]) % mod; 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;  

    solve(n); 
    cout << mem[n] << endl; 
    return 0; 
}