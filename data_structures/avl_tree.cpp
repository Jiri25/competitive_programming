#include <iostream>
#include <climits>
using namespace std;

class AVL_tree {
private: 

    struct node {
        int val; 
        int height; 
        node* parent; 
        node* left; 
        node* right; 

        explicit node(int data) : val(data), height(1), 
            parent(nullptr), left(nullptr), right(nullptr) {}; 
    };

    node* root; 

    int height(const node* curr) const noexcept {
        return curr? curr->height : 0; 
    }

    int balance_factor(const node* curr) const noexcept {
        return curr? height(curr->left) - height(curr->right) : 0; 
    }

    [[nodiscard]]
    node* right_rotate(node* curr) {
        node* child = curr->left; 
        node* child_right = child->right; 

        child->right = curr; 
        curr->left = child_right;  

        child->parent = curr->parent; 
        curr->parent = child;
        if(child_right)
            child_right->parent = curr; 

        curr->height = 1 + max(height(curr->left), height(curr->right)); 
        child->height = 1 + max(height(child->left), height(child->right)); 

        return child; 
    }

    [[nodiscard]]
    node* left_rotate(node* curr) {
        node* child = curr->right; 
        node* child_left = child->left; 

        child->left = curr; 
        curr->right = child_left; 
        
        child->parent = curr->parent; 
        curr->parent = child; 
        if(child_left) 
            child_left->parent = curr; 

        curr->height = 1 + max(height(curr->left), height(curr->right)); 
        child->height = 1 + max(height(child->left), height(child->right)); 

        return child; 
    }

    [[nodiscard]]
    node* rebalance(node* curr) {
        curr->height = 1 + max(height(curr->left), height(curr->right)); 
        int bf = balance_factor(curr); 

        if(bf > 1) {
            if(balance_factor(curr->left) < 0) 
                curr->left = left_rotate(curr->left); 

            return right_rotate(curr); 
        }

        if(bf < -1) {
            if(balance_factor(curr->right) > 0) 
                curr->right = right_rotate(curr->right); 

            return left_rotate(curr); 
        }

        return curr; 
    }

    [[nodiscard]]
    node* insert_node(node* curr, int val) {
        if(!curr) return new node(val); 

        if(val < curr->val) {
            curr->left = insert_node(curr->left, val); 
            if(curr->left) 
                curr->left->parent = curr; 
        }

        else {
            curr->right = insert_node(curr->right, val); 
            if(curr->right) 
                curr->right->parent = curr; 
        }

        return rebalance(curr); 
    }

    int minValin_right_subtree(const node* curr) const noexcept {
        while(curr->left) 
            curr = curr->left; 

        return curr->val; 
    }

    [[nodiscard]]
    node* remove_node(node* curr, int val) {
        if(!curr) return nullptr; 

        if(val < curr->val) 
            curr->left = remove_node(curr->left, val); 
        
        else if(val > curr->val) 
            curr->right = remove_node(curr->right, val);         

        else {

            if(!curr->left || !curr->right) {
                node* next = curr->left? curr->left : curr->right; 
                if(next) 
                    next->parent = curr->parent; 

                delete curr; 
                return next; 
            }

            curr->val = minValin_right_subtree(curr->right); 
            curr->right = remove_node(curr->right, curr->val); 
        }

        return rebalance(curr); 
    }

    void inorder_traversal(const node* curr) const noexcept {
        if(!curr) return; 
        inorder_traversal(curr->left); 
        
        cout << "{v:" << curr->val 
             << ", h:" << curr->height 
             << ", p:" << (curr->parent ? to_string(curr->parent->val) : "null") 
             << "} ";

        inorder_traversal(curr->right);  
    }

    void clear(node* curr) noexcept {
        if(!curr) return; 
        clear(curr->left); 
        clear(curr->right); 
        delete curr; 
    }

public:

    class iterator {
    private:
        const node* curr; 
        const AVL_tree* owner; 

