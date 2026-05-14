#include <iostream> 
using namespace std;

char str[100005]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; 

    while(n--) {
        int bit = 0, cnt = 0; 
        cin >> str;
        
        for(int i = 0; str[i]; ++i) {
            int tmp = bit | (1 << (str[i] - 'a')); 
            if(tmp != bit) ++cnt; 
            bit = tmp; 
        }
        cout << cnt << '\n'; 
    }

    return 0; 
}