#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 
    vector<int> arr(n); 
    for(int& i : arr) 
        cin >> i; 

    sort(arr.begin(), arr.end()); 
    cout << unique(arr.begin(), arr.end()) - arr.begin() << endl; 
    return 0; 
}