#ifndef SRC_MY_STACK_H_
#define SRC_MY_STACK_H_

#include <initializer_list>
#include <iostream>

namespace my {

template <typename T>
class Stack {
 public:
  // member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  // construtros default
  Stack();

  // initializer constructor
  explicit Stack(std::initializer_list<value_type> const &items);

  // constructor copy
  Stack(const Stack &s);

  // constructor move
  Stack(Stack &&s);

  // destructor
  ~Stack() { Clear(); }

  // overload operator

  Stack<T> &operator=(const Stack &s);
  Stack<T> &operator=(Stack &&s);

  // capacity

  bool Empty();
  size_t Size();

  // element access

  const_reference Top() const;

  // modifiers

  void Push(const value_type value);
  void Pop();
  void Swap(Stack &other);

 private:
  template <typename T2>
  class Node {
   public:
    T2 data_;
    Node *prev_ = nullptr;
    Node(T2 data = T2(), Node *prev = nullptr) : data_(data), prev_(prev) {}
  };

  Node<T> *head_ = nullptr;
  size_t size_ = 0;

  void Clear();
  void CopyItemsToNewStack(Stack &new_stack, const Stack &s);
  void CopyStack(const Stack &new_stack);
};

};  // namespace my

// **************************************************************

// construtros default
template <typename T>
my::Stack<T>::Stack() : size_(0U), head_(nullptr) {}

// initializer constructor
template <typename T>
my::Stack<T>::Stack(std::initializer_list<value_type> const &items) {
  for (auto *p = items.begin(); p != items.end(); p++) {
    Push(*p);
  }
}

// constructor copy
template <typename T>
my::Stack<T>::Stack(const Stack &s) {
  Clear();
  Stack<T> new_stack;
  Node<T> *temp = s.head_;
  size_t temp_size = s.size_;
  while (temp_size) {
    new_stack.Push(temp->data_);
    temp = temp->prev_;
    temp_size--;
  }
  Node<T> *temp_new_stack = new_stack.head_;
  size_t temp_new_size = new_stack.size_;
  while (temp_new_size) {
    Push(temp_new_stack->data_);
    temp_new_stack = temp_new_stack->prev_;
    temp_new_size--;
  }
}

// constructor move
template <typename T>
my::Stack<T>::Stack(Stack &&s) : size_(s.size_), head_(s.head_) {
  s.head_ = nullptr;
  s.size_ = 0U;
}

// overload operator

template <typename T>
my::Stack<T> &my::Stack<T>::operator=(const Stack &s) {
  if (this != &s) {
    Clear();
    Stack<T> new_stack;
    CopyItemsToNewStack(new_stack, s);
    CopyStack(new_stack);
  }
  return *this;
}

template <typename T>
my::Stack<T> &my::Stack<T>::operator=(Stack &&s) {
  if (this != &s) {
    Clear();
    Stack<T> new_stack;
    CopyItemsToNewStack(new_stack, s);
    CopyStack(new_stack);
    s.Clear();
  }
  return *this;
}

// capacity

template <typename T>
bool my::Stack<T>::Empty() {
  if (size_ == 0) {
    return true;
  }
  return false;
}

template <typename T>
size_t my::Stack<T>::Size() {
  return size_;
}

// element access

template <typename T>
typename my::Stack<T>::const_reference my::Stack<T>::Top() const {
  Node<T> *temp = head_;
  return temp->data_;
}

// modifiers

template <typename T>
void my::Stack<T>::Push(const value_type value) {
  head_ = new Node<T>(value, head_);
  size_++;
}

template <typename T>
void my::Stack<T>::Pop() {
  Node<T> *last = head_;
  head_ = head_->prev_;
  delete last;
  last = nullptr;
  size_--;
}

template <typename T>
void my::Stack<T>::Swap(Stack &other) {
  Stack<T> temp(other);
  other = std::move(*this);
  *this = std::move(temp);
}

// support

template <typename T>
void my::Stack<T>::Clear() {
  while (size_) {
    Node<T> *temp = head_;
    head_ = head_->prev_;
    delete temp;
    temp = nullptr;
    size_--;
  }
}

template <typename T>
void my::Stack<T>::CopyItemsToNewStack(Stack &new_stack, const Stack &s) {
  Node<T> *temp = s.head_;
  size_t temp_size = s.size_;
  while (temp_size) {
    new_stack.Push(temp->data_);
    temp = temp->prev_;
    temp_size--;
  }
}

template <typename T>
void my::Stack<T>::CopyStack(const Stack &new_stack) {
  Node<T> *temp_new_stack = new_stack.head_;
  size_t temp_new_size = new_stack.size_;
  while (temp_new_size) {
    Push(temp_new_stack->data_);
    temp_new_stack = temp_new_stack->prev_;
    temp_new_size--;
  }
}

#endif  // SRC_MY_STACK_H_
