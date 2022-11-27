#ifndef SRC_MY_LIST_H_
#define SRC_MY_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace my {

template <typename T>
class List {
  class Node;

 public:
  // member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  // construtros default
  List();

  // paramitrized constructor
  explicit List(size_t n);

  // initializer list constructor
  explicit List(std::initializer_list<T> const &items);

  // constructor copy
  List(const List &l);

  // constructor move
  List(List &&l);

  // destructor
  ~List();

  // list iterators
  class ListIterator;

  // member type
  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  // iteerators

  iterator Begin();
  iterator End();
  const_iterator Kbegin() const;
  const_iterator Kend() const;

  class ListIterator {
   public:
    ListIterator() : pCurrentNode_(nullptr) {}
    explicit ListIterator(Node *pNode) : pCurrentNode_(pNode) {}

    // overload
    const_reference operator*() { return pCurrentNode_->data_; }

    ListIterator &operator++() {
      pCurrentNode_ = pCurrentNode_->pNext_;
      return *this;
    }

    ListIterator &operator--() {
      pCurrentNode_ = pCurrentNode_->pPrev_;
      return *this;
    }

    bool operator!=(const ListIterator &iter) {
      return pCurrentNode_ != iter.pCurrentNode_;
    }

    bool operator==(const ListIterator &iter) {
      return pCurrentNode_ == iter.pCurrentNode_;
    }

    Node *GetCurrentNode() { return pCurrentNode_; }

   private:
    Node *pCurrentNode_ = nullptr;
  };

  // overload operator

  List &operator=(const List &l);
  List &operator=(List &&l);

  // list element access

  const_reference Front();
  const_reference Back();

  // list capacity

  bool Empty();
  size_t Size();
  size_t MaxSize();

  // list modifiers

  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PopBack();
  void PushFront(const_reference value);
  void PopFront();
  void Swap(List &other);
  void Merge(List &other);
  void Splice(const_iterator pos, List &other);
  void Reverse();
  void Unique();
  void Sort();

 private:
  class Node {
   public:
    friend class List;
    T data_;
    Node *pNext_ = nullptr;
    Node *pPrev_ = nullptr;
    Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr)
        : data_(data), pPrev_(pPrev), pNext_(pNext) {}
  };

  Node *head_ = nullptr;
  Node *tail = nullptr;
  Node *node_end_ = nullptr;
  size_t size_ = 0;
};
}  // namespace my

// **********************************

// constructors

// default constructor
template <typename T>
my::List<T>::List() : size_(0U), head_(nullptr), node_end_(nullptr) {}

// paramitrized constructor
template <typename T>
my::List<T>::List(size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (head_ == nullptr) {
      head_ = new Node();
      node_end_ = new Node;
      node_end_->pNext_ = nullptr;
      head_->pNext_ = node_end_;
      size_++;
    } else {
      value_type temp;
      PushBack(temp);
    }
  }
}

// initializer
template <typename T>
my::List<T>::List(std::initializer_list<T> const &items) {
  for (auto element : items) {
    PushBack(element);
  }
}

// copy
template <typename T>
my::List<T>::List(const List &l) {
  Node *temp = l.head_;
  size_t temp_size = l.size_;
  while (temp_size) {
    PushBack(temp->data_);
    temp = temp->pNext_;
    temp_size--;
  }
}

// constructor move
template <typename T>
my::List<T>::List(List &&l)
    : size_(l.size_), head_(l.head_), node_end_(l.node_end_) {
  l.size_ = 0U;
  l.head_ = nullptr;
  l.node_end_ = nullptr;
}

// destructor
template <typename T>
my::List<T>::~List() {
  Clear();
  delete node_end_;
  node_end_ = nullptr;
}

// iterators

template <typename T>
typename my::List<T>::iterator my::List<T>::Begin() {
  return iterator(head_);
}

template <typename T>
typename my::List<T>::iterator my::List<T>::End() {
  return iterator(node_end_);
}

template <typename T>
typename my::List<T>::const_iterator my::List<T>::Kbegin() const {
  return const_iterator(head_);
}

template <typename T>
typename my::List<T>::const_iterator my::List<T>::Kend() const {
  return const_iterator(node_end_);
}

// overload operator

template <typename T>
my::List<T> &my::List<T>::operator=(const List &l) {
  if (&l != this) {
    Clear();
    delete node_end_;
    node_end_ = nullptr;
    Node *temp = l.head_;
    size_t temp_size = l.size_;
    while (temp_size) {
      PushBack(temp->data_);
      temp = temp->pNext_;
      temp_size--;
    }
  }
  return *this;
}

