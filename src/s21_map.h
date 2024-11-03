#ifndef S21_MAP_H_
#define S21_MAP_H_

#include <memory>  // For std::allocator_traits
#include <stdexcept>

#include "s21_stack.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using size_type = std::size_t;  // Определение size_type как std::size_t
  using mapped_type = T;
  using key_type = Key;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const reference;

 private:
  enum Color { RED, BLACK, END };

  struct Node {
    value_type value;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(const value_type& val, Color c, Node* p)
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
    value_type& operator*();
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
    friend class map;
    Node* find_min(Node* node);
    Node* find_max(Node* node);
  };

  // Constructors
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) noexcept;

  // Destructor
  ~map();

  // Assignment operators
  // копирование
  map& operator=(const map& m);
  // перемещение
  map& operator=(map&& m) noexcept;

  T& at(const Key& key);
  T& operator[](const Key& key);

  // Iterators
  iterator begin() const;
  iterator end() const;

  // Capacity
  bool empty() const noexcept;
  size_type size() const;
  size_type max_size() const noexcept;

  // Modifiers
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  // Lookup
  bool contains(const Key& key) const;

  // Part3
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  // Приватные функции для балансировки и работы с деревом
  iterator find(const Key& key) const;
  void balance_after_insert(Node* node);
  void balance_after_erase(Node* node, Node* parent);
  void rotate_left(Node* node);
  void rotate_right(Node* node);
  Node* find_min(Node* node) const;
  Node* find_max(Node* node) const;
};

}  // namespace s21

#include "s21_map.inc"
#endif  // S21_MAP_H_