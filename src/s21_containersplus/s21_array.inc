#include "s21_array.h"

// Array Constructors

namespace s21 {

// Constructors

template <typename T, std::size_t N>
array<T, N>::array() {}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) {
  if (items.size() > N || items.size() > max_size()) {
    throw std::length_error("Too many elements for array");
  }
  std::copy(items.begin(), items.end(), data_);  // copies elements in the range
  if (items.size() < N) {
    for (size_t i = items.size(); i < N; i++) {
      data_[i] = T{};
    }
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array& a) {
  std::copy(a.begin(), a.end(), data_);
}

template <typename T, std::size_t N>
array<T, N>::array(array&& a) noexcept {
  for (size_t i = 0; i < N; i++) {
    data_[i] = a.data_[i];
    a.data_[i] = 0;
  }
}

template <typename T, std::size_t N>
array<T, N>::~array() {}

// Array Operators

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array& a) {
  if (this != &a) {
    std::copy(a.begin(), a.end(), data_);
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array&& a) noexcept {
  if (this != &a) {  // проверка на самоприсваивание
    // перемещение элементов из `a` в текущий объект
    std::move(a.data_, a.data_ + N, data_);
    // Обнуление исходного массива для безопасности
    std::fill(a.data_, a.data_ + N, T{});
  }
  return *this;
}

// Array Element access

template <typename T, std::size_t N>
T& array<T, N>::at(size_t pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of bounds");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
T& array<T, N>::operator[](size_t pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of bounds");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
const T& array<T, N>::front() const noexcept {
  return data_[0];
}

template <typename T, std::size_t N>
const T& array<T, N>::back() const noexcept {
  return (N == 0) ? data_[0] : data_[N - 1];
}

// Array Iterators

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return iterator(data_);  // Используем конструктор iter, передавая указатель
                           // на начало массива
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  // Конец массива указывает на позицию после последнего элемента
  return iterator(data_ + N);
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return ((N == 0) ? data_ + 1 : data_ + N);
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return iterator(data_);
}

// Array Capacity

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
  return (N == 0);
}

template <typename T, std::size_t N>
size_t array<T, N>::size() const noexcept {
  return N;
}

template <typename T, std::size_t N>
size_t array<T, N>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

// Array Modifiers

template <typename T, std::size_t N>
void array<T, N>::swap(array& other) noexcept {
  std::swap(data_, other.data_);
}

template <typename T, std::size_t N>
void array<T, N>::fill(const T& value) {
  for (size_t i = 0; i < N; i++) {
    data_[i] = value;
  }
}

// Iterator class

template <typename T, std::size_t N>
array<T, N>::iterator::iterator() : element(nullptr) {}

template <typename T, std::size_t N>
array<T, N>::iterator::iterator(T* ptr) : element(ptr) {}

template <typename T, std::size_t N>
T& array<T, N>::iterator::operator*() {
  return *element;
}

template <typename T, std::size_t N>
bool array<T, N>::iterator::operator==(iterator& other) {
  return element == other.element;
}

template <typename T, std::size_t N>
bool array<T, N>::iterator::operator!=(iterator& other) {
  return element != other.element;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::iterator::operator++(int) {
  element = element + 1;
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::iterator::operator--(int) {
  element = element - 1;
  return *this;
}

}  // namespace s21
