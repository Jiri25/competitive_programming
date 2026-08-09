#include <iostream>
#include <vector> 
#include <algorithm> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n, m, k; 
    cin >> n >> m >> k; 

    vector<int> N(n); 
    for(int i = 0; i < n; ++i) cin >> N[i]; 

    vector<int> M(m); 
    for(int i = 0; i < m; ++i) cin >> M[i];  

    sort(N.begin(), N.end()); 
    sort(M.begin(), M.end()); 

    int cnt = 0, i = 0, j = 0; 
    while(i < n && j < m) {
        if(M[j] > N[i] + k) 
            ++i; 

        else if(M[j] < N[i] - k) 
            ++j; 

        else 
            ++cnt, ++i, ++j; 
    }

    cout << cnt << endl; 
    return 0; 
}