#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    vector<int> top; 
    top.reserve(n); 

    int num; 
    while(n--) {
        cin >> num; 
        auto it = upper_bound(top.begin(), top.end(), num); 

        if(it == top.end())
            top.push_back(num); 
        else    
            *it = num; 
    }

    cout << top.size() << endl; 
    return 0; 
}