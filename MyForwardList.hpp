#pragma once
#include <memory>
#include <cstddef>
#include <utility>

template<typename T>
class Flist {
    struct Node {
        T data_;
        std::unique_ptr<Node> next_;
        Node(const T& v) : data_(v), next_(nullptr) {}
        Node(T&& v) : data_(std::move(v)), next_(nullptr) {}
    };
    std::unique_ptr<Node> head_;
    size_t size_;
public:
    Flist();
    Flist(const Flist& other);
    Flist(Flist&& other) noexcept;
    Flist& operator=(Flist&& other) noexcept;
    ~Flist() = default;

    void push_back(const T& value);
    void push_back(T&& value);
    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);
    void erase(size_t index);
    size_t size() const;
    T& operator[](size_t index);

    class iterator {
        Node* node_;
    public:
        iterator(Node* n) : node_(n) {}
        T& operator*() { return node_->data_; }
        iterator& operator++() { node_ = node_->next_.get(); return *this; }
        bool operator!=(const iterator& other) const { return node_ != other.node_; }
    };

    iterator begin() { return iterator(head_.get()); }
    iterator end() { return iterator(nullptr); }

private:
    Node* get_node(size_t index);
};
