#include <iostream>
#include <cstring> 
#include <vector> 
#include <climits> 
using namespace std;

//----------------------Total Space Required-----------------------------
//number of leaves = m (the number of leaves = the size of the original string data)
//number of non-leaves <= m - 1 (each non-leaf node has at least two children)
//Total: O(m + (m - 1)) ==> O(2m - 1) ==> O(m).
//Thus, space grows linearly with respect to the size of the original string data 
class suffix_tree {
private:
    struct node {
        int l; int* r; 
        int next[128]; 
        int suffix_link; 
        int index; //leaf index 
        int leaf_count; //precomputing it reduces O(m + k) queries to O(m). 

        int len() const { return *r - l + 1; } 

        node(int start, int* end) : l(start), r(end), suffix_link(0), index(-1), leaf_count(0) {
            memset(next, -1, sizeof(next)); 
        }
    };

    vector<node> pool; 
    int global_end = -1; 
    const string text;

    //-------Active Point--------
    int active_node = 0; 
    int active_edge = -1; 
    int active_len = 0; 
    int remainder = 0; 

    void build() {
        for(int i = 0; i < text.size(); ++i) {
            ++remainder; 
            ++global_end; 

            int last_internal_node = 0; 

            while(remainder) {
                if(active_len == 0) active_edge = i; 

                char c = text[active_edge]; 

                if(pool[active_node].next[c] == -1) {
                    pool[active_node].next[c] = pool.size(); 
                    pool.emplace_back(i, &global_end); 

                    if(last_internal_node) {
                        pool[last_internal_node].suffix_link = active_node; 
                        last_internal_node = 0; 
                    }
                }
                else {
                    int next_node = pool[active_node].next[c]; 
                    int edge_len = pool[next_node].len(); 

                    if(active_len >= edge_len) {
                        active_node = next_node; 
                        active_edge += edge_len; 
                        active_len -= edge_len; 
                        continue; 
                    }

                    if(text[pool[next_node].l + active_len] == text[i]) {
                        ++active_len; 

                        if(last_internal_node && active_node) {
                            pool[last_internal_node].suffix_link = active_node; 
                            last_internal_node = 0; 
                        }
                        break; 
                    }

                    int next_l = pool[next_node].l; 
                    int split_end = next_l + active_len - 1; 

                    pool.emplace_back(next_l, new int(split_end)); //fixed end 
                    int split_node = pool.size() - 1; 
                    pool[active_node].next[c] = split_node; 

                    pool.emplace_back(i, &global_end); 
                    pool[split_node].next[text[i]] = pool.size() - 1; 

                    pool[next_node].l += active_len; 
                    pool[split_node].next[text[pool[next_node].l]] = next_node; 

                    if(last_internal_node) {
                        pool[last_internal_node].suffix_link = split_node; 
                    }

                    last_internal_node = split_node; 
                }

                --remainder; 

                if(!active_node && active_len > 0) {
                    --active_len; 
                    active_edge = i - remainder + 1; 
                }
                else if(active_node) {
                    active_node = pool[active_node].suffix_link; 
                }
            }
        }
    }

    void assign_leaf_indices(int curr = 0, int path_len = 0) {
        bool is_leaf = true; 
        
        for(int i = 0; i < 128; ++i) {
            int child = pool[curr].next[i]; 
            if(child == -1) continue; 

            is_leaf = false; 
            assign_leaf_indices(child, path_len + pool[child].len()); 
            pool[curr].leaf_count += pool[child].leaf_count; 
        }

        if(is_leaf) {
            pool[curr].index = text.size() - path_len; 
            pool[curr].leaf_count = 1; 
        }
    }

    void print_occurrence_suffixes(int curr) const {
        for(int i = 0; i < 128; ++i) {
            int child = pool[curr].next[i]; 
            if(child == -1) continue; 

            print_occurrence_suffixes(child); 
        }

        if(pool[curr].index != -1) {
            for(int i = pool[curr].index; i < text.size(); ++i) {
                cout << text[i]; 
            } cout << '\n'; 
        }
    }

    //-----------Helpers------------
    int count_leaves(int curr) const { 
        bool is_leaf = true; 

        int cnt = 0; 
        for(int i = 0; i < 128; ++i) {
            int child = pool[curr].next[i]; 
            if(child == -1) continue; 

            is_leaf = false; 
            cnt += count_leaves(child); 
        }

        return is_leaf? 1 : cnt; 
    }

