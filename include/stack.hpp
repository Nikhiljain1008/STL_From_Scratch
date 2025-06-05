// File: include/stack.hpp
#pragma once

#include <iostream>
#include <utility>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename U>
        Node(U&& val, Node* n = nullptr) : data(std::forward<U>(val)), next(n) {}
    };
    
    Node* head;
    size_t sz;

public:
    Stack() : head(nullptr), sz(0) {}
    
    Stack(Stack&& other) noexcept : head(other.head), sz(other.sz) {
        other.head = nullptr;
        other.sz = 0;
    }
    
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            sz = other.sz;
            other.head = nullptr;
            other.sz = 0;
        }
        return *this;
    }
    
    template<typename U>
    void push(U&& value) {
        head = new Node(std::forward<U>(value), head);
        ++sz;
    }
    
    void pop() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
            --sz;
        }
    }
    
    T& top() {
        return head->data;
    }
    
    const T& top() const {
        return head->data;
    }
    
    bool empty() const {
        return head == nullptr;
    }
    
    size_t size() const {
        return sz;
    }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        sz = 0;
    }
    
    void print() const {
        std::cout << "Stack (top to bottom): ";
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
    
    ~Stack() {
        clear();
    }
    
    // Delete copy constructor and copy assignment
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
};