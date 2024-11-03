#ifndef SRC_S21_QUEUE_H
#define SRC_S21_QUEUE_H

namespace s21 {

template <typename T>

class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    T data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* front_;
  Node* back_;
  size_type size_;

 public:
  queue();  // Конструктор по умолчанию
  queue(std::initializer_list<value_type> const&
            items);           // initializer list constructor
  queue(const queue& other);  // Конструктор копирования
  queue(queue&& other);       // Конструктор перемещения
  ~queue();                   // Деструктор

  queue& operator=(const queue& other);  // Оператор присваивания копированием
  queue& operator=(queue&& other);  // Оператор присваивания перемещением

  const T& front() const;  // Доступ к первому элементу
  const T& back() const;  // Доступ к последнему элементу

  bool empty() const;   // Проверка на пустоту
  size_t size() const;  // Получение размера

  void push(const T& value);  // Добавление элемента в конец
  void pop();  // Удаление элемента из начала
  void swap(queue& other);  // Обмен содержимым с другим очередью

  // Part 3 (Bonus)
  template <typename... Args>
  void insert_many_back(Args&&... args);
};
}  // namespace s21

#include "s21_queue.inc"

#endif  // SRC_S21_QUEUE_H
