#include <iostream>
#include <vector> 
#include <climits> 
#include <algorithm> 
using namespace std;

//MAX Segment Tree 
class segment_tree {
private:

    vector<int> tree; 
    int padded_size; 

    int next_pow_of_two(int n) const {
        if(n <= 1) return 1; 
        int ret = 1 << (32 - __builtin_clz(n) - 1); 
        return ret == n? ret : ret << 1; 
    }

    //O(N)
    void build(const vector<int>& arr) {
        int index = padded_size; 
        copy(arr.begin(), arr.end(), tree.begin() + padded_size); 

        for(int i = padded_size - 1; i > 0; --i) 
            tree[i] = max(tree[i << 1], tree[i << 1 | 1]); 
    }

public:

    segment_tree(const vector<int>& arr) {
        int n = arr.size(); 
        padded_size = next_pow_of_two(n); 
        tree.resize(padded_size * 2, INT_MIN);

        build(arr); 
    }

    //O(log N)
    void update(int index, int value) {
        index += padded_size; 
        tree[index] = value; 
        while(index > 1) {
            index /= 2; 
            tree[index] = max(tree[index << 1], tree[index << 1 | 1]); 
        }
    }

    //O(log N) {from, to(inclusive)}  
    int range_query(int from, int to) const {
        from += padded_size;
        to += padded_size; 

        int ret = INT_MIN; 
        while(from <= to) {
            if((from & 1) == 1) {
                ret = max(tree[from], ret); 
                ++from; 
            }

            if((to & 1) != 1) {
                ret = max(tree[to], ret); 
                --to; 
            }

            from /= 2; 
            to /= 2; 
        }
        return ret; 
    }

    //debugging
    void print() const {
        for(int i : tree) cout << i << ' '; 
    }
}; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    int n; 
    cin >> n;
    vector<int> arr(n); 
    for(int i = 0; i < n; ++i) cin >> arr[i]; 

    segment_tree st(arr); 
    st.print(); 
    cout << endl; 

    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            cout << '{' << i << ", " << j << "}: " << st.range_query(i, j) << endl; //O(log n) 
        }
    }

    cout << "-----------------" << endl; 

    st.update(0, 5); 
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            cout << '{' << i << ", " << j << "}: " << st.range_query(i, j) << endl; //O(log n) 
        }
    }

    st.print(); 
    return 0; 
}