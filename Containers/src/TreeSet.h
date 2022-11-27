#ifndef SRC_MY_TREESET_H_
#define SRC_MY_TREESET_H_

#include <iostream>
#include <limits>

#include "NodeSet.h"

template <class Key>
class TreeSet {
  using value_type = Key;
  using size_type = size_t;

 private:
  NodeSet<Key> *root_{nullptr};
  int size_;
  void print_tree(NodeSet<Key> *curr);
  void delete_tree(NodeSet<Key> *curr);

 public:
  TreeSet();
  explicit TreeSet(value_type val);
  explicit TreeSet(std::initializer_list<value_type> const &items);
  TreeSet(const TreeSet<Key> &tree);
  TreeSet(TreeSet<Key> &&tree);
  ~TreeSet();
  void CopyTree(NodeSet<Key> *curr);
  void operator=(TreeSet<Key> &&other);
  class IteratorTree;
  void Print();
  bool Contains(const Key &val);
  IteratorTree Find(const Key &val);
  bool Empty();
  void Clear();
  size_type Size() { return size_; }
  size_type MaxSize() {
    return std::numeric_limits<size_t>::max() / sizeof(NodeSet<Key>);
  }
  NodeSet<Key> *Pos(Key val);
  std::pair<IteratorTree, bool> Insert(value_type val) {
    NodeSet<Key> *curr = root_;
    if (curr) {
      while (curr && curr->value_ != val) {
        if (curr->value_ > val && curr->left_ == nullptr) {
          curr->left_ = new NodeSet<Key>(val);
          curr->left_->parent_ = curr;
          ++size_;
          IteratorTree iter(curr->left_, this->MostLeft(this->root_),
                            this->MostRight(this->root_));
          return std::make_pair(iter, true);
        }
        if (curr->value_ < val && curr->right_ == nullptr) {
          curr->right_ = new NodeSet<Key>(val);
          curr->right_->parent_ = curr;
          ++size_;
          IteratorTree iter(curr->right_, this->MostLeft(this->root_),
                            this->MostRight(this->root_));
          return std::make_pair(iter, true);
        }
        if (curr->value_ > val) {
          curr = curr->left_;
        } else {
          curr = curr->right_;
        }
      }
    } else {
      root_ = new NodeSet<Key>(val);
      ++size_;
      IteratorTree iter(root_, this->MostLeft(this->root_),
                        this->MostRight(this->root_));
      return std::make_pair(iter, true);
    }
    IteratorTree iter = this->End();
    return std::make_pair(iter, false);
  }
  void Erase(IteratorTree pos);
  void Erase(value_type val);
  NodeSet<Key> *MostLeft(NodeSet<Key> *curr);
  NodeSet<Key> *MostRight(NodeSet<Key> *curr);
  void Swap(TreeSet &other);
  void Merge(TreeSet &other);

  class IteratorTree {
   private:
    NodeSet<Key> *current_{nullptr};
    NodeSet<Key> *minnode_{nullptr};
    NodeSet<Key> *maxnode_{nullptr};

   private:
    void increment();
    void decrement();

   public:
    using iterator = IteratorTree;
    IteratorTree();
    IteratorTree(NodeSet<Key> *curr, NodeSet<Key> *mn, NodeSet<Key> *mx);
    ~IteratorTree() = default;

   public:
    NodeSet<Key> GetCurr() { return *current_; }

   public:
    bool operator==(const iterator &other) {
      if (other.current_ == nullptr || current_ == nullptr)
        return other.current_ != current_;
      return other.current_->value_ == current_->value_;
    }
    bool operator!=(const iterator &other) {
      if (other.current_ == nullptr || current_ == nullptr)
        return other.current_ != current_;
      return other.current_->value_ != current_->value_;
    }
    value_type operator*() {
      if (current_ != nullptr) return current_->value_;
      return maxnode_->value_;
    }
    iterator operator++() {
      increment();
      return *this;
    }
    iterator operator--() {
      decrement();
      return *this;
    }
  };

  class ConstIteratorTree {
   private:
    NodeSet<Key> *current_{nullptr};
    NodeSet<Key> *minnode_{nullptr};
    NodeSet<Key> *maxnode_{nullptr};

   private:
    void increment();
    void decrement();

   public:
    using const_iterator = ConstIteratorTree;
    ConstIteratorTree();
    ConstIteratorTree(NodeSet<Key> *curr, NodeSet<Key> *mn, NodeSet<Key> *mx);
    ~ConstIteratorTree() = default;

   public:
    NodeSet<Key> GetCurr() { return *current_; }

   public:
    bool operator==(const const_iterator &other) {
      if (other.current_ == nullptr || current_ == nullptr)
        return other.current_ != current_;
      return other.current_->value_ == current_->value_;
    }
    bool operator!=(const const_iterator &other) {
      if (other.current_ == nullptr || current_ == nullptr)
        return other.current_ != current_;
      return other.current_->value_ != current_->value_;
    }
    const value_type operator*() const {
      if (current_ != nullptr) return current_->value_;
      return maxnode_->value_;
    }
    const_iterator operator++() {
      increment();
      return *this;
    }
    const_iterator operator--() {
      decrement();
      return *this;
    }
  };

