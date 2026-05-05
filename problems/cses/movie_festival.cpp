#include <iostream>
#include <algorithm> 
using namespace std;

pair<int, int> arr[200005]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n; 

    for(int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second; 
    }

    sort(arr, arr + n, [](const auto& a, const auto& b){
        return a.second < b.second; 
    }); 

    int end = 0, cnt = 0; 
    for(int i = 0; i < n; ++i){
        if(arr[i].first >= end) {
            ++cnt; end = arr[i].second; 
        }
    }

    cout << cnt << endl; 
    return 0; 
}