template <typename T>
my::List<T> &my::List<T>::operator=(List &&l) {
  if (&l != this) {
    Clear();
    delete node_end_;
    node_end_ = nullptr;
    head_ = l.head_;
    node_end_ = l.node_end_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.node_end_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

// list element access

template <typename T>
typename my::List<T>::const_reference my::List<T>::Front() {
  return head_->data_;
}

template <typename T>
typename my::List<T>::const_reference my::List<T>::Back() {
  Node *temp = node_end_->pPrev_;
  return temp->data_;
}

// list capacity

template <typename T>
bool my::List<T>::Empty() {
  bool result = false;
  if (size_ == 0) {
    result = true;
  }
  return result;
}

template <typename T>
size_t my::List<T>::Size() {
  return size_;
}

template <typename T>
size_t my::List<T>::MaxSize() {
  size_t max_size = (std::numeric_limits<size_t>::max() / sizeof(Node) / 2);
  return max_size;
}

// list modifiers

template <typename T>
void my::List<T>::Clear() {
  while (size_) {
    PopFront();
  }
  head_ = nullptr;
}

template <typename T>
typename my::List<T>::iterator my::List<T>::Insert(iterator pos,
                                                     const_reference value) {
  Node *curr = pos.GetCurrentNode();
  Node *prev = nullptr;
  iterator insert_pos;

  if (curr == head_ || Empty()) {
    PushFront(value);
    insert_pos = Begin();
  } else {
    Node *new_node = new Node(value, curr->pPrev_, curr);
    prev = curr->pPrev_;
    prev->pNext_ = new_node;
    curr->pPrev_ = new_node;
    iterator insert_tmp(new_node);
    insert_pos = insert_tmp;
    size_++;
  }

  return insert_pos;
}

template <typename T>
void my::List<T>::Erase(iterator pos) {
  Node *curr = pos.GetCurrentNode();
  if (Empty()) {
    throw std::invalid_argument("List is Empty");
  } else if (curr == head_) {
    PopFront();
  } else if (curr->pNext_ == nullptr) {
    PopBack();
  } else {
    Node *next = curr->pNext_;
    Node *prev = curr->pPrev_;
    prev->pNext_ = next;
    next->pPrev_ = prev;
    delete curr;
    curr = nullptr;
    size_--;
  }
}

template <typename T>
void my::List<T>::PushBack(const_reference value) {
  if (head_ == nullptr) {
    node_end_ = new Node;
    head_ = new Node(value, nullptr, node_end_);
    node_end_->pPrev_ = head_;
    node_end_->pNext_ = nullptr;
  } else {
    Node *temp = head_;
    while (temp->pNext_ != node_end_) {
      temp = temp->pNext_;
    }
    temp->pNext_ = new Node(value, temp, node_end_);
    node_end_->pPrev_ = temp->pNext_;
  }
  node_end_->pNext_ = nullptr;
  size_++;
}

template <typename T>
void my::List<T>::PopBack() {
  if (head_) {
    Node *temp_h = head_;
    size_t temp_s = size_ - 1;
    while (temp_s > 1) {
      temp_h = temp_h->pNext_;
      temp_s--;
    }
    delete temp_h->pNext_;
    temp_h->pNext_ = nullptr;
    node_end_->pPrev_ = temp_h;
    size_--;
  }
}

template <typename T>
void my::List<T>::PushFront(const_reference value) {
  if (node_end_ == nullptr) {
    node_end_ = new Node;
    head_ = new Node(value, nullptr, head_);
    node_end_->pPrev_ = head_;
    node_end_->pNext_ = nullptr;
  } else {
    head_ = new Node(value, nullptr, head_);
  }
  size_++;
}

template <typename T>
void my::List<T>::PopFront() {
  if (head_) {
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      delete node_end_;
      node_end_ = nullptr;
      size_--;
    } else {
      Node *temp = head_;
      head_ = head_->pNext_;
      delete temp;
      temp = nullptr;
      size_--;
    }
  }
}

template <typename T>
void my::List<T>::Swap(List &other) {
  List<T> temp(other);
  other = std::move(*this);
  *this = std::move(temp);
}

template <typename T>
void my::List<T>::Merge(List &other) {
  size_t other_size = other.size_;
  Node *temp_head_other = other.head_;
  while (other_size) {
    PushBack(temp_head_other->data_);
    temp_head_other = temp_head_other->pNext_;
    other_size--;
  }
  other.Clear();
}

template <typename T>
void my::List<T>::Splice(const_iterator pos, List &other) {
  if (!other.Empty()) {
    for (auto it = other.Begin(); it != other.End(); ++it) {
      Insert(pos, *it);
    }
    other.Clear();
  }
}

template <typename T>
void my::List<T>::Reverse() {
  List<T> list_reverse;
  Node *temp_head = head_;
  size_t temp_size = size_;
  while (temp_size != 0) {
    list_reverse.PushFront(temp_head->data_);
    temp_head = temp_head->pNext_;
    temp_size--;
  }
  Clear();
  *this = std::move(list_reverse);
}

template <typename T>
void my::List<T>::Unique() {
  if (Empty() == false) {
    for (auto iter = Kbegin(); iter != Kend();) {
      iterator temp = iter;
      value_type current_value = *iter;
      value_type next_value = *(++iter);
      Node *temp_node_current = iter.GetCurrentNode();
      if (current_value == next_value && (temp_node_current != node_end_)) {
        Erase(iter);
        iter = temp;
      }
    }
  }
}

template <typename T>
void my::List<T>::Sort() {
  if (Empty() == false) {
    iterator iter_end = End();
    iterator iter_last_elem = --iter_end;
    ++iter_end;
    for (auto it = Begin(); it != iter_end; ++it) {
      for (auto it2 = Begin(); it2 != iter_last_elem;) {
        value_type current_elem = *it2;
        Node *current_point_to_node = it2.GetCurrentNode();
        value_type next_elem = *(++it2);
        Node *next_point_to_node = it2.GetCurrentNode();
        if (current_elem > next_elem && next_point_to_node != node_end_)
          std::swap(current_point_to_node->data_, next_point_to_node->data_);
      }
    }
  }
}

#endif  // SRC_MY_LIST_H_