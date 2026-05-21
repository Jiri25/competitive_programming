#include <iostream>
#include <cstring> 
using namespace std;

constexpr int MAX = 1005; 
bool mem[MAX]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t; 

    string a, b; 
    while(t--) {
        cin >> a >> b; 
        memset(mem, false, b.size() * sizeof(bool)); 
        mem[0] = true; 

        //O(a.size() * b.size()) 
        for(char c : a) {
            bool is_upper = isupper(c); 
            char upcase = toupper(c); 

            for(int j = b.size(); j > -1; --j) {
                if(mem[j]) {
                    if(j < b.size() && upcase == b[j]) mem[j + 1] = true; 
                    if(is_upper) mem[j] = false; 
                }
            }
        }
        
        cout << (mem[b.size()]? "YES" : "NO") << '\n'; 
    }

    return 0; 
}