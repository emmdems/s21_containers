#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>  // For std::allocator_traits

namespace s21 {

template <typename T>

class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node {
    value_type data;
    Node* next;
    Node* prev;
    Node(const value_type& value) : data(value), next(nullptr), prev(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  Node* end_;
  size_type size_;

 public:
  list();             // default constructor, creates empty list
  list(size_type n);  // parameterized constructor, creates the list of size n
  list(std::initializer_list<value_type> const&
           items);  // initializer list constructor, creates list initizialized
                    // using std::initializer_list
  list(const list& l);      // copy constructor
  list(list&& l) noexcept;  // move constructor
  ~list();                  // destructor

  list& operator=(const list& l);
  list& operator=(list&& l) noexcept;

  class ListIterator {
   private:
    Node* ptr_ = nullptr;
    friend class list<value_type>;

   public:
    ListIterator();
    ListIterator(Node* ptr);
    reference operator*();
    ListIterator operator++(int);
    ListIterator operator--(int);
    ListIterator& operator++();
    ListIterator& operator--();
    bool operator==(ListIterator other);
    bool operator!=(ListIterator other);
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    ListConstIterator(const ListIterator& ptr);
    const T& operator*();
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Element access
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size() const;
  size_type max_size();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // Containersplus
  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <class... Args>
  void insert_many_back(Args&&... args);
  template <class... Args>
  void insert_many_front(Args&&... args);

 private:  // Utils
  void change_end();
};

}  // namespace s21

#include "s21_list.inc"  // Здесь подключается файл с реализацией методов

#endif  // SRC_S21_LIST_H_
