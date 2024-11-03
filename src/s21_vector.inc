#include "s21_vector.h"

namespace s21 {

// Constructors
template <typename T>
vector<T>::vector() : data_(new T[0]), size_(0), capacity_(0), index_(0) {}

template <typename T>
vector<T>::vector(size_type n) : data_(new T[n]), size_(n), capacity_(n) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = T();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<T> init)
    : data_(new T[init.size()]),
      size_(init.size()),
      capacity_(init.size()),
      index_(0) {
  for (const T& item : init) {
    data_[index_++] = item;  // Копируем элементы
  }
}

template <typename T>
vector<T>::vector(const vector& v)
    : data_(new T[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_),
      index_(v.index_) {
  // Копируем элементы из другого вектора
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
}

template <typename T>
vector<T>::vector(vector&& v)
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_), index_(v.index_) {
  // Копируем элементы из другого вектора
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = v.data_[i];
  }
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
  v.index_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;
  size_ = 0;
  capacity_ = 0;
  index_ = 0;
}

// Assignment operators
template <typename T>
vector<T>& vector<T>::operator=(const vector& v) {
  if (this != &v) {
    vector temp(v);
    this->swap(temp);
  }
  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) noexcept {
  if (this != &v) {
    this->swap(v);
  }
  return *this;
}

// Element access
template <typename T>
T& vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T>
T& vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
T* vector<T>::data() {
  return data_;
}

template <typename T>
T& vector<T>::front() {
  return data_[0];
}

template <typename T>
T& vector<T>::back() {
  return data_[size_ - 1];
}

// Capacity
template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::reserve(size_type new_cap) {
  if (new_cap > capacity_) {
    T* new_data = new T[new_cap];  // Выделяем новую память

    // Копируем элементы
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = move(
          data_[i]);  // Используем std::move для перемещения, если возможно
    }

    delete[] data_;  // Освобождаем старую память
    data_ = new_data;  // Обновляем указатель на новые данные
    capacity_ = new_cap;  // Обновляем емкость
  }
}

// Modifiers
template <typename T>
void vector<T>::clear() {
  // Вызываем деструкторы для всех элементов вектора
  for (size_type i = 0; i < size_; ++i) {
    data_[i].~T();  // Явно вызываем деструктор для каждого элемента
  }

  // Сбрасываем размер вектора
  size_ = 0;
}

template <typename T>
void vector<T>::push_back(const T& value) {
  if (size_ == capacity_) {
    reserve(capacity_ ? 2 * capacity_ : 1);
  }
  data_[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1] = 0;
    --size_;  // Уменьшаем размер
    // Возможно, стоит уменьшить емкость (если нужно)
    if (size_ < capacity_) {
      reserve(capacity_ - 1);  // Уменьшаем емкость вдвое
    }
  }
}

template <typename T>
void vector<T>::swap(vector& other) {
  // Меняем указатели на данные
  T* temp_data = data_;
  data_ = other.data_;
  other.data_ = temp_data;

  // Меняем размер
  size_type temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;

  // Меняем емкость
  size_type temp_capacity = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = temp_capacity;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  // Вычислим максимальный размер, который может иметь вектор, в зависимости от
  // системы.
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T* new_data = new T[size_];  // Создаем новый массив точного размера
    index_ = size_;
    std::copy(begin(), end(),
              iterator(new_data, index_));  // Копируем текущие элементы
    delete[] data_;  // Удаляем старый массив
    data_ = new_data;  // Обновляем указатель на новый массив
    capacity_ = size_;  // Обновляем емкость
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos, const T& value) {
  // Рассчитать индекс позиции
  size_type index = pos - begin();

  // Если текущий размер равен ёмкости, нужно увеличить ёмкость
  if (size_ == capacity_) {
    reserve(capacity_ ? 2 * capacity_ : 1);  // Удваиваем ёмкость
  }

  // Сдвигаем элементы вправо, начиная с позиции index
  for (size_type i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }

  // Вставляем новое значение
  data_[index] = value;

  // Увеличиваем размер
  ++size_;

  // Возвращаем итератор на новое значение
  return begin() + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  // Сдвигаем элементы влево, начиная с позиции pos
  for (size_type i = pos - begin(); i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];  // Используем перемещение вместо копирования
  }
  // Уменьшаем размер вектора
  --size_;
  // Вызов деструктора для последнего элемента
  data_[size_].~T();  // Теперь деструктор вызывается для последнего элемента
}

