#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std;
typedef long long ll; 

constexpr int mod = 1e9 + 7; 

void init(vector<ll>& arr, int val) {
    if(val != 0) {
        arr[val] = 1; 
    }
    else {
        fill(arr.begin() + 1, arr.end() - 1, 1); 
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n, m; 
    cin >> n >> m; 

    vector<ll> prev(m + 2); 
    vector<ll> curr(m + 2); 

    int val; 
    cin >> val; 

    init(prev, val); 
    
    while(--n) {
        fill(curr.begin(), curr.end(), 0); 
        cin >> val; 

        if(val != 0) {
            curr[val] = (prev[val] + prev[val - 1] + prev[val + 1]) % mod; 
        }
        else {
            for(int i = 1; i <= m; ++i) {
                curr[i] = (prev[i] + prev[i - 1] + prev[i + 1]) % mod; 
            }
        }

        swap(prev, curr); 
    }

    ll sum = 0; 
    for(int i : prev) sum = (sum + i) % mod; 
    
    cout << sum << endl; 
    return 0; 
}
