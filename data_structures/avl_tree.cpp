#include <iostream>
#include <climits> 
using namespace std;

class AVL_tree {
private:
    
    struct node {
        int val; 
        int height; 
        node* left; 
        node* right; 

        explicit node(int data) : val(data), height(1), left(nullptr), right(nullptr) {}; 
    };

    node* root; 

    int height(const node* curr) const noexcept {
        return curr? curr->height : 0; 
    }

    int balance_factor(const node* curr) const noexcept {
        return curr? height(curr->left) - height(curr->right) : 0; 
    }

    node* right_rotate(node* curr) {
        node* child = curr->left; 
        node* child_right = child->right; 

        child->right = curr; 
        curr->left = child_right; 

        curr->height = 1 + max(height(curr->left), height(curr->right)); 
        child->height = 1 + max(height(child->left), height(child->right)); 

        return child; 
    }

    node* left_rotate(node* curr) {
        node* child = curr->right; 
        node* child_left = child->left; 

        child->left = curr; 
        curr->right = child_left; 

        curr->height = 1 + max(height(curr->left), height(curr->right)); 
        child->height = 1 + max(height(child->left), height(child->right)); 

        return child; 
    }

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

        if(val < curr->val) 
            curr->left = insert_node(curr->left, val); 

        else
            curr->right = insert_node(curr->right, val); 

        return rebalance(curr); 
    }

    int minValin_right_subtree(const node* curr) const {
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
                node* to_remove = curr; 
                curr = curr->left? curr->left : curr->right; 
                delete to_remove; 
                return curr; 
            }

            curr->val = minValin_right_subtree(curr->right); 
            curr->right = remove_node(curr->right, curr->val); 
        }

        return rebalance(curr); 
    }

    void inorder_traversal(const node* curr) const noexcept {
        if(!curr) return; 
        inorder_traversal(curr->left); 
        cout << "{v:" << curr->val << ", h:" << curr->height << "} "; 
        inorder_traversal(curr->right); 
    }
    
    void clear(node* curr) {
        if(!curr) return; 
        clear(curr->left); 
        clear(curr->right); 
        delete curr; 
    }

public:

    AVL_tree() : root(nullptr) {}; 

    ~AVL_tree() { clear(root); }

    AVL_tree(const &AVL_tree) = delete; 
    AVL_tree& operator=(const &AVL_tree) = delete; 

    AVL_tree(AVL_tree&&) noexcept = default; 
    AVL_tree& operator=(AVL_tree&&) noexcept = default; 

    void insert(int val) {
        root = insert_node(root, val); 
    }

    void remove(int val) {
        root = remove_node(root, val); 
    }

    //for debugging purpose only 
    void inorder() const noexcept {
        inorder_traversal(root); 
    }
}; 

int main() {
    int arr[] = {33, 22, 77, 15, 25, 55, 99, 11, 35, 66};

    AVL_tree tree; 
    for(int i : arr) 
        tree.insert(i); 

    tree.remove(99); 
    tree.remove(22); 
    tree.remove(33); 

    tree.inorder(); cout << endl; 
    return 0; 
}