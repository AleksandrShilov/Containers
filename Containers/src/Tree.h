#ifndef SRC_MY_TREE_H_
#define SRC_MY_TREE_H_

#include <iostream>
#include <limits>

#include "NodeTree.h"

template <class Key, class Value>
class Tree {
  using value_type = std::pair<const Key, Value>;
  using size_type = size_t;

 private:
  Node<Key, Value> *root_{nullptr};
  int size_;
  void print_tree(Node<Key, Value> *curr);
  void delete_tree(Node<Key, Value> *curr);

 public:
  Tree();
  explicit Tree(value_type val);
  explicit Tree(std::initializer_list<value_type> const &items);
  Tree(const Tree<Key, Value> &tree);
  Tree(Tree<Key, Value> &&tree);
  ~Tree();
  void CopyTree(Node<Key, Value> *curr);
  void operator=(Tree<Key, Value> &&other);
  class IteratorTree;
  void Print();
  bool Contains(const Key &val);
  bool Empty();
  void Clear();
  size_type Size() { return size_; }
  size_type MaxSize() {
    return std::numeric_limits<size_t>::max() / sizeof(Node<Key, Value>);
  }
  Node<Key, Value> *Pos(Key val);
  std::pair<IteratorTree, bool> Insert(value_type val) {
    Node<Key, Value> *curr = root_;
    if (curr) {
      while (curr && curr->value_.first != val.first) {
        if (curr->value_.first > val.first && curr->left_ == nullptr) {
          curr->left_ = new Node<Key, Value>(val);
          curr->left_->parent_ = curr;
          ++size_;
          IteratorTree iter(curr->left_, this->MostLeft(this->root_),
                            this->MostRight(this->root_));
          return std::make_pair(iter, true);
        }
        if (curr->value_.first < val.first && curr->right_ == nullptr) {
          curr->right_ = new Node<Key, Value>(val);
          curr->right_->parent_ = curr;
          ++size_;
          IteratorTree iter(curr->right_, this->MostLeft(this->root_),
                            this->MostRight(this->root_));
          return std::make_pair(iter, true);
        }
        if (curr->value_.first > val.first) {
          curr = curr->left_;
        } else {
          curr = curr->right_;
        }
      }
    } else {
      root_ = new Node<Key, Value>(val);
      ++size_;
      IteratorTree iter(root_, this->MostLeft(this->root_),
                        this->MostRight(this->root_));
      return std::make_pair(iter, true);
    }
    IteratorTree iter = this->End();
    return std::make_pair(iter, false);
  }
  std::pair<IteratorTree, bool> Insert(const Key &key, const Value &obj) {
    return Insert(std::make_pair(key, obj));
  }
  std::pair<IteratorTree, bool> InsertOrAssign(const Key &key,
                                               const Value &obj) {
    bool check = this->Contains(key);
    if (check) {
      Node<Key, Value> *elem = this->Pos(key);
      elem->value_.second = obj;
      IteratorTree iter(elem, this->MostLeft(this->root_),
                        this->MostRight(this->root_));
      return std::make_pair(iter, false);
    } else {
      return Insert(key, obj);
    }
  }
  void Erase(IteratorTree pos);
  void Erase(value_type val);
  Node<Key, Value> *MostLeft(Node<Key, Value> *curr);
  Node<Key, Value> *MostRight(Node<Key, Value> *curr);
  Value &at(const Key &key);
  Value &operator[](const Key &key);
  void Swap(Tree &other);
  void Merge(Tree &other);

  class IteratorTree {
   private:
    Node<Key, Value> *current_{nullptr};
    Node<Key, Value> *minnode_{nullptr};
    Node<Key, Value> *maxnode_{nullptr};

   private:
    void increment();
    void decrement();

   public:
    using iterator = IteratorTree;
    IteratorTree();
    IteratorTree(Node<Key, Value> *curr, Node<Key, Value> *mn,
                 Node<Key, Value> *mx);
    ~IteratorTree() = default;

   public:
    Node<Key, Value> GetCurr() { return *current_; }

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
    Node<Key, Value> *current_{nullptr};
    Node<Key, Value> *minnode_{nullptr};
    Node<Key, Value> *maxnode_{nullptr};

   private:
    void increment();
    void decrement();

   public:
    using const_iterator = ConstIteratorTree;
    ConstIteratorTree();
    ConstIteratorTree(Node<Key, Value> *curr, Node<Key, Value> *mn,
                      Node<Key, Value> *mx);
    ~ConstIteratorTree() = default;

