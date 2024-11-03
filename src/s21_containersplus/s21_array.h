#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

namespace s21 {
template <typename T, std::size_t N>
class array {
  // Member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using const_iterator = const T *;
  using size_type = std::size_t;

 private:
  T data_[N];

 public:
  class iterator {
   public:
    iterator();
    iterator(T *ptr);
    bool operator==(iterator &other);
    bool operator!=(iterator &other);
    T &operator*();
    iterator operator++(int);
    iterator operator--(int);

   private:
    T *element;
  };

 public:
  // Array Constructors
  array();
  array(std::initializer_list<value_type> const
            &items);          // initializer constructor
  array(const array &a);      // copy constructor
  array(array &&a) noexcept;  // move constructor
  ~array();                   // destructor

  // Array Operators
  array &operator=(const array &a);
  array &operator=(array &&a) noexcept;

  // Array Element access
  reference at(size_t pos);
  reference operator[](size_t pos);
  const_reference front() const noexcept;
  const_reference back() const noexcept;

  // Array Iterators
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  iterator data() noexcept;

  // Array Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Array Modifiers
  void swap(array &other) noexcept;
  void fill(const_reference value);
};
}  // namespace s21

#include "s21_array.inc"  // Methods' realization

#endif  // SRC_S21_ARRAY_H_
