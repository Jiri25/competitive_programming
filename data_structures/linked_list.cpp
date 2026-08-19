#include <iostream>
#include <utility> 
#include <stdexcept> 

template <typename T> 
class ll {
private:
    struct base_node {
        base_node* prev; 
        base_node* next; 

        base_node() : prev(this), next(this) {}; 
    }; 

    struct node : base_node {
        T data; 

        template <typename U> 
        explicit node(U&& val) : base_node(), data(std::forward<U>(val)) {}; 
    }; 

    base_node sentinel; 
    size_t m_size = 0; 

    void clear() noexcept {
        base_node* curr = sentinel.next; 
        base_node* next = nullptr; 
        while(curr != &sentinel) {
            next = curr->next; 
            delete static_cast<node*>(curr); 
            curr = next; 
        }

        sentinel.next = &sentinel; 
        sentinel.prev = &sentinel; 
        m_size = 0; 
    }

public: 

    class iterator {
    private:    
        base_node* curr; 

    public:
        explicit iterator(base_node* bn) : curr(bn) {}; 

        T& operator*() const noexcept {
            return static_cast<node*>(curr)->data; 
        }

        T* operator->() const noexcept {
            return &static_cast<node*>(curr)->data; 
        }

        iterator& operator++() noexcept {
            curr = curr->next; 
            return *this; 
        }

        iterator operator++(int) noexcept {
            iterator ret = *this; 
            ++(*this); 
            return ret; 
        }

        iterator& operator--() noexcept {
            curr = curr->prev; 
            return *this; 
        }

        iterator operator--(int) noexcept {
            iterator ret = *this; 
            --(*this); 
            return ret; 
        }

        bool operator==(const iterator& other) const noexcept {
            return curr == other.curr; 
        }

        bool operator!=(const iterator& other) const noexcept {
            return curr != other.curr; 
        }
    }; 

    class reverse_iterator {
    private:
        base_node* curr; 
        
    public:
        reverse_iterator(base_node* bn) : curr(bn) {}; 

        T& operator*() const noexcept {
            return static_cast<node*>(curr)->data; 
        }

        T* operator->() const noexcept {
            return &static_cast<node*>(curr)->data; 
        }

        reverse_iterator& operator++() noexcept {
            curr = curr->prev; 
            return *this; 
        }

        reverse_iterator operator++(int) noexcept {
            reverse_iterator ret = *this; 
            ++(*this); 
            return ret; 
        }

        reverse_iterator& operator--() noexcept {
            curr = curr->next; 
            return *this; 
        }

        reverse_iterator operator--(int) noexcept {
            reverse_iterator ret = *this; 
            --(*this); 
            return ret; 
        }

        bool operator==(const reverse_iterator& other) const noexcept {
            return curr == other.curr; 
        }

        bool operator!=(const reverse_iterator& other) const noexcept {
            return curr != other.curr; 
        }
    }; 

    ll() = default;
    ~ll() { clear(); }

    ll(const ll& other) = delete; 
    ll& operator=(const ll& other) = delete; 

    ll(ll&& other) noexcept : m_size(other.m_size) {
        if(other.m_size != 0) {
            sentinel.next = other.sentinel.next; 
            sentinel.prev = other.sentinel.prev; 

            sentinel.next->prev = &sentinel; 
            sentinel.prev->next = &sentinel; 

            other.sentinel.next = &other.sentinel; 
            other.sentinel.prev = &other.sentinel; 
            other.m_size = 0; 
        }
    }

    ll& operator=(ll&& other) noexcept {
        if(this != &other) {
            clear(); 
            if(other.m_size != 0) {
                sentinel.next = other.sentinel.next; 
                sentinel.prev = other.sentinel.prev; 

                sentinel.next->prev = &sentinel; 
                sentinel.prev->next = &sentinel; 

                m_size = other.m_size; 

                other.sentinel.next = &other.sentinel; 
                other.sentinel.prev = &other.sentinel; 
                other.m_size = 0; 
            }
        }
    }

    template <typename U> 
    void insert(U&& val) {
        node* new_node = new node(std::forward<U>(val)); 

        sentinel.prev->next = new_node; 
        new_node->prev = sentinel.prev; 

        new_node->next = &sentinel; 
        sentinel.prev = new_node; 
        
        ++m_size; 
    }

    void remove_by_index(size_t index) {
        if(index >= m_size) 
            throw std::out_of_range("ll::remove(): index out of bounds!"); 

        base_node* curr = &sentinel; 
        for(size_t i = 0; i <= index; ++i) 
            curr = curr->next; 
        
        curr->prev->next = curr->next; 
        curr->next->prev = curr->prev; 
        delete static_cast<node*>(curr); 

        --m_size; 
    }

    void remove_by_value(const T& data) {
        base_node* curr = sentinel.next; 
        while(curr != &sentinel && static_cast<node*>(curr)->data != data)
            curr = curr->next; 

        if(curr == &sentinel) return; 

        curr->prev->next = curr->next; 
        curr->next->prev = curr->prev; 
        delete static_cast<node*>(curr); 
    
        --m_size; 
    }

    size_t size() const noexcept {
        return m_size; 
    }

    void print() const noexcept {
        const base_node* curr = sentinel.next; 
        while(curr != &sentinel) {
            std::cout << static_cast<const node*>(curr)->data << ' '; 
            curr = curr->next; 
        }
    }

    iterator begin() noexcept {
        return iterator(sentinel.next); 
    }

    iterator end() noexcept {
        return iterator(&sentinel); 
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(sentinel.prev); 
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(&sentinel); 
    }
}; 

int main() {
    ll<int> list; 
    for(int i = 1; i <= 10; ++i)
        list.insert(i);
        
    for(int i = 0; i <= 20; ++i) 
        list.remove_by_value(i); 

    list.insert(8); 
    list.insert(17);
    list.insert(10); 
    list.insert(25);  

    ll<int> list1 = std::move(list); 

    for(auto it = list1.begin(); it != list1.end(); ++it) 
        std::cout << *it << ' '; 

    std::cout << std::endl; 
    
    for(auto it = list1.rbegin(); it != list1.rend(); ++it) 
        std::cout << *it << ' '; 

    std::cout << std::endl; 
    std::cout << "Size: " << list1.size() << std::endl; 
    std::cout << "Old Size: " << list.size() << std::endl; 
    return 0; 
}