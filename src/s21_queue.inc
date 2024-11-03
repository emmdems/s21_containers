#include "s21_queue.h"

namespace s21 {

// Конструктор по умолчанию
template <typename T>
queue<T>::queue() : front_(nullptr), back_(nullptr), size_(0) {}

// Initializer list constructor
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const& items)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (auto i : items) {
    push(i);
  }
}

// Конструктор копирования
template <typename T>
queue<T>::queue(const queue& other) : queue() {
  Node* current = other.front_;
  while (current) {
    push(current->data);
    current = current->next;
  }
}

// Конструктор перемещения
template <typename T>
queue<T>::queue(queue&& other) : queue() {
  swap(other);
}

// Деструктор
template <typename T>
queue<T>::~queue() {
  while (!empty()) {
    pop();
  }
}

// Оператор присваивания копированием
template <typename T>
queue<T>& queue<T>::operator=(const queue& other) {
  if (this != &other) {
    queue tmp(other);
    swap(tmp);
  }
  return *this;
}

// Оператор присваивания перемещением
template <typename T>
queue<T>& queue<T>::operator=(queue&& other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

// Добавление элемента в конец
template <typename T>
void queue<T>::push(const T& value) {
  Node* new_node = new Node(value);
  if (empty()) {
    front_ = back_ = new_node;
  } else {
    back_->next = new_node;
    back_ = new_node;
  }
  ++size_;
}

// Удаление элемента из начала
template <typename T>
void queue<T>::pop() {
  if (empty()) {
    return;  // Если очередь пуста, просто возвращаемся
  }
  Node* tmp = front_;
  front_ = front_->next;
  delete tmp;
  --size_;
}

// Доступ к первому элементу
template <typename T>
const T& queue<T>::front() const {
  if (!front_) {
    throw std::exception();
  } else {
    return front_->data;
  }
}

// Доступ к последнему элементу
template <typename T>
const T& queue<T>::back() const {
  if (!back_) {
    throw std::exception();
  } else {
    return back_->data;
  }
}

// Проверка на пустоту
template <typename T>
bool queue<T>::empty() const {
  return size_ == 0;
}

// Получение размера
template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return size_;
}

// Обмен содержимым с другой очередью
template <typename T>
void queue<T>::swap(queue& other) {
  // Обмен front_
  Node* temp_front = front_;
  front_ = other.front_;
  other.front_ = temp_front;

  // Обмен back_
  Node* temp_back = back_;
  back_ = other.back_;
  other.back_ = temp_back;

  // Обмен size_
  size_type temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

// Part 3 (Bonus)
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  // Используем развёртку пакета параметров для вызова push для каждого элемента
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21