template <typename T>
T&& vector<T>::move(T& obj) {
  return static_cast<T&&>(obj);
}

// Part 3
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(iterator pos,
                                                    Args&&... args) {
  size_t index = pos - begin();  // Вычисляем индекс, где нужно вставить
  size_t num_new_elements = sizeof...(args);  // Количество новых элементов

  if (size_ + num_new_elements > capacity_) {
    reserve((size_ + num_new_elements) * 2);  // Увеличиваем емкость, если нужно
  }

  // Сдвигаем элементы после позиции вставки
  for (size_t i = size_; i > index; --i) {
    data_[i + num_new_elements - 1] = move(data_[i - 1]);
  }

  // Вставляем новые элементы с перфектным forwarding
  size_t insertion_index = index;
  ((data_[insertion_index++] = std::forward<Args>(args)), ...);

  size_ += num_new_elements;  // Обновляем размер
  return begin() + index;  // Возвращаем итератор на первую вставленную позицию
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  size_t num_new_elements = sizeof...(args);  // Количество новых элементов

  if (size_ + num_new_elements > capacity_) {
    reserve((size_ + num_new_elements) * 2);  // Увеличиваем емкость, если нужно
  }

  // Вставляем новые элементы в конец
  T temp[] = {std::forward<Args>(args)...};  // Временный массив для вставки
  for (size_t i = 0; i < num_new_elements; ++i) {
    data_[size_++] = move(temp[i]);
  }
}

// Конструктор итератора
template <typename T>
vector<T>::iterator::iterator(T* ptr, size_t index)
    : ptr_(ptr), index_(index) {}

// Конструктор копирования для итератора
template <typename T>
vector<T>::iterator::iterator(const iterator& other)
    : ptr_(other.ptr_), index_(other.index_) {}

// Перегрузка оператора разыменования
template <typename T>
T& vector<T>::iterator::operator*() {
  return *ptr_;
}

// Перегрузка оператора инкремента (префиксный)
template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator++() {
  ++ptr_;
  return *this;
}

// Перегрузка оператора инкремента (постфиксный)
template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

// Перегрузка оператора декремента (префиксный)
template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator--() {
  --ptr_;
  return *this;
}

// Перегрузка оператора декремента (постфиксный)
template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

// Перегрузка оператора сравнения ==
template <typename T>
bool vector<T>::iterator::operator==(const iterator& other) const {
  return ptr_ == other.ptr_;
}

// Перегрузка оператора сравнения !=
template <typename T>
bool vector<T>::iterator::operator!=(const iterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator+(
    size_t offset) const {
  return iterator(ptr_ + offset, index_ + offset);
}

template <typename T>
typename vector<T>::iterator vector<T>::iterator::operator-(
    size_t offset) const {
  return iterator(ptr_ - offset, index_ - offset);
}

template <typename T>
typename vector<T>::size_type vector<T>::iterator::operator-(
    const iterator& other) const {
  return index_ - other.index_;  // Difference in indices
}

// Реализация методов begin() и end()
template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(data_, 0);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(data_ + size_, size_);
}

// Оператор присваивания для итератора
template <typename T>
typename vector<T>::iterator& vector<T>::iterator::operator=(
    const iterator& other) {
  if (this != &other) {  // Проверка на самоприсваивание
    this->ptr_ = other.ptr_;
    this->index_ = other.index_;
  }
  return *this;
}

}  // namespace s21