  IteratorTree Begin() {
    IteratorTree it(this->MostLeft(root_), this->MostLeft(root_),
                    this->MostRight(root_));
    return it;
  }
  IteratorTree End() {
    IteratorTree it;
    return it;
  }
};

template <typename Key>
TreeSet<Key>::TreeSet(value_type val) {
  root_ = new NodeSet<Key>(val);
  size_ = 1;
}

template <typename Key>
TreeSet<Key>::TreeSet() {
  root_ = nullptr;
  size_ = 0;
}

template <typename Key>
TreeSet<Key>::TreeSet(const TreeSet<Key> &tree) : TreeSet() {
  CopyTree(tree.root_);
}

template <typename Key>
TreeSet<Key>::TreeSet(std::initializer_list<value_type> const &items)
    : TreeSet() {
  for (const value_type &item : items) {
    Insert(item);
  }
}

template <typename Key>
TreeSet<Key>::TreeSet(TreeSet<Key> &&tree) : TreeSet() {
  *this = std::move(tree);
}

template <typename Key>
void TreeSet<Key>::operator=(TreeSet<Key> &&other) {
  if (root_ != other.root_) {
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
  }
}

template <typename Key>
TreeSet<Key>::~TreeSet() {
  delete_tree(root_);
}

template <typename Key>
void TreeSet<Key>::delete_tree(NodeSet<Key> *curr) {
  if (curr) {
    delete_tree(curr->left_);
    delete_tree(curr->right_);
    curr->parent_ = nullptr;
    delete curr;
  }
}

template <typename Key>
void TreeSet<Key>::CopyTree(NodeSet<Key> *curr) {
  if (!curr) return;
  CopyTree(curr->left_);
  Insert(curr->value_);
  CopyTree(curr->right_);
}

template <typename Key>
void TreeSet<Key>::Print() {
  print_tree(root_);
  std::cout << std::endl;
}

template <typename Key>
void TreeSet<Key>::print_tree(NodeSet<Key> *curr) {
  if (curr) {
    print_tree(curr->left_);
    std::cout << curr->value_ << " ";
    print_tree(curr->right_);
  }
}

