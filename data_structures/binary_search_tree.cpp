#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

class BST {
private:

    struct node {
        int val; 
        unique_ptr<node> left; 
        unique_ptr<node> right; 

        explicit node(int data) : val(data) {}; 
    }; 

    unique_ptr<node> root; 

    // Builds a balanced BST from a sorted unique array in O(n).
    [[nodiscard]] 
    unique_ptr<node> build(const vector<int>& arr, int start, int end) {
        if(start > end) return nullptr; 
        
        int mid = (start + end) / 2; 

        auto ret = make_unique<node>(arr[mid]); 

        ret->left = build(arr, start, mid - 1); 
        ret->right = build(arr, mid + 1, end); 

        return ret; 
    }

public:

    explicit BST(const vector<int>& arr) {
        auto tmp = arr; //one deep copy 

        sort(tmp.begin(), tmp.end()); 
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end()); 

        root = build(tmp, 0, tmp.size() - 1); 
    }

    BST(const BST&) = delete; 
    BST& operator=(const BST&) = delete; 

    BST(BST&&) noexcept = default; 
    BST& operator=(BST&&) noexcept = default; 

    void insert(int val) {
        unique_ptr<node>* curr = &root; 

        while(*curr && val != (*curr)->val) {
            if(val < (*curr)->val) 
                curr = &((*curr)->left); 

            else curr = &((*curr)->right); 
        }

        if(!*curr) 
            *curr = make_unique<node>(val); 
    }

    void remove(int val) {
        unique_ptr<node>* curr = &root; 

        while(*curr && val != (*curr)->val) {
            if(val < (*curr)->val) 
                curr = &((*curr)->left); 

            else curr = &((*curr)->right); 
        }

        if(!*curr) return; 
        
        if(!((*curr)->left)) 
            *curr = move((*curr)->right); 

        else if(!((*curr)->right)) 
            *curr = move((*curr)->left); 

        else {
            unique_ptr<node>* successor = &((*curr)->right); 
            while((*successor)->left) 
                successor = &((*successor)->left); 

            (*curr)->val = (*successor)->val; 
            *successor = move(((*successor)->right)); 
        }
    }

    class iterator {
    private: 
        vector<const node*> stack; 

        void push_left(const node* curr) {
            while(curr) {
                stack.emplace_back(curr); 
                curr = curr->left.get(); 
            }
        }

    public:
        explicit iterator(const node* root) {
            push_left(root); 
        }

        const int& operator*() const {
            return stack.back()->val; 
        }

        iterator& operator++() {
            const node* curr = stack.back(); 
            stack.pop_back(); 
            push_left(curr->right.get()); 

            return *this; 
        }

        iterator operator++(int) {
            iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }

        bool operator==(const iterator& other) const {
            if(stack.empty() && other.stack.empty()) 
                return true; 

            if(stack.empty() || other.stack.empty()) 
                return false; 

            return stack.back() == other.stack.back(); 
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other); 
        }
    }; 

    iterator begin() const {
        return iterator(root.get()); 
    }

    iterator end() const {
        return iterator(nullptr); 
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 

    vector<int> arr = {6, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 1}; 

    BST tree(arr); 
    for(const int& i : tree) cout << i << ' '; 
    cout << endl; 
    
    vector<int> arr1 = {-1, 0, 7, 8, 9, 5}; 
    for(int i : arr1) 
        tree.insert(i); 

    for(int i : tree) cout << i << ' '; //sorted order verified: -1 0 1 2 3 4 5 6 7 8 9
    cout << endl; 

    for(int i : arr1) 
        tree.remove(i); 

    for(int i : tree) cout << i << ' '; //1 2 3 4 6
    cout << endl; 

    for(int i : arr) 
        tree.remove(i); 

    tree.remove(7); //remove a non-existing node 
    
    for(int i : tree) cout << i << ' '; 
    return 0; 
}