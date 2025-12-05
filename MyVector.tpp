#pragma once
#include "MyVector.hpp"
#include <stdexcept>

template<typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template<typename T>
vector<T>::vector(const vector& other) : data_(nullptr), size_(0), capacity_(0) {
    resize(other.capacity_);
    for (size_t i = 0; i < other.size_; i++)
        data_[i] = other.data_[i];
    size_ = other.size_;
}

template<typename T>
vector<T>::vector(vector&& other) noexcept : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
void vector<T>::resize(size_t new_capacity) {
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
    for (size_t i = 0; i < size_; i++)
        new_data[i] = std::move(data_[i]);
    data_ = std::move(new_data);
    capacity_ = new_capacity;
}

template<typename T>
void vector<T>::push_back(const T& value) {
    if (size_ >= capacity_) {
        size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
        resize(new_cap);
    }
    data_[size_++] = value;
}

template<typename T>
void vector<T>::push_back(T&& value) {
    if (size_ >= capacity_) {
        size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
        resize(new_cap);
    }
    data_[size_++] = std::move(value);
}

template<typename T>
void vector<T>::insert(size_t index, const T& value) {
    if (index > size_) throw std::out_of_range("Out of range");
    if (size_ >= capacity_) resize((capacity_ == 0) ? 1 : capacity_ * 2);

    for (size_t i = size_; i > index; --i)
        data_[i] = std::move(data_[i - 1]);

    data_[index] = value;
    ++size_;
}

template<typename T>
void vector<T>::insert(size_t index, T&& value) {
    if (index > size_) throw std::out_of_range("Out of range");
    if (size_ >= capacity_) resize((capacity_ == 0) ? 1 : capacity_ * 2);

    for (size_t i = size_; i > index; --i)
        data_[i] = std::move(data_[i - 1]);

    data_[index] = std::move(value);
    ++size_;
}

template<typename T>
void vector<T>::erase(size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    for (size_t i = index; i < size_ - 1; i++)
        data_[i] = std::move(data_[i + 1]);
    --size_;
}

template<typename T>
size_t vector<T>::size() const { return size_; }

template<typename T>
T& vector<T>::operator[](size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    return data_[index];
}
