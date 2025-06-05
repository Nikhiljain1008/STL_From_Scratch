// File: include/map.hpp
#pragma once

#include <iostream>
#include <utility>

template <typename K, typename V>
class Map {
private:
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;
        
        template<typename KType, typename VType>
        Node(KType&& k, VType&& v) 
            : key(std::forward<KType>(k)), value(std::forward<VType>(v)), 
              left(nullptr), right(nullptr), height(1) {}
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
    
    template<typename KType, typename VType>
    Node* insert(Node* node, KType&& key, VType&& value) {
        if (!node) {
            ++sz;
            return new Node(std::forward<KType>(key), std::forward<VType>(value));
        }
        
        if (key < node->key) {
            node->left = insert(node->left, std::forward<KType>(key), std::forward<VType>(value));
        } else if (key > node->key) {
            node->right = insert(node->right, std::forward<KType>(key), std::forward<VType>(value));
        } else {
            node->value = std::forward<VType>(value);
            return node;
        }
        
        updateHeight(node);
        int balance = getBalance(node);
        
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }
    
    Node* remove(Node* node, const K& key) {
        if (!node) return node;
        
        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
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
                node->key = temp->key;
                node->value = temp->value;
                ++sz; // Compensate for the decrement above
                node->right = remove(node->right, temp->key);
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
    
    Node* find(Node* node, const K& key) const {
        if (!node || node->key == key) return node;
        return key < node->key ? find(node->left, key) : find(node->right, key);
    }
    
    void inorder(Node* node) const {
        if (node) {
            inorder(node->left);
            std::cout << "{" << node->key << ": " << node->value << "} ";
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
    Map() : root(nullptr), sz(0) {}
    
    Map(Map&& other) noexcept : root(other.root), sz(other.sz) {
        other.root = nullptr;
        other.sz = 0;
    }
    
    Map& operator=(Map&& other) noexcept {
        if (this != &other) {
            destroyTree(root);
            root = other.root;
            sz = other.sz;
            other.root = nullptr;
            other.sz = 0;
        }
        return *this;
    }
    
    template<typename KType, typename VType>
    void insert(KType&& key, VType&& value) {
        root = insert(root, std::forward<KType>(key), std::forward<VType>(value));
    }
    
    void erase(const K& key) {
        root = remove(root, key);
    }
    
    V* find(const K& key) {
        Node* node = find(root, key);
        return node ? &(node->value) : nullptr;
    }
    
    const V* find(const K& key) const {
        Node* node = find(root, key);
        return node ? &(node->value) : nullptr;
    }
    
    V& operator[](const K& key) {
        Node* node = find(root, key);
        if (!node) {
            Node*& ref = root;
            insert(key, V{});
            return find(ref, key)->value;

        }
        return node->value;
    }
    
    size_t size() const { return sz; }
    bool empty() const { return sz == 0; }
    
    void print() const {
        std::cout << "Map: ";
        inorder(root);
        std::cout << "\n";
    }
    
    ~Map() {
        destroyTree(root);
    }
    
    // Delete copy constructor and copy assignment
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;
};