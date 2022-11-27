#ifndef SRC_MY_VECTOR_H_
#define SRC_MY_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace my {

template <typename T>
class Vector {
 public:
  // member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;

  // default constructor
  Vector();

  // parametrized constructor
  explicit Vector(size_t n);

  // initializer list constructor
  explicit Vector(std::initializer_list<value_type> const &items);

  // copy constructor
  Vector(const Vector &v);

  // move constructor
  Vector(Vector &&v);

  // destructor
  ~Vector() { delete[] arr_; }

  // overload operator

  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v);

  // vector element access

  reference At(size_t pos);
  reference operator[](size_t pos);
  const_reference Front();
  const_reference Back();
  iterator Data();

  // vector iterators

  iterator Begin();
  iterator End();

  // vector capacity

  bool Empty();
  size_t Size();
  size_t MaxSize();
  void Reserve(size_t size);
  size_t Capacity();
  void ShrinkToFit();

  // vector modifiers

  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PopBack();
  void Swap(Vector &other);

 private:
  value_type *arr_;
  size_t m_capacity_;
  size_t m_size_;

  // support

  void ChangeCapacity(size_t n);
  void Copy(iterator const &pos, const_reference value);
};
}  // namespace my

// ***********************************************

// support methods

template <typename T>
void my::Vector<T>::ChangeCapacity(size_t n) {
  if (n == 0) {
    n = 2;
  }
  m_capacity_ = n;
  value_type *buff = new value_type[m_capacity_];
  for (size_t i = 0; i < m_size_; i++) {
    buff[i] = arr_[i];
  }
  if (arr_) {
    delete[] arr_;
    arr_ = nullptr;
  }
  arr_ = buff;
}

template <typename T>
void my::Vector<T>::Copy(iterator const &pos, const_reference value) {
  iterator first_element = Begin();
  value_type *buff = new value_type[m_capacity_]{};

  int i = 0;
  while (first_element != End()) {
    if (first_element == pos) {
      buff[i] = value;
      i++;
      buff[i] = *first_element;
      i++;
    } else {
      buff[i] = *first_element;
      i++;
    }
    ++first_element;
  }
  m_size_ = i;

  if (arr_) {
    delete[] arr_;
    arr_ = nullptr;
  }
  arr_ = buff;
}

// constructors

// default constructor
template <typename T>
my::Vector<T>::Vector() : m_size_(0U), m_capacity_(0U), arr_(nullptr) {}

// parametrized constructor
template <typename T>
my::Vector<T>::Vector(size_t n)
    : m_size_(n), m_capacity_(n), arr_(new value_type[n]{}) {}

// initializer
template <typename T>
my::Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  m_capacity_ = items.size() * 2;
  m_size_ = items.size();
  arr_ = new value_type[m_capacity_];
  size_t i = 0;
  for (auto *p = items.begin(); p != items.end(); p++) {
    arr_[i] = *p;
    i++;
  }
}

// move constructor
template <typename T>
my::Vector<T>::Vector(Vector &&v)
    : m_size_(v.m_size_), m_capacity_(v.m_capacity_), arr_(v.arr_) {
  v.arr_ = nullptr;
  v.m_size_ = 0;
  v.m_capacity_ = 0;
}

// copy
template <typename T>
my::Vector<T>::Vector(const Vector &v)
    : m_size_(v.m_size_), m_capacity_(v.m_capacity_) {
  arr_ = new value_type[m_size_];
  for (size_t i = 0; i < m_size_; i++) {
    arr_[i] = v.arr_[i];
  }
}

// operator overload

template <typename T>
my::Vector<T> &my::Vector<T>::operator=(const Vector &v) {
  if (this != &v) {
    delete[] arr_;
    m_size_ = v.m_size_;
    m_capacity_ = v.m_capacity_;
    arr_ = new value_type[m_size_];
    for (size_t i = 0; i < m_size_; i++) {
      arr_[i] = v.arr_[i];
    }
  }
  return *this;
}

