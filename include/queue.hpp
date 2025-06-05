// File: include/queue.hpp
#pragma once

#include <iostream>
#include <utility>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename U>
        Node(U&& val) : data(std::forward<U>(val)), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t sz;

public:
    Queue() : head(nullptr), tail(nullptr), sz(0) {}
    
    Queue(Queue&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }
    
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            sz = other.sz;
            other.head = nullptr;
            other.tail = nullptr;
            other.sz = 0;
        }
        return *this;
    }
    
    template<typename U>
    void push(U&& value) {
        Node* newNode = new Node(std::forward<U>(value));
        if (tail) {
            tail->next = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++sz;
    }
    
    void pop() {
        if (head) {
            Node* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            --sz;
        }
    }
    
    T& front() {
        return head->data;
    }
    
    const T& front() const {
        return head->data;
    }
    
    T& back() {
        return tail->data;
    }
    
    const T& back() const {
        return tail->data;
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
        tail = nullptr;
        sz = 0;
    }
    
    void print() const {
        std::cout << "Queue (front to back): ";
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
    
    ~Queue() {
        clear();
    }
    
    // Delete copy constructor and copy assignment
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
};