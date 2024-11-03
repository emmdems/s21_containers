#include "s21_list.h"

namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  change_end();
}

template <typename T>
list<T>::list(size_type n)
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  for (size_type i = 0; i < n; i++) push_back(0);
  change_end();
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  for (const auto& item : items) {
    push_back(item);
  }
  change_end();
}

template <typename T>
list<T>::list(const list& other) : list() {
  for (Node* curr = other.head_; curr != nullptr; curr = curr->next) {
    push_back(curr->data);
  }
}

template <typename T>
list<T>::list(list&& other) noexcept
    : head_(other.head_),
      tail_(other.tail_),
      end_(other.end_),
      size_(other.size_) {
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other) {
    clear();
    for (Node* curr = other.head_; curr != nullptr; curr = curr->next) {
      push_back(curr->data);
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (tail_) {
    tail_->next = new_node;
    new_node->prev = tail_;
    tail_ = new_node;
  } else {
    head_ = tail_ = new_node;
  }
  size_++;
  change_end();
}

template <typename T>
void list<T>::pop_back() {
  if (tail_) {
    Node* temp = tail_;
    tail_ = tail_->prev;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    delete temp;
    size_--;
    change_end();
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (head_) {
    head_->prev = new_node;
    new_node->next = head_;
    head_ = new_node;
  } else {
    head_ = tail_ = new_node;
  }
  size_++;
  change_end();
}

template <typename T>
void list<T>::pop_front() {
  if (head_) {
    Node* temp = head_;
    head_ = head_->next;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete temp;
    size_--;
    change_end();
  }
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::allocator_traits<std::allocator<Node>>::max_size(
      std::allocator<Node>());
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
bool list<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return head_ ? iterator(head_) : iterator(end_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(end_);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* newNode = new Node(value);
  Node* currentNode = pos.ptr_;
  if (empty()) {
    push_back(value);
  } else {
    newNode->next = currentNode;
    newNode->prev = currentNode->prev;
    currentNode->prev = newNode;
    if (newNode->prev) {
      newNode->prev->next = newNode;
    }
    size_++;
    if (pos == begin()) {
      head_ = newNode;
    }
  }
  change_end();
  return iterator(newNode);
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(other.head_, head_);
  std::swap(other.tail_, tail_);
  std::swap(other.size_, size_);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (!empty()) {
    if (pos == begin())
      pop_front();
    else if (pos.ptr_ == this->tail_)
      pop_back();
    else if (pos.ptr_ != nullptr) {
      Node* currentNode = pos.ptr_;
      currentNode->prev->next = currentNode->next;
      currentNode->next->prev = currentNode->prev;
      delete currentNode;
      size_--;
      end_->data--;
    }
  }
}

template <typename T>
void list<T>::merge(list& other) {
  if (this != &other) {
    this->sort();  // Both lists should be sorted
    other.sort();
    iterator it = other.begin();
    size_t n = other.size();
    for (size_t i = 0; i < n; i++) {
      this->push_back(*it);
      it++;
    }
    other.clear();
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (this != &other && !other.empty()) {
    iterator oth_it = other.begin();
    if (empty()) {
      for (size_t i = 0; i < other.size(); i++) {
        push_back(*oth_it);
        oth_it++;
      }
    } else {
      oth_it = other.begin();
      for (size_t i = 0; i < other.size(); i++) {
        insert(pos, *oth_it);
        oth_it++;
      }
    }
    change_end();
    other.clear();
  }
}

template <typename T>
void list<T>::reverse() {
  if (size() > 1) {
    list<T> tmp;
    iterator it = begin();
    for (size_t i = 0; i < size(); i++) {
      tmp.push_front(*it);
      it++;
    }
    *this = tmp;
    tmp.clear();
    change_end();
  }
}

template <typename T>
void list<T>::unique() {
  if (size() > 1) {
    T tmp = *begin();
    iterator it = begin();
    iterator it_next;
    it++;
    size_t list_size = size() - 1;
    for (size_t i = 0; i < list_size; i++) {
      it_next = it;
      if (i != list_size - 1) {
        it_next++;
      }
      if (tmp == *it) {
        erase(it);
        it = it_next;
      }
    }
    change_end();
  }
}

template <typename T>
void list<T>::sort() {
  if (size() > 1) {
    list<T> res;
    T min;
    iterator it;
    iterator it_min;
    while (size() > 0) {
      min = *begin();
      it = begin();
      it_min = begin();
      for (size_t i = 0; i < size(); i++) {
        if (*it < min) {
          min = *it;
          it_min = it;
        }
        it++;
      }
      res.push_back(min);
      erase(it_min);
    }
    *this = res;
    change_end();
  }
}

template <typename T>
void list<T>::change_end() {
  if (end_) {
    end_->prev = tail_;
    end_->data = size();
  }
}

template <class T>
template <class... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  if (empty()) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  } else {
    for (const auto& arg : {args...}) {
      insert(pos, arg);
    }
  }
  return pos;
}

template <class T>
template <class... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <class T>
template <class... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}

// SHINOJIC'S ADDITION

template <class T>
const T& list<T>::front() {
  if (head_) {
    return head_->data;
  } else {
    return end_->data;
  }
}

template <class T>
const T& list<T>::back() {
  if (tail_) {
    return tail_->data;
  } else {
    return end_->data;
  }
}

// Iterator's realization

template <class T>
list<T>::ListIterator::ListIterator() {
  ptr_ = nullptr;
}

template <class T>
list<T>::ListIterator::ListIterator(Node* ptr) {
  ptr_ = ptr;
}

template <typename T>
T& list<T>::ListIterator::operator*() {
  if (this->ptr_ == nullptr) {
    throw std::invalid_argument("This is nullptr");
  }
  return this->ptr_->data;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  ptr_ = ptr_->prev;
  return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
  ptr_ = ptr_->prev;
  return *this;
}

template <typename T>
bool list<T>::ListIterator::operator==(ListIterator other) {
  return this->ptr_ == other.ptr_;
}

template <typename T>
bool list<T>::ListIterator::operator!=(ListIterator other) {
  return this->ptr_ != other.ptr_;
}

template <class T>
list<T>::ListConstIterator::ListConstIterator() : ListIterator(){};

template <class T>
list<T>::ListConstIterator::ListConstIterator(const ListIterator& ptr)
    : ListIterator(ptr){};

template <typename T>
const T& list<T>::ListConstIterator::operator*() {
  return iterator ::operator*();
}

}  // namespace s21
