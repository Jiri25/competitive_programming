#include <iostream>
#include <vector> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 
    vector<int> arr(n + 1); 

    int num; 
    for(int i = 1; i <= n; ++i) {
        cin >> num; 
        arr[num] = i; 
    }

    int rounds = 1; 
    for(int i = 2; i <= n; ++i) {
        if(arr[i - 1] > arr[i]) 
            ++rounds; 
    }

    cout << rounds << endl; 
    return 0; 
}