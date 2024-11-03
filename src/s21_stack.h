#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <iostream>

namespace s21 {

template <typename T>

class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    T data;
    Node* prev;
    Node(const T& value)
        : data(value), prev(nullptr) {}  // parametriezed constructor
  };

  Node* top_;
  size_type size_;

 public:
  // Stack Constructors
  stack();  // default constructor
  stack(std::initializer_list<value_type> const&
            items);               // initializer list constructor
  stack(const stack& other);      // copy constructor
  stack(stack&& other) noexcept;  // move constructor
  ~stack();                       // destructor

  // Stack Operators
  stack& operator=(const stack& other);  // Оператор присваивания копированием
  stack& operator=(stack&& other);  // Оператор присваивания перемещением

  // Stack Element access
  const T& top();

  // Stack Capacity
  bool empty() const;
  size_type size() const;

  // Stack Modifiers
  void push(const T& value);
  void pop();
  void swap(stack& other);

  // Part 3 (Bonus)
  template <class... Args>
  void insert_many_back(Args&&... args);
};
}  // namespace s21

#include "s21_stack.inc"  // Methods' realization

#endif  // SRC_S21_STACK_H_
