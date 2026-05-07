#include <iostream>
#include <vector> 
#include <algorithm> 
#include <unordered_map> 
using namespace std;

typedef long long ll;

constexpr int MAX = 200005; 
int arr[MAX], ans[MAX]; 
vector<pair<int, int>> queries[MAX]; 
unordered_map<int, int> map; 

int BIT[MAX]; 

void update(int index, int n) {
    while(index <= n) {
        ++BIT[index]; 
        index += index & -index; 
    }
}

void move_marker(int new_pos, int old_pos, int n) {
    while(new_pos <= n || old_pos <= n) {
        if(new_pos <= n) {
            ++BIT[new_pos]; 
            new_pos += new_pos & -new_pos; 
        }

        if(old_pos <= n) {
            --BIT[old_pos]; 
            old_pos += old_pos & -old_pos; 
        }
    }
}

int solve(int index) {
    int ret = 0; 
    while(index > 0) {
        ret += BIT[index]; 
        index -= index & -index; 
    }
    return ret; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map.reserve(MAX); 

    int n, q;
    cin >> n >> q; 

    for(int i = 1; i <= n; ++i) cin >> arr[i]; 

    int l, r; 
    for(int i = 0; i < q; ++i) {
        cin >> l >> r; 
        queries[l].push_back({r, i}); 
    }

    for(int i = n; i >= 1; --i) {
        int val = arr[i]; 

        const auto& it = map.find(val); 
        if(it != map.end()) {
            move_marker(i, it->second, n); 
            it->second = i; 
        }
        else {
            update(i, n); 
            map[val] = i; 
        }

        for(const auto& p : queries[i]) {
            int r = p.first; 
            int index = p.second; 
            ans[index] = solve(r); 
        }
    }

    for(int i = 0; i < q; ++i) cout << ans[i] << '\n'; 
    return 0; 
}