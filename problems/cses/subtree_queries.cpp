#include <iostream>
#include <vector> 
using namespace std;

typedef long long ll;

constexpr int MAX = 200005; 
vector<int> tree[MAX]; 
int tin[MAX], tout[MAX], val[MAX]; 
ll BIT[MAX]; 

void add(int index, int val, int n) {
    BIT[index] += val; 
    int next = index + (index & -index); 
    if(next <= n) {
        BIT[next] += BIT[index]; 
    }
}

void update(int node, int new_val, int n) {
    int tmp = new_val; 
    new_val -= val[node]; 
    val[node] = tmp; 

    int index = tin[node]; 
    while(index <= n) {
        BIT[index] += new_val; 
        index += index & -index; 
    }
}

ll subtree_sum(int k, int n) {
    int l = tin[k] - 1, r = tout[k];    
    ll a = 0, b = 0; 

    while(l > 0 || r > 0) {
        if(l > 0) {
            a += BIT[l]; 
            l -= l & -l; 
        }

        if(r > 0) {
            b += BIT[r]; 
            r -= r & -r; 
        }
    }

    return b - a; 
}

int timer = 0; 
void dfs(int parent, int curr, int n) {
    ++timer; 
    tin[curr] = timer; 
    add(tin[curr], val[curr], n); 

    for(int child : tree[curr]) {
        if(child == parent) continue; 
        dfs(curr, child, n); 
    }
    tout[curr] = timer; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; 
    cin >> n >> q; 

    for(int i = 1; i <= n; ++i) cin >> val[i]; 

    int a, b;
    for(int i = 0; i < n - 1; ++i) {
        cin >> a >> b; 
        tree[a].push_back(b); 
        tree[b].push_back(a); 
    }

    dfs(-1, 1, n); 

    int t, s, x, k; 
    while(q--) {
        cin >> t; 
        if(t == 1) {
            cin >> s >> x; 
            update(s, x, n); 
        }
        else {
            cin >> k; 
            cout << subtree_sum(k, n) << '\n'; 
        }
    }
    return 0; 
}
