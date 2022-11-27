#ifndef SRC_MY_SET_H_
#define SRC_MY_SET_H_

#include "TreeSet.h"

namespace my {
template <class Key>
class Set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename TreeSet<Key>::IteratorTree;
  using const_iterator = typename TreeSet<Key>::ConstIteratorTree;
  using size_type = size_t;

 private:
  TreeSet<Key> tree;

 public:
  Set();
  explicit Set(std::initializer_list<value_type> const &items);
  Set(const Set &m) : tree(m.tree) {}
  Set(Set &&m) : tree(std::move(m.tree)) {}
  ~Set();
  void operator=(Set &&m);

 public:
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(Set &other);
  void merge(Set &other);

 public:
  bool empty();
  size_type size();
  size_type max_size();

 public:
  bool contains(const key_type &key);
  iterator find(const Key &key) { return tree.Find(key); };

 public:
  iterator begin() { return tree.Begin(); }
  iterator end() { return tree.End(); }
};

template <typename key_type>
Set<key_type>::Set() {}

template <typename key_type>
Set<key_type>::Set(std::initializer_list<value_type> const &items) {
  for (const value_type &item : items) {
    this->insert(item);
  }
}

template <typename key_type>
Set<key_type>::~Set() {}

template <typename key_type>
typename Set<key_type>::size_type Set<key_type>::size() {
  return tree.Size();
}

template <typename key_type>
std::pair<typename Set<key_type>::iterator, bool> Set<key_type>::insert(
    const value_type &value) {
  return tree.Insert(value);
}

template <typename key_type>
bool Set<key_type>::empty() {
  return tree.Empty();
}

template <typename key_type>
typename Set<key_type>::size_type Set<key_type>::max_size() {
  return tree.MaxSize();
}

template <typename key_type>
void Set<key_type>::clear() {
  tree.Clear();
}

template <typename key_type>
bool Set<key_type>::contains(const key_type &key) {
  return tree.Contains(key);
}

template <typename key_type>
void Set<key_type>::erase(iterator pos) {
  tree.Erase(pos);
}

template <typename key_type>
void Set<key_type>::swap(Set &other) {
  tree.Swap(other.tree);
}

template <typename key_type>
void Set<key_type>::merge(Set &other) {
  tree.Merge(other.tree);
}

template <typename key_type>
void Set<key_type>::operator=(Set &&m) {
  tree.operator=(m.tree);
}

}  // namespace my

#endif  // SRC_MY_SET_H_