    void search_suffixes(int curr, string& ret) const {
        bool is_leaf = true; 
        for(int i = 0; i < 128; ++i) {
            int child = pool[curr].next[i]; 
            if(child == -1) continue; 

            int start = pool[child].l; 
            int end = *pool[child].r + 1; 

            int before_len = ret.size(); 
            for(int j = start; j < end; ++j) ret.push_back(text[j]); 

            is_leaf = false; 
            search_suffixes(child, ret); 

            ret.resize(before_len); 
        }

        if(is_leaf) {   
            cout << ret << '\n'; 
        }
    }

public: 
    suffix_tree(const string& str) : text(str) {
        pool.emplace_back(-1, new int(-1)); 
        build(); 
        assign_leaf_indices(); 
    }

    ~suffix_tree() {
        for(const node& n : pool) if(n.r != &global_end) delete n.r; 
    }

    //check if a given string occurs in the original string data
    //O(m); where m = size of string being processed 
    bool find(const string& str, int curr = 0, int edge = 0) const {
        if(edge == str.size()) return true; 

        int child = pool[curr].next[str[edge]]; 
        if(child == -1) return false; 

        int start = pool[child].l; 
        int end = *pool[child].r + 1; 

        for(int i = start; i < end && edge < str.size(); ++i) {
            if(str[edge++] != text[i]) return false; 
        }

        return find(str, child, edge); 
    }

    //answers the number of times a given string occurs in all suffixes 
    //O(m + k) time; where m = size of string and k is the number of edges
    //Or.... (m + k + (k - 1)) more specifically 
    int find_occurrences(const string& str, int curr = 0, int edge = 0) const {
        if(edge == str.size()) {
            cout << pool[curr].leaf_count << ' '; //this cuts off O(k)
            return count_leaves(curr); //O(k) 
        }

        int child = pool[curr].next[str[edge]]; 
        if(child == -1) return 0; 

        int start = pool[child].l; 
        int end = *pool[child].r + 1; 

        for(int i = start; i < end && edge < str.size(); ++i) {
            if(str[edge++] != text[i]) return 0; 
        }

        return find_occurrences(str, child, edge); 
    }

    //answers in which suffixes the query string appeared 
    //O(m + k)
    void report_occurrence_suffixes(const string& str, int curr = 0, int edge = 0) const {
        if(edge == str.size()) {
            print_occurrence_suffixes(curr); return; 
        }

        int child = pool[curr].next[str[edge]]; 
        if(child == -1) {
            cout << "No Offset found!\n"; return; 
        }

        int start = pool[child].l; 
        int end = *pool[child].r + 1; 

        for(int i = start; i < end && edge < str.size(); ++i) {
            if(str[edge++] != text[i]) {
                cout << "No Offset found!\n"; return; 
            }
        }

        report_occurrence_suffixes(str, child, edge); 
    }

    //------Debugging------
    void print_suffixes() const {
        string ret; 
        search_suffixes(0, ret); 
    }

    void print_suffix_links() const {
        for(int i = 1; i < pool.size(); ++i) {
            int start = pool[i].l; 
            int end = *pool[i].r + 1; 

            for(int j = start; j < end; ++j) cout << text[j]; 

            cout << "-----> "; 

            if(pool[i].suffix_link == 0) cout << "Root\n"; 
            else {
                int snode = pool[i].suffix_link; 
                start = pool[snode].l;
                end = *pool[snode].r + 1; 
                for(int j = start; j < end; ++j) cout << text[j]; 
                cout << '\n'; 
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> arr = {
        "mississippi$",
        "aabaaa$", 
        "abaaba$",
        "aaaaa$" 
    }; 

    for(const string& str : arr) {
        suffix_tree st(str); 

        st.print_suffixes(); 
        cout << '\n'; 
        st.print_suffix_links(); 
        cout << "----------------\n"; 
    }


    suffix_tree st("banana$"); //1 
    cout << st.find("nana") << endl; //1
    cout << st.find("banana") << endl; //1
    cout << st.find("a") << endl; //1
    cout << st.find("anana") << endl; //1
    cout << st.find("banang") << endl; //0
    cout << endl;


    suffix_tree st1("abaaba$"); 
    cout << st1.find_occurrences("aba$") << endl; // 1
    cout << st1.find_occurrences("a$") << endl;   // 1
    cout << st1.find_occurrences("aba") << endl;  // 2
    cout << st1.find_occurrences("a") << endl;    // 4
    cout << endl; 

    
    cout << "Offsets Found:\n"; 
    st1.report_occurrence_suffixes("aba"); cout << endl; 
    st1.report_occurrence_suffixes("a"); 
    return 0; 
}