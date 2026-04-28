#include <iostream>
using namespace std;

typedef long long ll; 

class fenwick {
private:
    ll arr[200005]; 

public:
    void add(int index, int data, int n) {
        arr[index] += data; 
        int next = index + (index & -index); 
        if(next <= n) {
            arr[next] += arr[index]; 
        }
    }

    void range_update(int a, int b, int u, int n) {
        ++b; 
        while(a <= n || b <= n) {
            if(a <= n) {
                arr[a] += u; 
                a += a & -a; 
            }

            if(b <= n) {
                arr[b] += -u; 
                b += b & -b; 
            }
        }
    }

    ll get_point(int k) const {
        ll sum = 0; 
        while(k) {
            sum += arr[k]; 
            k -= k & -k; 
        }

        return sum; 
    }
}; 

fenwick fw; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; 
    cin >> n >> q; 

    int curr, prev = 0; 
    for(int i = 0; i < n; ++i) {
        cin >> curr; 
        fw.add(i + 1, curr - prev, n); 
        prev = curr; 
    }

    int t, a, b, u, k; 
    while(q--) {
        cin >> t; 

        if(t == 1) {
            cin >> a >> b >> u; 
            fw.range_update(a, b, u, n); 
        }
        else {
            cin >> k; 
            cout << fw.get_point(k) << '\n'; 
        }
    }    

    return 0; 
}