        const node* minimum(const node* curr) const noexcept {
            if(!curr) return nullptr; 

            while(curr->left) 
                curr = curr->left; 
            return curr; 
        }

        const node* maximum(const node* curr) const noexcept {
            if(!curr) return nullptr; 

            while(curr->right) 
                curr = curr->right; 
            return curr; 
        }

    public:
        using iterator_category = bidirectional_iterator_tag; 
        using value_type = int; 
        using difference_type = ptrdiff_t; 
        using pointer = const int*; 
        using reference = const int&; 

        iterator(const node* root, const AVL_tree* ow) noexcept 
        : curr(minimum(root)), owner(ow) {}; 

        reference operator*() const noexcept {
            return curr->val; 
        }

        pointer operator->() const noexcept {
            return &curr->val;  
        }

        iterator& operator++() noexcept {
            if(curr->right) {
                curr = curr->right; 
                while(curr->left) 
                    curr = curr->left; 

                return *this; 
            }

            const node* parent = curr->parent; 
            while(parent && curr == parent->right) {
                curr = parent; 
                parent = parent->parent; 
            }

            curr = parent; 
            return *this; 
        }

        iterator operator++(int) noexcept {
            iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }

        iterator& operator--() noexcept {
            if(!curr) {
                curr = maximum(owner->root); 
                return *this; 
            }

            if(curr->left) {
                curr = curr->left; 
                while(curr->right) 
                    curr = curr->right; 
                return *this; 
            }

            const node* parent = curr->parent; 
            while(parent && curr == parent->left) {
                curr = parent; 
                parent = parent->parent; 
            }
            curr = parent; 
            return *this; 
        }

        iterator operator--(int) noexcept {
            iterator tmp = *this; 
            --(*this); 
            return tmp; 
        }

        bool operator==(const iterator& other) const noexcept {
            return this->curr == other.curr; 
        }

        bool operator!=(const iterator& other) const noexcept {
            return this->curr != other.curr; 
        }
    }; 

    iterator begin() const noexcept {
        return iterator(root, this); 
    }

    iterator end() const noexcept {
        return iterator(nullptr, this); 
    }

    AVL_tree() noexcept : root(nullptr) {}; 

    AVL_tree(const AVL_tree&) = delete; 

    AVL_tree& operator=(const AVL_tree&) = delete; 

    AVL_tree(AVL_tree&& other) noexcept : root(other.root) {
        other.root = nullptr; 
    }

    AVL_tree& operator=(AVL_tree&& other) noexcept {
        if(this != &other) {
            clear(root); 
            root = other.root; 
            other.root = nullptr; 
        }
        return *this; 
    }

    ~AVL_tree() { clear(root); }; 

    //allows duplicate insertion
    void insert(int val) { 
        root = insert_node(root, val); 
    }

    void remove(int val) {
        root = remove_node(root, val); 
    }

    //debugging and visualization 
    void in_order() const noexcept {
        inorder_traversal(root); 
    }
};

int main() {
    int arr[] = {33, 22, 77, 15, 25, 55, 99, 11, 35, 66}; 

    AVL_tree tmp; 
    for(int i : arr)
        tmp.insert(i); 

    tmp = move(tmp); //nothing happens 

    AVL_tree tree; 
    tree = move(tmp); //move assignment 

    tree.remove(99); 
    tree.remove(22); 
    tree.remove(33); 
    tree.remove(35); 
    tree.remove(66); 
    tree.remove(77); 

    tree.in_order(); cout << endl; 

    for(int i : tree) 
        cout << i << ' '; 
    cout << endl; 

    for(auto it = tree.end(); it != tree.begin();) {
        --it; 
        cout << *it << ' '; 
    }
    cout << endl; 

    auto it = tree.begin(); 
    cout << *it << ' ' << *(++it) << endl; 
    cout << *it << ' ' << *(--it) << endl; 
    
    return 0; 
}