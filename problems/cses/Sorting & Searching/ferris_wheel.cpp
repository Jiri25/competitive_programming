#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n, x; 
    cin >> n >> x; 
    vector<int> arr(n); 
    for(int& i : arr) 
        cin >> i; 

    sort(arr.begin(), arr.end()); 

    int cnt = 0, i = 0, j = arr.size() - 1; 
    while(i < j) {
        if(arr[i] + arr[j] <= x) 
            ++i, --j; 
        else 
            --j; 

        ++cnt; 
    }

    if(i == j) ++cnt; 

    cout << cnt << endl; 
    return 0; 
}