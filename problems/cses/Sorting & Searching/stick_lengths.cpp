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

    nth_element(arr.begin(), arr.begin() + n / 2, arr.end()); 
    
    int target = arr[n / 2]; 
    long long ret = 0; 
    for(int i : arr) 
        ret += abs(target - i); 

    cout << ret << endl; 
    return 0; 
}