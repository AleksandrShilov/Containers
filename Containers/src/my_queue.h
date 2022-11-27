#include "my_list.h"

namespace my {

template <typename T>
class Queue : private List<T> {
 public:
  // member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  // constructor default
  Queue() : List<value_type>::List() {}

  // constructor initialize
  explicit Queue(std::initializer_list<T> const &items)
      : List<value_type>::List(items) {}

  // constructor copy
  Queue(const Queue &q) : List<value_type>::List(q) {}

  // constructor move
  Queue(Queue &&q) : List<value_type>::List(std::move(q)) {}

  // destructor
  ~Queue() {}

  // overload copy
  Queue &operator=(const Queue &q) {
    List<value_type>::Clear();
    for (auto p = q.Kbegin(); p != q.Kend(); ++p) {
      Push(*p);
    }
    return *this;
  }

  // overload move
  Queue &operator=(Queue &&q) {
    List<value_type>::operator=(std::move(q));
    return *this;
  }

  // element access

  const_reference Front() {
    auto first_elem = List<value_type>::Begin();
    return *first_elem;
  }

  const_reference Back() {
    auto last_elem = List<value_type>::End();
    --last_elem;
    return *last_elem;
  }

  // capacity

  using List<value_type>::Empty;
  using List<value_type>::Size;

  // modifiers

  void Push(const_reference value) { List<value_type>::PushBack(value); }
  void Pop() { List<value_type>::PopFront(); }
  void Swap(Queue &other) { List<value_type>::Swap(other); }
};
}  // namespace my