   public:
    Node<Key, Value> GetCurr() { return *current_; }

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

template <typename Key, typename Value>
Tree<Key, Value>::Tree(value_type val) {
  root_ = new Node<Key, Value>(val);
  size_ = 1;
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree() {
  root_ = nullptr;
  size_ = 0;
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(const Tree<Key, Value> &tree) : Tree() {
  CopyTree(tree.root_);
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(std::initializer_list<value_type> const &items)
    : Tree() {
  for (const value_type &item : items) {
    Insert(item);
  }
}

template <typename Key, typename Value>
Tree<Key, Value>::Tree(Tree<Key, Value> &&tree) : Tree() {
  *this = std::move(tree);
}

template <typename Key, typename Value>
void Tree<Key, Value>::operator=(Tree<Key, Value> &&other) {
  if (root_ != other.root_) {
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
  }
}

template <typename Key, typename Value>
Tree<Key, Value>::~Tree() {
  delete_tree(root_);
}

template <typename Key, typename Value>
void Tree<Key, Value>::delete_tree(Node<Key, Value> *curr) {
  if (curr) {
    delete_tree(curr->left_);
    delete_tree(curr->right_);
    curr->parent_ = nullptr;
    delete curr;
  }
}

template <typename Key, typename Value>
void Tree<Key, Value>::CopyTree(Node<Key, Value> *curr) {
  if (!curr) return;
  CopyTree(curr->left_);
  Insert(std::make_pair(curr->value_.first, curr->value_.second));
  CopyTree(curr->right_);
}

template <typename Key, typename Value>
void Tree<Key, Value>::Print() {
  print_tree(root_);
  std::cout << std::endl;
}

template <typename Key, typename Value>
void Tree<Key, Value>::print_tree(Node<Key, Value> *curr) {
  if (curr) {
    print_tree(curr->left_);
    std::cout << "(" << curr->value_.first << " , " << curr->value_.second
              << ") ";
    print_tree(curr->right_);
  }
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Contains(const Key &val) {
  Node<Key, Value> *curr = root_;
  while (curr && curr->value_.first != val) {
    if (curr->value_.first > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  return curr != nullptr;
}

template <typename Key, typename Value>
bool Tree<Key, Value>::Empty() {
  return root_ == nullptr;
}

template <typename Key, typename Value>
void Tree<Key, Value>::Clear() {
  if (root_) {
    delete_tree(root_);
  }
  size_ = 0;
  root_ = nullptr;
}

template <typename Key, typename Value>
Value &Tree<Key, Value>::at(const Key &key) {
  bool check = this->Contains(key);
  if (!check) {
    throw "There is no such key in the map!";
  }
  Node<Key, Value> *elem = this->Pos(key);
  return elem->value_.second;
}

template <typename Key, typename Value>
void Tree<Key, Value>::Swap(Tree &other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }
}

template <typename Key, typename Value>
void Tree<Key, Value>::Merge(Tree &other) {
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

template <typename Key, typename Value>
Value &Tree<Key, Value>::operator[](const Key &key) {
  bool check = this->Contains(key);
  if (!check) {
    Insert(key, Value());
  }
  Node<Key, Value> *elem = this->Pos(key);
  return elem->value_.second;
}

template <typename Key, typename Value>
Node<Key, Value> *Tree<Key, Value>::Pos(Key val) {
  Node<Key, Value> *curr = root_;
  while (curr && curr->value_.first != val) {
    if (curr->value_.first > val) {
      curr = curr->left_;
    } else {
      curr = curr->right_;
    }
  }
  return curr;
}

template <typename Key, typename Value>
void Tree<Key, Value>::Erase(IteratorTree pos) {
  value_type val = pos.GetCurr().value_;
  Node<Key, Value> *curr = root_;
  while (curr && curr->value_.first != val.first) {
    if (curr->value_.first > val.first) {
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
  Node<Key, Value> *replace = MostLeft(curr->right_);
  value_type replace_value = replace->value_;
  Erase(replace_value);
  curr->value_ = replace_value;
}

template <typename Key, typename Value>
void Tree<Key, Value>::Erase(value_type val) {
  Node<Key, Value> *curr = root_;
  while (curr && curr->value_.first != val.first) {
    if (curr->value_.first > val.first) {
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
  Node<Key, Value> *replace = MostLeft(curr->right_);
  value_type replace_value = replace->value_;
  Erase(replace_value);
  curr->value_ = replace_value;
}

template <typename Key, typename Value>
Node<Key, Value> *Tree<Key, Value>::MostLeft(Node<Key, Value> *curr) {
  while (curr->left_) {
    curr = curr->left_;
  }
  return curr;
}

template <typename Key, typename Value>
Node<Key, Value> *Tree<Key, Value>::MostRight(Node<Key, Value> *curr) {
  while (curr->right_) {
    curr = curr->right_;
  }
  return curr;
}

template <typename Key, typename Value>
Tree<Key, Value>::IteratorTree::IteratorTree()
    : current_(nullptr), minnode_(nullptr), maxnode_(nullptr) {}

template <typename Key, typename Value>
Tree<Key, Value>::IteratorTree::IteratorTree(Node<Key, Value> *curr,
                                             Node<Key, Value> *mn,
                                             Node<Key, Value> *mx)
    : current_(curr), minnode_(mn), maxnode_(mx) {}

template <typename Key, typename Value>
void Tree<Key, Value>::IteratorTree::increment() {
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

template <typename Key, typename Value>
void Tree<Key, Value>::IteratorTree::decrement() {
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

template <typename Key, typename Value>
void Tree<Key, Value>::ConstIteratorTree::increment() {
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

template <typename Key, typename Value>
void Tree<Key, Value>::ConstIteratorTree::decrement() {
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

template <typename Key, typename Value>
Tree<Key, Value>::ConstIteratorTree::ConstIteratorTree()
    : current_(nullptr), minnode_(nullptr), maxnode_(nullptr) {}

template <typename Key, typename Value>
Tree<Key, Value>::ConstIteratorTree::ConstIteratorTree(Node<Key, Value> *curr,
                                                       Node<Key, Value> *mn,
                                                       Node<Key, Value> *mx)
    : current_(curr), minnode_(mn), maxnode_(mx) {}
#endif  // SRC_MY_TREE_H_
