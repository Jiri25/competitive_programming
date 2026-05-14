#include <iostream>
#include <cstring> 
using namespace std;

constexpr int MAX = 10005; 
int freq[MAX]; 
int idx[MAX]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; 
    
    int m, n; 
    while(t--) {
        cin >> m >> n; 
        memset(freq, 0, sizeof(freq)); 

        int num; 
        bool con = true; 
        for(int i = 1; i <= n; ++i) {
            cin >> num; 
            if(con) {
                int need = m - num; 
                if(freq[need]) {
                    cout << idx[need] << ' ' << i << '\n'; 
                    con = false; 
                }

                ++freq[num]; 
                idx[num] = i; 
            }
        }
    }
    return 0; 
}