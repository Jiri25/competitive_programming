#include <iostream>
#include <vector> 
#include <climits> 
using namespace std;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr); 

    string s1, s2; 
    cin >> s1 >> s2; 

    int n = s1.size(), m = s2.size(); 

    vector<int> prev(m + 1); 
    vector<int> curr(m + 1); 

    for(int i = 1; i <= m; ++i) prev[i] = i; 

    for(int i = 1; i <= n; ++i) {
        curr[0] = i; 

        for(int j = 1; j <= m; ++j) {
            if(s1[i - 1] == s2[j - 1]) curr[j] = prev[j - 1]; 
            else curr[j] = 1 + min(min(curr[j - 1], prev[j]), prev[j - 1]); 
        }

        swap(prev, curr); 
    }

    cout << prev[m] << endl; 
    return 0; 
}