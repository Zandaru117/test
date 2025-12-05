#pragma once
#include <memory>
#include <cstddef>
#include <utility>

template<typename T>
class vector {
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
public:
    vector();
    vector(const vector& other);
    vector(vector&& other) noexcept;
    vector& operator=(vector&& other) noexcept;
    ~vector() = default;

    void push_back(const T& value);
    void push_back(T&& value);
    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);
    void erase(size_t index);
    size_t size() const;
    T& operator[](size_t index);

    void resize(size_t new_capacity);

    // Iterator
    class iterator {
        T* ptr_;
    public:
        iterator(T* p) : ptr_(p) {}
        T& operator*() { return *ptr_; }
        iterator& operator++() { ++ptr_; return *this; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
    };

    iterator begin() { return iterator(data_.get()); }
    iterator end() { return iterator(data_.get() + size_); }
};
