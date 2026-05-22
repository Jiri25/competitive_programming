#include <iostream>
#include <cstring>
using namespace std;
using ll = long long; 

constexpr int mod = 1e9 + 7; 
constexpr int MAX = 4500; 
constexpr int MAXOR = (1 << (32 - __builtin_clz(MAX))) - 1; //8191
int cnt[MAX + 1]; 
bool prime[MAXOR + 1]; 
ll mem[2][MAXOR + 1]; 

void sieve() {
    prime[0] = prime[1] = true; 
    for(int i = 4; i <= MAXOR; i += 2) prime[i] = true; 

    for(int i = 3; i * i <= MAXOR; i += 2) {
        if(prime[i]) continue; 
        for(int j = i * i; j <= MAXOR; j += i * 2) {
            prime[j] = true; 
        }
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    sieve(); 
    
    int t; 
    cin >> t; 

    while(t--) {
        int n; 
        cin >> n; 
        memset(cnt, 0, sizeof(cnt)); 
        memset(mem, 0, sizeof(mem)); 

        int num; 
        for(int i = 0; i < n; ++i) {
            cin >> num; 
            ++cnt[num]; 
        }

        mem[0][0] = 1; 
        bool flag = 1; 

        for(int i = 3500; i <= 4500; ++i) {
            if(!cnt[i]) continue; 

            int even, odd; 
            even = odd = (cnt[i] >> 1) + 1; 
            if(!(cnt[i] & 1)) --odd; 

            for(int j = 0; j <= MAXOR; ++j) {
                int XOR = i ^ j; 
                mem[flag][j] = (mem[flag ^ 1][j] * even + mem[flag ^ 1][XOR] * odd) % mod; 
            }

            flag ^= 1; 
        }

        ll ans = 0; 
        for(int i = 2; i <= MAXOR; ++i) {
            if(prime[i]) continue; 
            ans = (ans + mem[flag ^ 1][i]) % mod; 
        }

        cout << ans << '\n'; 
    }

    return 0; 
}