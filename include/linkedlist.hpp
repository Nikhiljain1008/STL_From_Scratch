// File: include/linkedlist.hpp
#pragma once

#include <iostream>
#include <utility>

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        template<typename U>
        Node(U&& val, Node* n = nullptr) : data(std::forward<U>(val)), next(n) {}
    };
    
    Node* head;
    Node* tail;
    size_t sz;

public:
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}
    
    LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), sz(other.sz) {
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0;
    }
    
    LinkedList& operator=(LinkedList&& other) noexcept {
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
    void push_front(U&& value) {
        Node* newNode = new Node(std::forward<U>(value), head);
        head = newNode;
        if (!tail) tail = head;
        ++sz;
    }
    
    template<typename U>
    void push_back(U&& value) {
        Node* newNode = new Node(std::forward<U>(value));
        if (tail) {
            tail->next = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++sz;
    }
    
    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            --sz;
        }
    }
    
    void pop_back() {
        if (!head) return;
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        --sz;
    }
    
    template<typename U>
    void insert(size_t index, U&& value) {
        if (index == 0) {
            push_front(std::forward<U>(value));
            return;
        }
        if (index >= sz) {
            push_back(std::forward<U>(value));
            return;
        }
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* newNode = new Node(std::forward<U>(value), current->next);
        current->next = newNode;
        ++sz;
    }
    
    void erase(size_t index) {
        if (index >= sz) return;
        
        if (index == 0) {
            pop_front();
            return;
        }
        
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        
        Node* toDelete = current->next;
        current->next = toDelete->next;
        if (toDelete == tail) tail = current;
        delete toDelete;
        --sz;
    }
    
    T& operator[](size_t index) {
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    const T& operator[](size_t index) const {
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    T& front() { return head->data; }
    const T& front() const { return head->data; }
    T& back() { return tail->data; }
    const T& back() const { return tail->data; }
    
    bool empty() const { return head == nullptr; }
    size_t size() const { return sz; }
    
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
        std::cout << "LinkedList: [ ";
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "]\n";
    }
    
    ~LinkedList() {
        clear();
    }
    
    // Delete copy constructor and copy assignment
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;
};