// File: include/vector.hpp
#pragma once

#include <cstddef> // for size_t
#include <new>      // for placement new
#include <utility>  // for std::move, std::forward
#include <iostream>

// Base interface for polymorphism
class IContainer {
public:
    virtual void print() const = 0;
    virtual ~IContainer() = default;
};

template <typename T>
class Vector : public IContainer {
private:
    T* data;
    size_t sz;
    size_t cap;

    void reallocate(size_t new_cap) {
        T* new_data = reinterpret_cast<T*>(::operator new(sizeof(T) * new_cap));
        for (size_t i = 0; i < sz; ++i) {
            new (new_data + i) T(std::move(data[i]));
            data[i].~T();
        }
        ::operator delete(data);
        data = new_data;
        cap = new_cap;
    }

public:
    Vector() : data(nullptr), sz(0), cap(0) {}

    // Move constructor
    Vector(Vector&& other) noexcept : data(other.data), sz(other.sz), cap(other.cap) {
        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // Move assignment
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            ::operator delete(data);
            data = other.data;
            sz = other.sz;
            cap = other.cap;
            other.data = nullptr;
            other.sz = 0;
            other.cap = 0;
        }
        return *this;
    }

    // Perfect forwarding push_back - handles all cases including conversions
    template<typename U>
    void push_back(U&& val) {
        if (sz == cap) reallocate(cap ? cap * 2 : 1);
        new (data + sz) T(std::forward<U>(val));
        ++sz;
    }

    void pop_back() {
        if (sz > 0) {
            --sz;
            data[sz].~T();
        }
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    size_t size() const { return sz; }
    size_t capacity() const { return cap; }

    void clear() {
        for (size_t i = 0; i < sz; ++i)
            data[i].~T();
        sz = 0;
    }

    void print() const override {
        std::cout << "[ ";
        for (size_t i = 0; i < sz; ++i)
            std::cout << data[i] << " ";
        std::cout << "]\n";
    }

    ~Vector() {
        clear();
        ::operator delete(data);
    }
};