template <typename Key>
bool TreeSet<Key>::Contains(const Key &val) {
  NodeSet<Key> *curr = root_;
  while (curr && curr->value_ != val) {
    if (curr->value_ > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  return curr != nullptr;
}

template <typename Key>
typename TreeSet<Key>::IteratorTree TreeSet<Key>::Find(const Key &val) {
  NodeSet<Key> *curr = root_;
  while (curr && curr->value_.first != val) {
    if (curr->value_.first > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  IteratorTree iter(curr, this->MostLeft(this->root_),
                    this->MostRight(this->root_));
  return iter;
}

template <typename Key>
bool TreeSet<Key>::Empty() {
  return root_ == nullptr;
}

template <typename Key>
void TreeSet<Key>::Clear() {
  if (root_) {
    delete_tree(root_);
  }
  size_ = 0;
  root_ = nullptr;
}

template <typename Key>
void TreeSet<Key>::Swap(TreeSet &other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }
}

template <typename Key>
void TreeSet<Key>::Merge(TreeSet &other) {
  if (this->root_ != other.root_) {
    for (auto beg = other.Begin(), endl = other.End(); beg != endl;) {
      std::pair<IteratorTree, bool> temp = Insert(beg.GetCurr().value_);
      if (temp.second) {
        auto del = beg;
        if (beg != other.Begin()) {
          --beg;
        } else {
          beg = other.Begin();
          continue;
        }
      }
      ++beg;
    }
  }
}

template <typename Key>
NodeSet<Key> *TreeSet<Key>::Pos(Key val) {
  NodeSet<Key> *curr = root_;
  while (curr && curr->value_ != val) {
    if (curr->value_ > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  return curr;
}

template <typename Key>
void TreeSet<Key>::Erase(IteratorTree pos) {
  value_type val = pos.GetCurr().value_;
  NodeSet<Key> *curr = root_;
  while (curr && curr->value_ != val) {
    if (curr->value_ > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  if (!curr) {
    return;
  }
  if (curr->left_ == nullptr) {
    // Вместо curr подвешивается его правое поддерево
    if (curr->parent_ && curr->parent_->left_ == curr) {
      curr->parent_->left_ = curr->right_;
    }
    if (curr->parent_ && curr->parent_->right_ == curr) {
      curr->parent_->right_ = curr->right_;
    }
    --size_;
    delete curr;
    return;
  }
  if (curr->right_ == nullptr) {
    // Вместо curr подвешивается его левое поддерево
    if (curr->parent_ && curr->parent_->left_ == curr)
      curr->parent_->left_ = curr->left_;
    if (curr->parent_ && curr->parent_->right_ == curr)
      curr->parent_->right_ = curr->left_;
    --size_;
    delete curr;
    return;
  }
  // У элемента есть два потомка, тогда на место элемента поставим
  // наименьший элемент из его правого поддерева
  NodeSet<Key> *replace = MostLeft(curr->right_);
  value_type replace_value = replace->value_;
  Erase(replace_value);
  curr->value_ = replace_value;
}

template <typename Key>
void TreeSet<Key>::Erase(value_type val) {
  NodeSet<Key> *curr = root_;
  while (curr && curr->value_ != val) {
    if (curr->value_ > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  if (!curr) {
    return;
  }
  if (curr->left_ == nullptr) {
    // Вместо curr подвешивается его правое поддерево
    if (curr->parent_ && curr->parent_->left_ == curr) {
      curr->parent_->left_ = curr->right_;
    }
    if (curr->parent_ && curr->parent_->right_ == curr) {
      curr->parent_->right_ = curr->right_;
    }
    --size_;
    delete curr;
    return;
  }
  if (curr->right_ == nullptr) {
    // Вместо curr подвешивается его левое поддерево
    if (curr->parent_ && curr->parent_->left_ == curr)
      curr->parent_->left_ = curr->left_;
    if (curr->parent_ && curr->parent_->right_ == curr)
      curr->parent_->right_ = curr->left_;
    --size_;
    delete curr;
    return;
  }
  // У элемента есть два потомка, тогда на место элемента поставим
  // наименьший элемент из его правого поддерева
  NodeSet<Key> *replace = MostLeft(curr->right_);
  value_type replace_value = replace->value_;
  Erase(replace_value);
  curr->value_ = replace_value;
}

template <typename Key>
NodeSet<Key> *TreeSet<Key>::MostLeft(NodeSet<Key> *curr) {
  while (curr->left_) {
    curr = curr->left_;
  }
  return curr;
}

template <typename Key>
NodeSet<Key> *TreeSet<Key>::MostRight(NodeSet<Key> *curr) {
  while (curr->right_) {
    curr = curr->right_;
  }
  return curr;
}

template <typename Key>
TreeSet<Key>::IteratorTree::IteratorTree()
    : current_(nullptr), minnode_(nullptr), maxnode_(nullptr) {}

template <typename Key>
TreeSet<Key>::IteratorTree::IteratorTree(NodeSet<Key> *curr, NodeSet<Key> *mn,
                                         NodeSet<Key> *mx)
    : current_(curr), minnode_(mn), maxnode_(mx) {}

template <typename Key>
void TreeSet<Key>::IteratorTree::increment() {
  if (current_ == maxnode_) {
    current_ = nullptr;
    return;
  }
  if (current_->has_right()) {
    current_ = current_->right_;
    while (current_->has_left()) {
      current_ = current_->left_;
    }
  } else {
    while (current_->is_right_child()) {
      current_ = current_->parent_;
    }
    current_ = current_->parent_;
  }
}

template <typename Key>
void TreeSet<Key>::IteratorTree::decrement() {
  if (current_ == nullptr) {
    current_ = maxnode_;
    return;
  }
  if (current_ == minnode_) {
    current_ = nullptr;
    return;
  }
  if (current_->has_left()) {
    current_ = current_->left_;
    while (current_->has_right()) {
      current_ = current_->right_;
    }
  } else {
    while (current_->is_left_child()) {
      current_ = current_->parent_;
    }
    current_ = current_->parent_;
  }
}

template <typename Key>
void TreeSet<Key>::ConstIteratorTree::increment() {
  if (current_ == maxnode_) {
    current_ = nullptr;
    return;
  }
  if (current_->has_right()) {
    current_ = current_->right_;
    while (current_->has_left()) {
      current_ = current_->left_;
    }
  } else {
    while (current_->is_right_child()) {
      current_ = current_->parent_;
    }
    current_ = current_->parent_;
  }
}

template <typename Key>
void TreeSet<Key>::ConstIteratorTree::decrement() {
  if (current_ == nullptr) {
    current_ = maxnode_;
    return;
  }
  if (current_ == minnode_) {
    current_ = nullptr;
    return;
  }
  if (current_->has_left()) {
    current_ = current_->left_;
    while (current_->has_right()) {
      current_ = current_->right_;
    }
  } else {
    while (current_->is_left_child()) {
      current_ = current_->parent_;
    }
    current_ = current_->parent_;
  }
}

template <typename Key>
TreeSet<Key>::ConstIteratorTree::ConstIteratorTree()
    : current_(nullptr), minnode_(nullptr), maxnode_(nullptr) {}

template <typename Key>
TreeSet<Key>::ConstIteratorTree::ConstIteratorTree(NodeSet<Key> *curr,
                                                   NodeSet<Key> *mn,
                                                   NodeSet<Key> *mx)
    : current_(curr), minnode_(mn), maxnode_(mx) {}
#endif  // SRC_MY_TREESET_H_
