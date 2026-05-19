#include <iostream>
#include <climits> 
using namespace std;
typedef long long ll;

int arr[10005]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n; 
    cin >> t; 

    //O(n * t)
    while(t--) {
        cin >> n; 
        int lowest_level = INT_MAX; 
        for(int i = 0; i < n; ++i) {
            cin >> arr[i]; 
            lowest_level = min(arr[i], lowest_level); 
        }

        int common_level[3]; //best possible common levels 
        for(int sub = 0; sub < 3; ++sub) {
            common_level[sub] = lowest_level - sub; 
        }

        //O(n) 
        ll ans[3] = {}; 
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 3; ++j) {
                int diff = arr[i] - common_level[j]; 
                ans[j] += diff / 5, diff %= 5; 
                ans[j] += diff / 2, diff %= 2; 
                ans[j] += diff; 
            }
        }

        cout << min(ans[0], min(ans[1], ans[2])) << '\n'; 
    }

    return 0; 
}