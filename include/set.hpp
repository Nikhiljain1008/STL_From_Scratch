// File: include/set.hpp
#pragma once

#include <iostream>
#include <utility>

template <typename T>
class Set {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;
        
        template<typename U>
        Node(U&& val) : data(std::forward<U>(val)), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    size_t sz;
    
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    
    template<typename U>
    Node* insert(Node* node, U&& value) {
        if (!node) {
            ++sz;
            return new Node(std::forward<U>(value));
        }
        
        if (value < node->data) {
            node->left = insert(node->left, std::forward<U>(value));
        } else if (value > node->data) {
            node->right = insert(node->right, std::forward<U>(value));
        } else {
            return node; // Duplicate, don't insert
        }
        
        updateHeight(node);
        int balance = getBalance(node);
        
        if (balance > 1 && value < node->left->data)
            return rotateRight(node);
        if (balance < -1 && value > node->right->data)
            return rotateLeft(node);
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }
    
    Node* remove(Node* node, const T& value) {
        if (!node) return node;
        
        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            --sz;
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                ++sz; // Compensate for the decrement above
                node->right = remove(node->right, temp->data);
            }
        }
        
        if (!node) return node;
        
        updateHeight(node);
        int balance = getBalance(node);
        
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    bool find(Node* node, const T& value) const {
        if (!node) return false;
        if (node->data == value) return true;
        return value < node->data ? find(node->left, value) : find(node->right, value);
    }
    
    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }
    }
    
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    Set() : root(nullptr), sz(0) {}
    
    Set(Set&& other) noexcept : root(other.root), sz(other.sz) {
        other.root = nullptr;
        other.sz = 0;
    }
    
    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            destroyTree(root);
            root = other.root;
            sz = other.sz;
            other.root = nullptr;
            other.sz = 0;
        }
        return *this;
    }
    
    template<typename U>
    void insert(U&& value) {
        root = insert(root, std::forward<U>(value));
    }
    
    void erase(const T& value) {
        root = remove(root, value);
    }
    
    bool contains(const T& value) const {
        return find(root, value);
    }
    
    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }
    
    void print() const {
        std::cout << "Set: { ";
        inorder(root);
        std::cout << "}\n";
    }
    
    ~Set() {
        destroyTree(root);
    }
    
    // Delete copy constructor and copy assignment
    Set(const Set&) = delete;
    Set& operator=(const Set&) = delete;
};