#include <iostream>
#include <climits> 
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n; 
    cin >> t; 

    while(t--) {
        cin >> n; 
        int prev, curr; 
        cin >> prev; 

        ll mini = 0, maxi = 0; 
        while(--n) {
            cin >> curr; 
            ll tmp = mini; 
            mini = max(maxi + prev - 1, mini); 
            maxi = max(maxi + abs(prev - curr), tmp + curr - 1); 
            prev = curr; 
        }

        cout << max(mini, maxi) << '\n'; 
    }
    return 0; 
}