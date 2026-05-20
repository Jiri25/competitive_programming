#include <iostream>
#include <vector> 
using namespace std;
using ll = long long; 

constexpr int mod = 1e9 + 7; 
vector<int> tree[100005]; 

pair<ll, ll> dfs(int parent, int curr) {
    ll same = 1, diff = 1; 

    for(int child : tree[curr]) {
        if(child == parent) continue; 
        const auto& p = dfs(curr, child); 
        same = (same * (p.first + p.second)) % mod; 
        diff = (diff * p.second) % mod; 
    }

    diff = (same - diff + mod) % mod; 
    return {same, diff}; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; 
    cin >> n; 

    int a, b; 
    for(int i = 0; i < n - 1; ++i) {
        cin >> a >> b; 
        tree[a].push_back(b); 
        tree[b].push_back(a); 
    }

    const auto& ans = dfs(-1, 1); 
    cout << (ans.second * 2) % mod << endl; 
    return 0; 
}