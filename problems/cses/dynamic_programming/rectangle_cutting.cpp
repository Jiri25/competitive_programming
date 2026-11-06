#include <iostream>
#include <vector> 
#include <climits> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int a, b; 
    cin >> a >> b; 
    if(a > b) swap(a, b);  

    vector<vector<int>> mem(a + 1, vector<int>(b + 1)); 

    for(int i = 1; i <= a; ++i) {
        for(int j = 1; j <= b; ++j) {
            if(i > j) 
                mem[i][j] = mem[j][i]; 

            else if(i < j) {
                mem[i][j] = 1e9; 

                for(int x = 1; x <= i / 2; ++x) {
                    mem[i][j] = min(mem[i][j], 1 + mem[i - x][j] + mem[x][j]); 
                }

                for(int x = 1; x <= j / 2; ++x) {
                    mem[i][j] = min(mem[i][j], 1 + mem[i][j - x] + mem[i][x]); 
                }
            }
        }
    }

    cout << mem[a][b] << endl; 
    return 0; 
}