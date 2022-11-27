#ifndef SRC_MY_NODE_TREE_H_
#define SRC_MY_NODE_TREE_H_

#include <iostream>

template <class Key, class Value>
class Node {
  using value_type = std::pair<Key, Value>;

 public:
  value_type value_;
  Node<Key, Value> *left_{nullptr};
  Node<Key, Value> *right_{nullptr};
  Node<Key, Value> *parent_{nullptr};

 public:
  explicit Node<Key, Value>(value_type val);
  Node<Key, Value>(const Node &other);
  Node<Key, Value>(Node &&other);
  ~Node<Key, Value>() = default;

 public:
  bool is_right_child();
  bool is_left_child();
  bool has_left();
  bool has_right();

 public:
  Node<Key, Value> &operator=(const Node &other) = default;
  Node<Key, Value> &operator=(Node &&other) = default;
};

template <typename Key, typename Value>
Node<Key, Value>::Node(value_type val)
    : value_(val), left_(nullptr), right_(nullptr), parent_(nullptr) {}

template <typename Key, typename Value>
Node<Key, Value>::Node(const Node &other) {
  *this = other;
}

template <typename Key, typename Value>
Node<Key, Value>::Node(Node &&other) {
  *this = std::move(other);
}

template <typename Key, typename Value>
bool Node<Key, Value>::is_left_child() {
  return this == parent_->left_;
}

template <typename Key, typename Value>
bool Node<Key, Value>::is_right_child() {
  return this == parent_->right_;
}

template <typename Key, typename Value>
bool Node<Key, Value>::has_left() {
  return left_ != nullptr;
}

template <typename Key, typename Value>
bool Node<Key, Value>::has_right() {
  return right_ != nullptr;
}

#endif  // SRC_MY_NODE_TREE_H_
