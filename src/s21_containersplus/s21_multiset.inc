#include "s21_multiset.h"

namespace s21 {

// Constructors
template <typename T>
multiset<T>::multiset() : root_(nullptr), size_(0) {}

template <typename T>
multiset<T>::multiset(std::initializer_list<T> const& items)
    : root_(nullptr), size_(0) {
  for (const T& value : items) {
    insert(value);  // Вставляем каждый элемент из списка инициализации
  }
}

// Конструктор копирования
template <typename T>
multiset<T>::multiset(const multiset& ms) : root_(nullptr), size_(0) {
  if (!ms.root_) return;  // Если исходное дерево пустое, просто выйти
  // Используем стек для обхода всех узлов и копирования дерева
  stack<Node*> stack;
  stack.push(ms.root_);
  while (!stack.empty()) {
    Node* original_node = stack.top();
    stack.pop();
    // Вставляем значение узла из исходного дерева
    insert(original_node->value);
    // Добавляем дочерние узлы в стек для дальнейшего копирования
    if (original_node->left) {
      stack.push(original_node->left);
    }
    if (original_node->right) {
      stack.push(original_node->right);
    }
  }
}

template <typename T>
multiset<T>::multiset(multiset&& ms) noexcept
    : root_(ms.root_), size_(ms.size_) {
  ms.root_ = nullptr;  // Обнуляем указатель на корень в перемещённом объекте
  ms.size_ = 0;  // Обнуляем размер в перемещённом объекте
}

// Destructor
template <typename T>
multiset<T>::~multiset() {
  clear();
}

// Assignment operators
template <typename T>
multiset<T>& multiset<T>::operator=(const multiset& ms) {
  if (this != &ms) {  // проверка на самоприсваивание
    multiset<T> temp(
        ms);  // Создаем временный объект через конструктор копирования
    swap(temp);  // Меняем содержимое временного объекта с текущим
    temp.~multiset();
  }
  return *this;
}

template <typename T>
multiset<T>& multiset<T>::operator=(multiset&& ms) noexcept {
  if (this != &ms) {
    swap(ms);  // Меняем содержимое временного объекта с текущим
    ms.~multiset();
  }
  return *this;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::begin() const {
  if (!root_) return iterator(root_);
  if (!root_->left) return iterator(root_);
  Node* first = find_min(root_->left);
  return iterator(first);
}

template <typename T>
typename multiset<T>::iterator multiset<T>::end() const {
  if (!root_) return iterator(root_);
  Node* last;
  if (root_->right) {
    last = find_max(root_->right);
    last->color = END;
  }
  return iterator(last);  // Возвращаем итератор на минимальный элемент
}

// Capacity
template <typename T>
bool multiset<T>::empty() const noexcept {
  return root_ == nullptr;
}

template <typename T>
typename multiset<T>::size_type multiset<T>::size() const {
  return size_;
}

template <typename T>
size_t multiset<T>::max_size() const noexcept {
  // Максимальный размер контейнера зависит от размера узла и максимального
  // размера памяти.
  return std::allocator_traits<std::allocator<Node>>::max_size(
      std::allocator<Node>());
}

template <typename T>
void multiset<T>::clear() {
  if (root_ != nullptr) {  // Если дерево пустое, ничего не делаем
    stack<Node*> node_stack;
    node_stack.push(root_);
    while (!node_stack.empty()) {
      Node* node = node_stack.top();
      node_stack.pop();
      // Сначала добавляем правого ребенка, затем левого
      // Порядок важен, так как левый будет обработан первым
      if (node->right != nullptr) {
        node_stack.push(node->right);
      }
      if (node->left != nullptr) {
        node_stack.push(node->left);
      }
      // Обнуляем указатели на детей перед удалением узла
      node->left = nullptr;
      node->right = nullptr;
      // Удаляем текущий узел
      delete node;
    }
    root_ = nullptr;  // Обнуляем указатель на корень
    size_ = 0;        // Обнуляем размер
  }
}

template <typename T>
typename multiset<T>::iterator multiset<T>::insert(const T& value) {
  Node* parent = nullptr;
  Node* current = root_;
  // Находим родителя для нового узла
  while (current != nullptr) {
    parent = current;
    if (*(&value) < current->value) {
      current = current->left;
    } else {
      // в том числе дубликаты вставляются в правое поддерево
      current = current->right;
    }
  }
  // Создаем новый узел, красим его в красный
  Node* new_node = new Node(value, RED, parent);
  // Вставляем новый узел в дерево
  if (root_ == nullptr) {
    root_ = new_node;  // Дерево было пустым, новый узел становится корнем
  } else if (*(&value) < parent->value) {
    parent->left = new_node;
  } else {
    parent->right = new_node;  // в том числе вставляем дубликаты
  }
  // Балансируем дерево после вставки
  balance_after_insert(new_node);
  // Увеличиваем количество узлов после вставки
  ++size_;
  return find(*(&value));
}

template <typename T>
void multiset<T>::erase(iterator pos) {
  if (pos == nullptr) return;
  // Получаем узел, соответствующий итератору
  Node* node_to_delete = pos.current_;
  Node* node = node_to_delete;
  Node* child = nullptr;
  Node* parent = nullptr;
  // Узел для удаления имеет двух детей
  if (node_to_delete->left != nullptr && node_to_delete->right != nullptr) {
    // Находим минимальный узел в правом поддереве (преемника)
    Node* successor = find_min(node_to_delete->right);
    // Заменяем значение удаляемого узла значением преемника
    node_to_delete->value = successor->value;
    // Теперь нужно удалить преемника
    node = successor;
    parent = node->parent;
    child = node->right;  // Преемник всегда будет иметь не более одного ребенка
                          // (правого)
  } else {
    // Узел для удаления имеет одного ребенка или не имеет детей
    child = (node->left != nullptr) ? node->left : node->right;
    parent = node->parent;
  }
  // Замещаем узел его ребенком
  if (child != nullptr) {
    if (parent == nullptr) {
      root_ = child;  // Если узел — это корень, обновляем корень
    } else if (node == parent->left) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    child->parent = parent;  // Устанавливаем родителя ребенка
  } else {
    // Если у узла нет детей
    if (parent == nullptr) {
      root_ = nullptr;  // Если узел — это корень, дерево становится пустым
    } else {
      if (node == parent->left) {
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    }
  }
  // Если удалённый узел был черным, выполняем балансировку
  balance_after_erase(child, parent);
  delete node;  // Удаляем узел
  size_--;      // Уменьшаем количество элементов
}

template <typename T>
void multiset<T>::swap(multiset& other) {
  // Обмениваем указатели на корни деревьев
  Node* temp_root = root_;
  root_ = other.root_;
  other.root_ = temp_root;
  // Обмениваем размеры множеств
  size_t temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <typename T>
void multiset<T>::merge(multiset& other) {
  size_t size = other.size();
  iterator merger = other.begin();
  for (size_t i = 0; i < size; i++) {
    insert(*merger);
    merger++;
  }
  other.clear();
}

template <typename T>
bool multiset<T>::contains(const T& value) const {
  if (size_ > 0) {
    if (find(value).current_->value == value) return true;
  }
  return false;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::find(const T& value) const {
  Node* result = nullptr;
  // Используем стек для обхода всех узлов и возврата первого совпадения
  stack<Node*> stack;
  stack.push(root_);
  while (!stack.empty()) {
    Node* original_node = stack.top();
    stack.pop();
    // Вставляем значение узла из исходного дерева
    if (*(&value) == original_node->value) {
      result = original_node;
      break;
    }
    // Добавляем дочерние узлы в стек для дальнейшего копирования
    if (original_node->left) {
      stack.push(original_node->left);
    }
    if (original_node->right) {
      stack.push(original_node->right);
    }
  }
  if (result != nullptr) {
    return iterator(result);  // Возвращаем первое вхождение
  }
  return end();  // Узел не найден
}

template <typename T>
size_t multiset<T>::count(const T& value) const {
  size_t occurrence_count = 0;
  // Используем стек для обхода всех узлов и подсчета дубликатов
  stack<Node*> stack;
  stack.push(root_);
  while (!stack.empty()) {
    Node* original_node = stack.top();
    stack.pop();
    // Вставляем значение узла из исходного дерева
    if (*(&value) == original_node->value) ++occurrence_count;
    // Добавляем дочерние узлы в стек для дальнейшего копирования
    if (original_node->left) {
      stack.push(original_node->left);
    }
    if (original_node->right) {
      stack.push(original_node->right);
    }
  }
  return occurrence_count;
}

template <typename T>
typename multiset<T>::iterator multiset<T>::lower_bound(const T& value) const {
  if (root_ == nullptr) return iterator(nullptr);
  Node* current = root_;
  Node* result = current;
  while (current != nullptr) {
    if (value > current->value) {
      current = current->right;  // Идем в левое поддерево
    } else {
      result = current;  // Сохраняем текущий узел как возможный результат
      current = current->left;  // Идем в правое поддерево
    }
  }
  if (value > result->value) {
    return iterator(nullptr);
  }
  return iterator(result);  // Возвращаем итератор на узел, >= value
}

template <typename T>
typename multiset<T>::iterator multiset<T>::upper_bound(const T& value) const {
  if (root_ == nullptr) return iterator(nullptr);
  Node* current = root_;
  Node* result = nullptr;
  if (value < *begin()) {
    return begin();
  }
  Node* max_val = root_;
  while (max_val->right) {
    max_val = max_val->right;
  }
  if (value > max_val->value) {
    return iterator(nullptr);
  }
  while (current != nullptr) {
    if (value < current->value) {
      current = current->left;  // Идем в левое поддерево
    } else {
      result = current;  // Сохраняем текущий узел как возможный результат
      current = current->right;  // Идем в правое поддерево
    }
  }
  iterator res(result);
  if (value >= result->value && *res != max_val->value) {
    res++;
  } else if (*res <= max_val->value) {
    return iterator(nullptr);
  }
  return res;  // Возвращаем итератор на узел, >= value
}

template <typename T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
multiset<T>::equal_range(const T& value) const {
  return {lower_bound(value), upper_bound(value)};
}

// Балансировка после вставки узла
template <typename T>
void multiset<T>::balance_after_insert(Node* node) {
  // Цикл продолжается, пока мы не вернулись к корню и родитель узла — красный
  while (node != root_ && node->parent && node->parent->color == RED) {
    Node* parent = node->parent;
    Node* grandparent = parent->parent;
    // Определяем дядю
    Node* uncle =
        (parent == grandparent->left) ? grandparent->right : grandparent->left;
    // Условие 1: Если дядя красный
    if (uncle && uncle->color == RED) {
      grandparent->color = RED;
      parent->color = BLACK;
      uncle->color = BLACK;
      node = grandparent;  // Продвигаемся вверх по дереву
    } else {
      // Условие 2: Родитель слева, узел справа
      if (node == parent->right && parent == grandparent->left) {
        rotate_left(parent);
        node = parent;
        parent = node->parent;
      }
      // Условие 3: Родитель справа, узел слева
      else if (node == parent->left && parent == grandparent->right) {
        rotate_right(parent);
        node = parent;
        parent = node->parent;
      }
      // Условие 4: Прямая ротация
      if (parent == grandparent->left) {
        rotate_right(grandparent);
      } else {
        rotate_left(grandparent);
      }
      // Меняем цвета родителя и дедушки
      std::swap(parent->color, grandparent->color);
      node = parent;
    }
  }
  // Условие 4: Корень должен быть черным
  root_->color = BLACK;
}

// Балансировка после удаления узла
template <typename T>
void multiset<T>::balance_after_erase(Node* node, Node* parent) {
  while (node != root_ && (node == nullptr || node->color == BLACK)) {
    Node* sibling = (node == parent->left) ? parent->right : parent->left;
    if (!sibling) break;
    // Случай 1: Брат узла красный
    if (sibling && sibling->color == RED) {
      sibling->color = BLACK;
      parent->color = RED;
      if (node == parent->left) {
        rotate_left(parent);
      } else {
        rotate_right(parent);
      }
      // Обновляем ссылку на брата
      sibling = (node == parent->left) ? parent->right : parent->left;
    }
    // Случай 2: Оба ребенка брата черные
    if (sibling && (!sibling->left || sibling->left->color == BLACK) &&
        (!sibling->right || sibling->right->color == BLACK)) {
      sibling->color = RED;
      node = parent;
      parent = node->parent;
    } else {
      // Случай 3: Левый ребенок брата красный, а правый черный
      if (sibling && (!sibling->right || sibling->right->color == BLACK)) {
        if (sibling->left) sibling->left->color = BLACK;
        sibling->color = RED;
        if (node == parent->left)
          rotate_right(sibling);
        else
          rotate_left(sibling);
        // Обновляем ссылку на брата
        sibling = (node == parent->left) ? parent->right : parent->left;
      }
      // Случай 4: Правый ребенок брата красный (если node - левый)
      if (sibling) {
        sibling->color = parent->color;
        parent->color = BLACK;
        if (node == parent->left) {
          if (sibling->right) sibling->right->color = BLACK;
          rotate_left(parent);
        } else {
          if (sibling->left) sibling->left->color = BLACK;
          rotate_right(parent);
        }
        node = root_;  // Завершить цикл
      }
    }
  }
  // Завершаем цикл, делаем узел черным
  if (node) node->color = BLACK;
}

template <typename T>
void multiset<T>::rotate_left(Node* node) {
  Node* right_child = node->right;
  // Проверка на null
  if (right_child == nullptr) return;
  node->right =
      right_child->left;  // Левое поддерево правого потомка становится правым
                          // поддеревом текущего узла
  if (right_child->left != nullptr) {
    right_child->left->parent =
        node;  // Перепривязываем родителя для нового потомка
  }
  right_child->parent =
      node->parent;  // Перепривязываем родителя для нового узла
  // Если узел был корнем, обновляем корень
  if (node->parent == nullptr) {
    root_ = right_child;
  } else if (node == node->parent->left) {
    node->parent->left = right_child;
  } else {
    node->parent->right = right_child;
  }
  right_child->left = node;  // Узел становится левым потомком нового родителя
  node->parent = right_child;  // Узел привязывается к новому родителю
}

template <typename T>
void multiset<T>::rotate_right(Node* node) {
  Node* left_child = node->left;
  // Проверка на null
  if (left_child == nullptr) return;
  node->left = left_child->right;  // Правое поддерево левого потомка становится
                                   // левым поддеревом текущего узла
  if (left_child->right != nullptr) {
    left_child->right->parent =
        node;  // Перепривязываем родителя для нового потомка
  }
  left_child->parent =
      node->parent;  // Перепривязываем родителя для нового узла
  // Если узел был корнем, обновляем корень
  if (node->parent == nullptr) {
    root_ = left_child;
  } else if (node == node->parent->right) {
    node->parent->right = left_child;
  } else {
    node->parent->left = left_child;
  }
  left_child->right = node;  // Узел становится правым потомком нового родителя
  node->parent = left_child;  // Узел привязывается к новому родителю
}

// Part 3
template <typename T>
template <typename... Args>
vector<std::pair<typename multiset<T>::iterator, bool>>
multiset<T>::insert_many(Args&&... args) {
  vector<std::pair<iterator, bool>> results;

  // Проверка, пустой ли список аргументов
  if constexpr (sizeof...(args) > 0) {
    for (const auto& value : {std::forward<Args>(args)...}) {
      auto it = insert(value);  // вставка значения
      bool inserted = it == find(value);  // проверка, является ли элемент новым
      results.push_back({it, inserted});
    }
  }

  return results;
}

// Конструктор итератора
template <typename T>
multiset<T>::iterator::iterator(Node* node) : current_(node) {}

// Конструктор по умолчанию
template <typename T>
multiset<T>::iterator::iterator() : current_(nullptr) {}

// Конструктор копирования
template <typename T>
multiset<T>::iterator::iterator(const iterator& other)
    : current_(other.current_) {}

template <typename T>
T& multiset<T>::iterator::operator*() {
  return current_->value;  // Возвращаем значение узла
}

// Оператор сравнения
template <typename T>
bool multiset<T>::iterator::operator==(const iterator& other) const {
  return current_ == other.current_;
}

template <typename T>
bool multiset<T>::iterator::operator!=(const iterator& other) const {
  return current_ != other.current_;
}

// Оператор присваивания для итератора
template <typename T>
typename multiset<T>::iterator& multiset<T>::iterator::operator=(
    const iterator& other) {
  if (this != &other) {  // Проверка на самоприсваивание
    this->current_ = other.current_;
  }
  return *this;
}

// Перегрузка оператора инкремента (постфиксный)
template <typename T>
typename multiset<T>::iterator multiset<T>::iterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

// Перегрузка оператора декремента (постфиксный)
template <typename T>
typename multiset<T>::iterator multiset<T>::iterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

// Оператор инкремента (движение вперед)
template <typename T>
typename multiset<T>::iterator& multiset<T>::iterator::operator++() {
  if (current_->right) {
    // Если есть правый потомок, идем в минимальный узел правого поддерева
    current_ = find_min(current_->right);
  } else {
    // Идем вверх по дереву, пока не найдем родителя, который больше текущего
    // узла
    Node* parent = current_->parent;
    while (parent && current_ == parent->right) {
      current_ = parent;
      parent = parent->parent;
    }
    current_ = parent;
  }
  return *this;
}

// Оператор декремента (движение назад)
template <typename T>
typename multiset<T>::iterator& multiset<T>::iterator::operator--() {
  if (current_->left) {
    // Если есть левый потомок, идем в максимальный узел левого поддерева
    current_ = find_max(current_->left);
  } else if (current_->color != END) {
    // Идем вверх по дереву, пока не найдем родителя, который меньше текущего
    // узла
    Node* parent = current_->parent;
    while (parent && current_ == parent->left) {
      current_ = parent;
      parent = parent->parent;
    }
    current_ = parent;
  }
  return *this;
}

template <typename T>
typename multiset<T>::Node* multiset<T>::iterator::find_min(Node* node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename T>
typename multiset<T>::Node* multiset<T>::iterator::find_max(Node* node) {
  // Находим самый правый узел в поддереве
  while (node && node->right) {
    node = node->right;
  }
  return node;
}

// Вспомогательные функции для поиска минимального и максимального узла
template <typename T>
typename multiset<T>::Node* multiset<T>::find_min(Node* node) const {
  while (node->left) {
    node = node->left;
  }
  return node;
}

template <typename T>
typename multiset<T>::Node* multiset<T>::find_max(Node* node) const {
  while (node->right) {
    node = node->right;
  }
  return node;
}

}  // namespace s21
