#include <iostream>
#include <climits> 
using namespace std;
using ll = long long;  

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    ll sum = -1e9, curr = 0; 
    int num; 
    while(n--) {
        cin >> num; 
        curr = curr < 0? num : curr + num; 
        sum = max(sum, curr); 
    }

    cout << sum << endl; 
    return 0; 
}