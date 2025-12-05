#pragma once
#include "MyLinkingList.hpp"
#include <stdexcept>

template<typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
list<T>::list(const list& other) : head_(nullptr), tail_(nullptr), size_(0) {
    for (size_t i = 0; i < other.size_; i++) push_back(other[i]);
}

template<typename T>
list<T>::list(list&& other) noexcept : head_(std::move(other.head_)), tail_(other.tail_), size_(other.size_) {
    other.tail_ = nullptr;
    other.size_ = 0;
}

template<typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
    if (this != &other) {
        head_ = std::move(other.head_);
        tail_ = other.tail_;
        size_ = other.size_;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
list<T>::~list() {
    while (head_) head_ = std::move(head_->next_);
    tail_ = nullptr;
    size_ = 0;
}

template<typename T>
typename list<T>::Node* list<T>::get_node(size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    Node* curr = head_.get();
    for (size_t i = 0; i < index; i++) curr = curr->next_.get();
    return curr;
}

template<typename T>
void list<T>::push_back(const T& value) { push_back(T(value)); }

template<typename T>
void list<T>::push_back(T&& value) {
    auto new_node = std::make_unique<Node>(std::move(value));
    if (!head_) {
        tail_ = new_node.get();
        head_ = std::move(new_node);
    } else {
        new_node->prev_ = tail_;
        tail_->next_ = std::move(new_node);
        tail_ = tail_->next_.get();
    }
    ++size_;
}

template<typename T>
void list<T>::insert(size_t index, const T& value) { insert(index, T(value)); }

template<typename T>
void list<T>::insert(size_t index, T&& value) {
    if (index > size_) throw std::out_of_range("Out of range");
    if (index == size_) { push_back(std::move(value)); return; }
    auto new_node = std::make_unique<Node>(std::move(value));
    if (index == 0) {
        new_node->next_ = std::move(head_);
        new_node->next_->prev_ = new_node.get();
        head_ = std::move(new_node);
    } else {
        Node* next = get_node(index);
        Node* prev = next->prev_;
        new_node->next_ = std::move(prev->next_);
        new_node->prev_ = prev;
        next->prev_ = new_node.get();
        prev->next_ = std::move(new_node);
    }
    ++size_;
}

template<typename T>
void list<T>::erase(size_t index) {
    if (index >= size_) throw std::out_of_range("Out of range");
    if (index == 0) {
        if (size_ == 1) { head_.reset(); tail_ = nullptr; }
        else { head_ = std::move(head_->next_); head_->prev_ = nullptr; }
    } else if (index == size_ - 1) {
        tail_ = tail_->prev_;
        tail_->next_.reset();
    } else {
        Node* curr = get_node(index);
        Node* prev = curr->prev_;
        Node* next = curr->next_.get();
        prev->next_ = std::move(curr->next_);
        next->prev_ = prev;
    }
    --size_;
}

template<typename T>
size_t list<T>::size() const { return size_; }

template<typename T>
T& list<T>::operator[](size_t index) { return get_node(index)->data_; }
