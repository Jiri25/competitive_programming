#include <iostream>
#include <vector> 
#include <algorithm> 
#include <climits> 
using namespace std; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n; 
    cin >> n; 
    vector<pair<int, int>> arr(n * 2); 

    for(int i = 0; i < arr.size(); i += 2) {
        cin >> arr[i].first >> arr[i + 1].first; 
        arr[i].second = 1; 
        arr[i + 1].second = -1; 
    }

    sort(arr.begin(), arr.end(), [](const auto& p1, const auto& p2) {
        if(p1.first != p2.first) 
            return p1.first < p2.first; 
        else 
            return p1.second > p2.second;  
    }); 

    int cnt = 0, ans = 0; 
    for(const auto& p : arr) {
        cnt += p.second; 
        ans = max(ans, cnt); 
    }
    
    cout << ans << endl; 
    return 0; 
}