template <typename T>
my::Vector<T> &my::Vector<T>::operator=(Vector &&v) {
  if (this != &v) {
    delete[] arr_;
    m_size_ = v.m_size_;
    m_capacity_ = v.m_capacity_;
    arr_ = v.arr_;
    v.arr_ = nullptr;
  }
  return *this;
}

// vector element access

template <typename T>
typename my::Vector<T>::reference my::Vector<T>::At(size_t pos) {
  if (pos > m_size_) {
    throw std::invalid_argument("The argument is not correct");
  }
  return arr_[pos];
}

template <typename T>
typename my::Vector<T>::reference my::Vector<T>::operator[](size_t pos) {
  return *(arr_ + pos);
}

template <typename T>
typename my::Vector<T>::const_reference my::Vector<T>::Front() {
  return *(arr_);
}

template <typename T>
typename my::Vector<T>::const_reference my::Vector<T>::Back() {
  return *(arr_ + (m_size_ - 1U));
}

template <typename T>
typename my::Vector<T>::iterator my::Vector<T>::Data() {
  return arr_;
}

// vector iterators

template <typename T>
typename my::Vector<T>::iterator my::Vector<T>::Begin() {
  return arr_;
}

template <typename T>
typename my::Vector<T>::iterator my::Vector<T>::End() {
  return arr_ + m_size_;
}

// vector capacity

template <typename T>
bool my::Vector<T>::Empty() {
  if (m_size_ != 0) {
    return false;
  }
  return true;
}

template <typename T>
size_t my::Vector<T>::Size() {
  return m_size_;
}

template <typename T>
size_t my::Vector<T>::MaxSize() {
  size_t max_size = (std::numeric_limits<size_t>::max() / sizeof(T) / 2);
  return max_size;
}

template <typename T>
void my::Vector<T>::Reserve(size_t size) {
  if (size > m_size_) {
    ChangeCapacity(size);
    m_capacity_ = size;
  }
}

template <typename T>
size_t my::Vector<T>::Capacity() {
  return m_capacity_;
}

template <typename T>
void my::Vector<T>::ShrinkToFit() {
  if (m_capacity_ > m_size_) {
    ChangeCapacity(m_size_);
    m_capacity_ = m_size_;
  }
}

// vector modifiers

template <typename T>
void my::Vector<T>::Clear() {
  for (size_t i = 0; i < m_size_; i++) {
    arr_[i] = 0;
  }
  m_size_ = 0;
}

template <typename T>
typename my::Vector<T>::iterator my::Vector<T>::Insert(
    iterator pos, const_reference value) {
  m_size_++;
  if (m_size_ >= m_capacity_) {
    m_capacity_ = m_size_ + 2;
  }
  Copy(pos, value);
  return pos;
}

template <typename T>
void my::Vector<T>::Erase(iterator pos) {
  iterator first_elem = Begin();
  value_type *buff = new value_type[m_capacity_]{};
  int i = 0;

  while (first_elem != End()) {
    if (first_elem != pos) {
      buff[i] = *first_elem;
      i++;
    }
    ++first_elem;
  }

  delete[] arr_;
  arr_ = buff;
  m_size_ = i;
}

template <typename T>
void my::Vector<T>::PushBack(const_reference value) {
  if (m_size_ >= m_capacity_) {
    ChangeCapacity(m_size_ * 2);
    arr_[m_size_++] = value;
  } else {
    arr_[m_size_++] = value;
  }
}

template <typename T>
void my::Vector<T>::PopBack() {
  if (m_size_) {
    arr_[m_size_--];
  }
}

template <typename T>
void my::Vector<T>::Swap(Vector &other) {
  Vector<T> temp(other);
  other = std::move(*this);
  *this = std::move(temp);
}
#endif  // SRC_MY_VECTOR_H_