#include <iostream>
#include <vector> 
using namespace std; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    int n, m; 
    cin >> n >> m; 

    vector<int> nums(n + 1); 
    vector<int> ind(n + 2); 

    for(int i = 1; i <= n; ++i) {
        cin >> nums[i]; 
        ind[nums[i]] = i; 
    }

    int rounds = 1; 
    for(int i = 2; i <= n; ++i) {
        if(ind[i] < ind[i - 1])
            ++rounds; 
    }

    ind[0] = ind[n + 1] = n + 1; //edge case

    int a, b; 
    while(m--) {
        cin >> a >> b; 
        int i = nums[a], j = nums[b]; 
        if(i > j) swap(i, j); 

        rounds -=   (ind[i] < ind[i - 1])
                  + (ind[i] > ind[i + 1])
                  + (j - 1 != i && ind[j] < ind[j - 1])
                  + (ind[j] > ind[j + 1]); 

        swap(ind[i], ind[j]); 
        swap(nums[a], nums[b]); 

        rounds +=   (ind[i] < ind[i - 1])
                  + (ind[i] > ind[i + 1])
                  + (j - 1 != i && ind[j] < ind[j - 1])
                  + (ind[j] > ind[j + 1]);

        cout << rounds << '\n'; 
    }

    return 0; 
}