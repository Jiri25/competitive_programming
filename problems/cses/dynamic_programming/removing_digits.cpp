#include <iostream>
#include <string> 
using namespace std;
typedef long long ll; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    ll cnt = 0; string snum; 
    while(n) {
        int maxi = 0; 
        snum = to_string(n); 
        for(int i = 0; i < snum.size(); ++i) {
            if(snum[i] - '0' > maxi) maxi = snum[i] - '0'; 
        }

        n -= maxi; 
        ++cnt; 
    }

    cout << cnt << endl; 
    return 0; 
}