#include <iostream>
#include <algorithm> 
#include <climits> 
using namespace std;
 
constexpr int MAX = 200005; 
pair<int, int> arr[MAX * 2]; 
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n; 
    cin >> n; 
 
    int in, out, ptr = 0; 
    for(int i = 0; i < n; ++i) {
        cin >> in >> out; 
 
        arr[ptr].first = in; 
        arr[ptr].second = 1; 
        ++ptr; 
 
        arr[ptr].first = out; 
        arr[ptr].second = -1; 
        ++ptr; 
    }
 
    sort(arr, arr + ptr, [](const auto& a, const auto& b) {
        if(a.first != b.first) return a.first < b.first; 
        return a.second > b.second; 
    }); 
 
    int curr = 0, ans = 0; 
    for(int i = 0; i < ptr; ++i) {
        curr += arr[i].second; 
        ans = max(curr, ans); 
    }
 
    cout << ans << endl; 
    return 0; 
}