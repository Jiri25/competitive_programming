#include <iostream>
using namespace std;

long long cap[251];

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    cap[0] = 1; 
    int n, m; 
    cin >> n >> m; 

    long long c; 
    for(int i = 0; i < m; ++i) {
        cin >> c; 
        for(int j = c; j <= n; ++j) {
            cap[j] += cap[j - c]; 
        }
    }

    cout << cap[n] << endl; 
    return 0; 
}


/*
n = 10
m = {2, 5, 3, 6}
        0   1   2   3   4   5   6   7   8   9   10
        1   0   0   0   0   0   0   0   0   0   0  
c = 2:  1   0   1   0   1   0   1   0   1   0   1
c = 5:  1   0   1   0   1   1   1   1   1   1   2
c = 3:  1   0   1   1   1   2   2   2   3   3   4
c = 6:  1   0   1   1   1   2   3   2   4   4   5
*/