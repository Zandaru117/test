#pragma once
#include "MyForwardList.hpp"
#include <stdexcept>

template<typename T>
Flist<T>::Flist() : head_(nullptr), size_(0) {}

template<typename T>
Flist<T>::Flist(const Flist& other) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < other.size_; i++)
        push_back(other[i]);
}

template<typename T>
Flist<T>::Flist(Flist&& other) noexcept : head_(std::move(other.head_)), size_(other.size_) {
    other.size_ = 0;
}

template<typename T>
Flist<T>& Flist<T>::operator=(Flist&& other) noexcept {
    if (this != &other) {
        head_ = std::move(other.head_);
        size_ = other.size_;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
typename Flist<T>::Node* Flist<T>::get_node(size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    Node* curr = head_.get();
    for (size_t i = 0; i < index; i++)
        curr = curr->next_.get();
    return curr;
}

template<typename T>
void Flist<T>::push_back(const T& value) { push_back(T(value)); }

template<typename T>
void Flist<T>::push_back(T&& value) {
    auto new_node = std::make_unique<Node>(std::move(value));
    if (!head_) head_ = std::move(new_node);
    else {
        Node* curr = head_.get();
        while (curr->next_) curr = curr->next_.get();
        curr->next_ = std::move(new_node);
    }
    ++size_;
}

template<typename T>
void Flist<T>::insert(size_t index, const T& value) { insert(index, T(value)); }

template<typename T>
void Flist<T>::insert(size_t index, T&& value) {
    if (index > size_) throw std::out_of_range("Out of range");
    auto new_node = std::make_unique<Node>(std::move(value));
    if (index == 0) {
        new_node->next_ = std::move(head_);
        head_ = std::move(new_node);
    } else {
        Node* prev = get_node(index - 1);
        new_node->next_ = std::move(prev->next_);
        prev->next_ = std::move(new_node);
    }
    ++size_;
}

template<typename T>
void Flist<T>::erase(size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    if (index == 0) head_ = std::move(head_->next_);
    else {
        Node* prev = get_node(index - 1);
        prev->next_ = std::move(prev->next_->next_);
    }
    --size_;
}

template<typename T>
size_t Flist<T>::size() const { return size_; }

template<typename T>
T& Flist<T>::operator[](size_t index) { return get_node(index)->data_; }
