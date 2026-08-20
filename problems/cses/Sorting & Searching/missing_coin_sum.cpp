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

    long long prefix_sum = 0; 
    for(int i : arr) {
        if(i <= prefix_sum + 1) 
            prefix_sum += i; 
        else 
            break; 
    }

    cout << prefix_sum + 1 << endl; 
    return 0; 
}