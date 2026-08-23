#include <iostream>
#include <climits> 
#include <unordered_map> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    unordered_map<int, int> map; 
    map.reserve(n * 2); //doubling the capacity reduces the risk of collision 

    int ans = 0, start = 0; 
    for(int end = 0; end < n; ++end) {
        int num; 
        cin >> num; 

        auto it = map.find(num); 
        if(it != map.end() && it->second >= start) 
            start = it->second + 1; 

        map[num] = end; 
        ans = max(ans, end + 1 - start); 
    }

    cout << ans << endl; 
    return 0; 
}