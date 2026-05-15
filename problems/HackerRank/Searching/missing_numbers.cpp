#include <iostream>
using namespace std;

constexpr int MAX = 10005; 
int freq[MAX]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, num; 
    cin >> n;   
    while(n--) {
        cin >> num; 
        ++freq[num]; 
    }

    cin >> m; 
    while(m--) {
        cin >> num; 
        --freq[num]; 
    }

    for(int i = 0; i < MAX; ++i) {
        if(freq[i]) cout << i << ' '; 
    }

    return 0; 
}