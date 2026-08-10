#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n; 

    vector<pair<int, int>> arr(n); 

    for(auto& p : arr) 
        cin >> p.first >> p.second; 

    sort(arr.begin(), arr.end(), [](const auto& p1, const auto& p2) {
        return p1.second < p2.second; 
    }); 

    int cnt = 0, end = 0; 
    for(const auto& p : arr) {
        if(p.first >= end) {
            end = p.second;
            ++cnt; 
        }
    }

    cout << cnt << endl; 
    return 0; 
}