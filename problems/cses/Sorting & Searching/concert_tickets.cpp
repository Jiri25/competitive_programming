#include <iostream>
#include <set> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n, m; 
    cin >> n >> m; 

    int num; 
    multiset<int> set; 
    while(n--) {
        cin >> num; 
        set.insert(num); 
    }

    while(m--) {
        cin >> num; 
        auto it = set.upper_bound(num); 
        
        if(it == set.begin()) 
            cout << -1 << '\n'; 

        else {
            --it; 
            cout << *it << '\n'; 
            set.erase(it); 
        }
    }

    return 0; 
}