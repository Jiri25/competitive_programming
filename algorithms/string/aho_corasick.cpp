#include <iostream>
#include <vector> 
#include <cstring> 
#include <queue> 
using namespace std;

class aho_corasick {
private:
    struct node {
        int next[128]; 
        int suffix_link; 
        int output_link; 
        int t_index; 

        node(int index = -1) : t_index(index), suffix_link(0), output_link(-1) {
            memset(next, 0, sizeof(next)); 
        }
    }; 

    vector<node> pool; 
    const vector<string> data; 

    void build_trie() {
        for(int i = 0; i < data.size(); ++i) {
            const string& str = data[i]; 
            int curr = 0; 

            for(int j = 0; j < str.size(); ++j) {
                if(!pool[curr].next[str[j]]) {
                    pool[curr].next[str[j]] = pool.size(); 
                    pool.emplace_back(); 
                }   

                curr = pool[curr].next[str[j]]; 
            }

            pool[curr].t_index = i; 
        }
    }

    void build_automaton() {
        queue<int> q;
        q.push(0); 

        while(!q.empty()) {
            int parent = q.front(); q.pop(); 
            int suffix = pool[parent].suffix_link; 

            for(int i = 0; i < 128; ++i) {
                int child = pool[parent].next[i]; 
                
                if(child) {
                    int suffix_node = pool[suffix].next[i]; 
                    //root case handled implicitly 
                    if(parent) {
                        pool[child].suffix_link = suffix_node; 
                        bool con = pool[suffix_node].t_index != -1; 
                        pool[child].output_link = con? suffix_node : pool[suffix_node].output_link;
                    } 
                    
                    q.push(child); 
                }
                else {
                    pool[parent].next[i] = pool[suffix].next[i]; 
                }
            }
        }
    }

public:
    aho_corasick(const vector<string>& arr) : data(arr) {
        pool.emplace_back(); 
        build_trie(); 
        build_automaton(); 
    }

    void find_patterns(const string& str) const {
        int curr = 0; 
        for(char c : str) {
            curr = pool[curr].next[c]; 

            if(pool[curr].t_index != -1) cout << data[pool[curr].t_index] << '\n'; 

            int out = pool[curr].output_link; 
            while(out != -1) {
                cout << data[pool[out].t_index] << '\n'; 
                out = pool[out].output_link; 
            }
        }
    }

    //debuggin 
    void print() const {
        for(int i = 0; i < pool.size(); ++i) {
            cout << "Node: " << i << '\n'; 
            cout << "Suffix Link: " << pool[i].suffix_link << '\n'; 
            cout << "Output Link: " << pool[i].output_link << '\n'; 
            cout << "t_index: " << pool[i].t_index << '\n'; 
            cout << "-----------------\n\n"; 
        }
    }
}; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> arr = {
        "aat", "atcg", "c", "cgc", "g", "gg", "ggg", "gta", "gca"
    }; 

    aho_corasick ac(arr); 
    ac.print(); 
    ac.find_patterns("ggg"); cout << endl; 
    ac.find_patterns("aatcg"); cout << endl; 
    ac.find_patterns("atcgca"); cout << endl; 
    ac.find_patterns("ggggg"); 

    return 0; 
}