#include "s21_stack.h"

namespace s21 {

// Stack Constructors

template <typename T>
stack<T>::stack() : top_(nullptr), size_(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items)
    : top_(nullptr), size_(0) {
  for (auto i : items) {
    push(i);
  }
}

template <typename T>
stack<T>::stack(const stack& other) : stack() {
  stack<T> tmp_stack;
  Node* other_nodes = other.top_;
  while (other_nodes) {
    tmp_stack.push(other_nodes->data);
    other_nodes = other_nodes->prev;
  }
  Node* tmp_nodes = tmp_stack.top_;
  while (tmp_nodes) {
    push(tmp_nodes->data);
    tmp_nodes = tmp_nodes->prev;
  }
}

template <typename T>
stack<T>::stack(stack&& other) noexcept : top_(other.top_), size_(other.size_) {
  other.top_ = nullptr;
  other.size_ = 0;
}

template <typename T>
stack<T>::~stack() {
  for (size_t i = 0; i < size_; i++) {
    pop();
  }
}

// Оператор присваивания копированием
template <typename T>
stack<T>& stack<T>::operator=(const stack& other) {
  if (this != &other) {
    stack tmp(other);
    swap(tmp);
  }
  return *this;
}

// Оператор присваивания перемещением
template <typename T>
stack<T>& stack<T>::operator=(stack&& other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

// Stack Element access
template <typename T>
const T& stack<T>::top() {
  return this->top_->data;
}

template <typename T>
bool stack<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
size_t stack<T>::size() const {
  return this->size_;
}

// Stack Modifiers

template <typename T>
void stack<T>::push(const T& value) {
  Node* new_element = new Node(value);
  if (!top_) {
    top_ = new_element;  // push first element in empty stack
  } else {
    new_element->prev = top_;  // redirect for previous
    top_ = new_element;
  }
  size_ = size_ + 1;  // update stack size
}

template <typename T>
void stack<T>::pop() {
  if (!top_) {
    throw std::exception();
  }
  Node* new_top = top_->prev;  // save new top adress
  delete top_;                 // delete old top node
  top_ = new_top;
  size_ = size_ - 1;  // update stack size
}

template <typename T>
void stack<T>::swap(stack& other) {
  std::swap(top_, other.top_);
  std::swap(size_, other.size_);
}

template <typename T>
template <class... Args>
void stack<T>::insert_many_back(Args&&... args) {
  for (auto& i : {args...}) {
    push(i);
  }
}

}  // namespace s21
