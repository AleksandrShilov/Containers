#ifndef SRC_MY_NODESET_TREE_H_
#define SRC_MY_NODESET_TREE_H_

#include <iostream>

template <class Key>
class NodeSet {
  using value_type = Key;

 public:
  value_type value_;
  NodeSet<Key> *left_{nullptr};
  NodeSet<Key> *right_{nullptr};
  NodeSet<Key> *parent_{nullptr};

 public:
  explicit NodeSet<Key>(value_type val);
  NodeSet<Key>(const NodeSet &other);
  NodeSet<Key>(NodeSet &&other);
  ~NodeSet<Key>() = default;

 public:
  bool is_right_child();
  bool is_left_child();
  bool has_left();
  bool has_right();

 public:
  NodeSet<Key> &operator=(const NodeSet &other) = default;
  NodeSet<Key> &operator=(NodeSet &&other) = default;
};

template <typename Key>
NodeSet<Key>::NodeSet(value_type val)
    : value_(val), left_(nullptr), right_(nullptr), parent_(nullptr) {}

template <typename Key>
NodeSet<Key>::NodeSet(const NodeSet &other) {
  *this = other;
}

template <typename Key>
NodeSet<Key>::NodeSet(NodeSet &&other) {
  *this = std::move(other);
}

template <typename Key>
bool NodeSet<Key>::is_left_child() {
  return this == parent_->left_;
}

template <typename Key>
bool NodeSet<Key>::is_right_child() {
  return this == parent_->right_;
}

template <typename Key>
bool NodeSet<Key>::has_left() {
  return left_ != nullptr;
}

template <typename Key>
bool NodeSet<Key>::has_right() {
  return right_ != nullptr;
}

#endif  // SRC_MY_NODESET_TREE_H_
