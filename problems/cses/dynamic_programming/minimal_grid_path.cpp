#include <iostream>
#include <vector> 
#include <climits> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n; 

    vector<string> grid(n); 
    for(auto& row : grid) cin >> row; 

    vector<vector<bool>> visited(n, vector<bool>(n)); 
    vector<pair<int, int>> curr_pos; 
    vector<pair<int, int>> next_pos; 
    curr_pos.push_back({0, 0}); 

    string ans; 
    ans.reserve(2 * n); 

    char min_char = grid[0][0];     
    while(!curr_pos.empty()) {
        ans.push_back(min_char); 
        char next_min_char = 'Z' + 1; 
        next_pos.clear(); 

        for(auto [r, c] : curr_pos) {
            if(grid[r][c] != min_char) continue; 

            if(r + 1 < n && !visited[r + 1][c]) {
                visited[r + 1][c] = true; 
                next_pos.push_back({r + 1, c}); 
                next_min_char = min(next_min_char, grid[r + 1][c]); 
            }

            if(c + 1 < n && !visited[r][c + 1]) {
                visited[r][c + 1] = true; 
                next_pos.push_back({r, c + 1}); 
                next_min_char = min(next_min_char, grid[r][c + 1]); 
            }
        }

        swap(curr_pos, next_pos);
        min_char = next_min_char;  
    }

    cout << ans << endl; 
    return 0; 
}