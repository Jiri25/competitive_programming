#include <iostream>
#include <vector> 
using namespace std;
typedef long long ll; 

constexpr int mod = 1e9 + 7; 

//500000004
ll inverse(ll base, int exp) {
    ll ret = 1; 
    while(exp > 0) {
        if(exp & 1) 
            ret = ret * base % mod; 

        base = base * base % mod; 
        exp >>= 1; 
    }
    return ret; 
}

int main() {
    int n; 
    cin >> n; 

    int sum = (n * (n + 1)) / 2; 
    if(sum & 1) {
        cout << 0 << endl; 
        return 0; 
    }

    int half = sum / 2; 
    vector<ll> dp(half + 1);  
    dp[0] = 1;  

    for(int i = 1; i <= n; ++i) {
        for(int j = half; j >= i; --j) {
            dp[j] = (dp[j] + dp[j - i]) % mod; 
        }
    }

    //int inv = inverse(2, mod - 2); 500000004
    cout << (dp[half] * 500000004) % mod << endl; 
    return 0; 
}