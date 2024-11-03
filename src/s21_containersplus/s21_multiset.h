#ifndef S21_MULTISET_H_
#define S21_MULTISET_H_

#include <memory>  // For std::allocator_traits

#include "../s21_stack.h"
#include "../s21_vector.h"

namespace s21 {
template <typename T>
class multiset {
 public:
  using size_type = std::size_t;  // Определение size_type как std::size_t
  using Key = T;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const reference;

 private:
  enum Color { RED, BLACK, END };

  struct Node {
    Key value;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    // Конструктор для инициализации узла
    Node(const Key& val, Color c, Node* p)
        : value(val), left(nullptr), right(nullptr), parent(p), color(c) {}
  };

  Node* root_;
  size_type size_;

  // Внутренний класс итератора
 public:
  class iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;

    // Конструкторы
    iterator();
    iterator(Node* node);
    iterator(const iterator& other);

    // Операторы разыменования
    Key& operator*();
    // Оператор инкремента
    iterator& operator++();
    iterator operator++(int);
    // Оператор декремента
    iterator& operator--();
    iterator operator--(int);
    // Оператор сравнения
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;
    iterator& operator=(const iterator& other);

   private:
    Node* current_;  // Указатель на текущий узел
    friend class multiset;
    Node* find_min(Node* node);
    Node* find_max(Node* node);
  };

  // Constructors
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms) noexcept;

  // Destructor
  ~multiset();

  // Assignment operators
  // копирование
  multiset& operator=(const multiset& ms);
  // перемещение
  multiset& operator=(multiset&& ms) noexcept;

  // Iterators
  iterator begin() const;
  iterator end() const;

  // Capacity
  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const noexcept;

  // Modifiers
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  // Lookup
  bool contains(const Key& key) const;
  iterator find(const Key& key) const;
  size_type count(const Key& key) const;
  iterator lower_bound(const Key& key) const;
  iterator upper_bound(const Key& key) const;
  std::pair<iterator, iterator> equal_range(const Key& key) const;

  // Part3
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  // Приватные функции для балансировки и работы с деревом
  void balance_after_insert(Node* node);
  void balance_after_erase(Node* node, Node* parent);
  void rotate_left(Node* node);
  void rotate_right(Node* node);
  Node* find_min(Node* node) const;
  Node* find_max(Node* node) const;
};

}  // namespace s21

#include "s21_multiset.inc"
#endif  // S21_MULTISET_H_
