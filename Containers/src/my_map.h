#ifndef SRC_MY_MAP_H_
#define SRC_MY_MAP_H_

#include "Tree.h"

namespace my {
template <class Key, class Value>
class Map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key, Value>::IteratorTree;
  using const_iterator = typename Tree<Key, Value>::ConstIteratorTree;
  using size_type = size_t;

 private:
  Tree<key_type, mapped_type> tree;

 public:
  Map();
  explicit Map(std::initializer_list<value_type> const &items);
  Map(const Map &m) : tree(m.tree) {}
  Map(Map &&m) : tree(std::move(m.tree)) {}
  ~Map();
  void operator=(Map &&m);

 public:
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(Map &other);
  void merge(Map &other);

 public:
  bool empty();
  size_type size();
  size_type max_size();

 public:
  bool contains(const key_type &key);

 public:
  iterator begin() { return tree.Begin(); }
  iterator end() { return tree.End(); }

 public:
  Value &at(const key_type &key) { return tree.at(key); }
  Value &operator[](const key_type &key) { return tree.operator[](key); }
};

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map() {}
template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(
    std::initializer_list<value_type> const &items) {
  for (const value_type &item : items) {
    this->insert(item);
  }
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::~Map() {}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::size() {
  return tree.Size();
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const value_type &value) {
  return tree.Insert(value);
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
  return tree.InsertOrAssign(key, obj);
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const key_type &key,
                                   const mapped_type &obj) {
  return tree.Insert(key, obj);
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::empty() {
  return tree.Empty();
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::max_size() {
  return tree.MaxSize();
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::clear() {
  tree.Clear();
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::contains(const key_type &key) {
  return tree.Contains(key);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::erase(iterator pos) {
  tree.Erase(pos);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::swap(Map &other) {
  tree.Swap(other.tree);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::merge(Map &other) {
  tree.Merge(other.tree);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::operator=(Map &&m) {
  tree.operator=(m.tree);
}

}  // namespace my

#endif  // SRC_MY_MAP_H_
