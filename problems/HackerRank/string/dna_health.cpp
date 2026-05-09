#include <iostream>
#include <vector> 
#include <queue> 
#include <climits> 
using namespace std; 
typedef long long ll; 

constexpr int N = 100005;
constexpr int MAX = 2000005; 
char str[MAX]; 
int trie[MAX][26]; 
int link[MAX], tin[MAX], tout[MAX], h[N], pattern_nodes[N]; 
vector<int> tree[MAX]; 

int ptr = 1; 
void add_to_trie(char* str, int index) {
    int curr = 0; 
    for(int i = 0; str[i]; ++i) {
        if(!trie[curr][str[i] - 'a']) {
            trie[curr][str[i] - 'a'] = ptr; 
            ++ptr; 
        }
        curr = trie[curr][str[i] - 'a']; 
    }

    pattern_nodes[index] = curr; 
}

void build() {
    queue<int> q; 
    q.push(0); 

    while(!q.empty()) {
        int parent = q.front(); q.pop(); 
        int suffix = link[parent]; 

        for(int i = 0; i < 26; ++i) {
            int child = trie[parent][i]; 
            if(child) {
                if(parent) {
                    link[child] = trie[suffix][i]; 
                }
                tree[link[child]].push_back(child); 
                q.push(child); 
            }
            else {
                trie[parent][i] = trie[suffix][i]; 
            }
        }
    }
}

int timer = 0; 
void dfs(int curr) {
    ++timer; 
    tin[curr] = timer;
    for(int child : tree[curr]) {
        dfs(child); 
    }
    tout[curr] = timer; 
}

ll BIT[MAX]; 

void update(int index, int val) {
    int l = tin[index], r = tout[index] + 1; 
    while(l <= timer || r <= timer) {
        if(l <= timer) {
            BIT[l] += val; 
            l += l & -l; 
        }

        if(r <= timer) {
            BIT[r] += -val; 
            r += r & -r; 
        }
    }
}

ll solve(int index) {
    ll ret = 0; index = tin[index]; 
    while(index > 0) {
        ret += BIT[index]; 
        index -= index & -index; 
    }
    return ret; 
}

vector<int> sub[N], add[N], query_nodes[N]; 
ll ans[N]; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    for(int i = 1; i <= n; ++i) {
        cin >> str; 
        add_to_trie(str, i); 
    }   

    for(int i = 1; i <= n; ++i) cin >> h[i]; 

    build(); dfs(0); 

    int q; 
    cin >> q; 

    int l, r; 
    for(int i = 0; i < q; ++i) {
        cin >> l >> r >> str; 
        ++l, ++r; 
        sub[l - 1].push_back(i); 
        add[r].push_back(i); 

        int curr = 0; 
        for(int j = 0; str[j]; ++j) {
            curr = trie[curr][str[j] - 'a']; 
            query_nodes[i].push_back(curr); 
        }
    }
    
    for(int i = 1; i <= n; ++i) {
        int node = pattern_nodes[i]; 
        update(node, h[i]); 

        for(int q_order : sub[i]) {
            for(int node : query_nodes[q_order]) {
                ans[q_order] -= solve(node); 
            }
        }

        for(int q_order : add[i]) {
            for(int node : query_nodes[q_order]) {
                ans[q_order] += solve(node); 
            }
        }
    }

    ll mini = LONG_LONG_MAX, maxi = 0; 
    for(int i = 0; i < q; ++i) {
        mini = min(mini, ans[i]); 
        maxi = max(maxi, ans[i]); 
    }

    cout << mini << ' ' << maxi << endl; 
    return 0; 
}