#ifndef SRC_S21_VECTOR_H
#define SRC_S21_VECTOR_H

namespace s21 {

template <typename T>

class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // Вложенный класс итератора
  class iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // Конструктор
    iterator(T* ptr, size_type index);
    iterator(const iterator& other);

    iterator operator+(size_t offset) const;
    iterator operator-(size_t offset) const;
    size_t operator-(const iterator& other) const;
    T& operator*();
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    iterator& operator=(const iterator& other);

   private:
    T* ptr_;
    size_type index_;
  };

  // Constructors
  vector();
  vector(size_t n);
  vector(std::initializer_list<T> init);
  vector(const vector& v);
  vector(vector&& v);
  ~vector();

  // Assignment operators
  vector& operator=(const vector& v);
  vector& operator=(vector&& v) noexcept;

  // Element access
  T& at(size_t pos);
  T& operator[](size_t pos);
  T& front();
  T& back();
  T* data();

  // Методы для работы с итераторами
  iterator begin();
  iterator end();

  // Capacity
  bool empty() const;
  size_t size() const;
  size_t max_size() const;
  void reserve(size_t new_cap);
  size_t capacity() const;
  void shrink_to_fit();
  T&& move(T& obj);

  // Modifiers
  void clear();
  iterator insert(iterator pos, const T& value);
  void erase(iterator pos);
  void push_back(const T& value);
  void pop_back();
  void swap(vector& other);

  // Part 3 (Bonus)
  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);

 private:
  T* data_;          // Pointer to dynamically allocated array
  size_t size_;      // Number of elements in the vector
  size_t capacity_;  // Capacity of the vector
  size_t index_;
};

}  // namespace s21

#include "s21_vector.inc"

#endif  // SRC_S21_VECTOR_H
