#include "s21_map.h"

namespace s21 {

// Constructors
template <typename Key, typename T>
map<Key, T>::map() : root_(nullptr), size_(0) {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items)
    : root_(nullptr), size_(0) {
  for (const auto& item : items) {
    insert(item);
  }
}

// Конструктор копирования
template <typename Key, typename T>
map<Key, T>::map(const map& ms) : root_(nullptr), size_(0) {
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

template <typename Key, typename T>
map<Key, T>::map(map&& s) noexcept : root_(s.root_), size_(s.size_) {
  s.root_ = nullptr;  // Обнуляем указатель на корень в перемещённом объекте
  s.size_ = 0;  // Обнуляем размер в перемещённом объекте
}

// Destructor
template <typename Key, typename T>
map<Key, T>::~map() {
  clear();
}

// Assignment operators
template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(const map& ms) {
  if (this != &ms) {  // проверка на самоприсваивание
    map<Key, T> temp(
        ms);  // Создаем временный объект через конструктор копирования
    swap(temp);  // Меняем содержимое временного объекта с текущим
    temp.~map();
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& ms) noexcept {
  if (this != &ms) {
    swap(ms);  // Меняем содержимое временного объекта с текущим
    ms.~map();
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() const {
  if (!root_) return iterator(root_);
  if (!root_->left) return iterator(root_);
  Node* first = find_min(root_->left);
  return iterator(first);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() const {
  if (!root_) return iterator(root_);
  Node* last;
  if (root_->right) {
    last = find_max(root_->right);
    last->color = END;
  }
  return iterator(last);  // Возвращаем итератор на минимальный элемент
}

// Capacity
template <typename Key, typename T>
bool map<Key, T>::empty() const noexcept {
  return size_ == 0;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const {
  return size_;
}

template <typename Key, typename T>
size_t map<Key, T>::max_size() const noexcept {
  // Используем стандартный аллокатор для получения максимального размера
  return std::allocator_traits<std::allocator<Node>>::max_size(
      std::allocator<Node>());
}

template <typename Key, typename T>
void map<Key, T>::clear() {
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

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  if (contains(key)) {
    // Ищем узел с данным ключом
    iterator iter = find(key);
    // Если ключ найден, обновляем значение и возвращаем пару с итератором на
    // существующий элемент и `false`
    iter.current_->value.second = obj;
    return {iter, false};
  } else {
    // Если ключ не найден, вставляем новый узел с данным ключом и значением
    auto result = insert({key, obj});
    // Возвращаем пару с итератором на новый элемент и `true`
    return {result.first, true};
  }
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  if (contains(value.first)) {
    auto exist = find(*(&value.first));
    return {exist, false};
  }
  Node* parent = nullptr;
  Node* current = root_;
  // Находим родителя для нового узла
  while (current != nullptr) {
    parent = current;
    if (*(&value.first) < current->value.first) {
      current = current->left;
    } else {
      // в том числе дубликаты вставляются в правое поддерево
      current = current->right;
    }
  }
  // Создаем новый узел, красим его в красный
  // Node* new_node = new Node(value.first, value.second, RED, parent);
  Node* new_node = new Node(value, RED, parent);
  // Вставляем новый узел в дерево
  if (root_ == nullptr) {
    root_ = new_node;  // Дерево было пустым, новый узел становится корнем
  } else if (*(&value.first) < parent->value.first) {
    parent->left = new_node;
  } else {
    parent->right = new_node;  // в том числе вставляем дубликаты
  }
  // Балансируем дерево после вставки
  balance_after_insert(new_node);
  // Увеличиваем количество узлов после вставки
  ++size_;
  // return find(*(&value));
  return {find(*(&value.first)), true};
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  if (pos == nullptr) {
    return;
  }

  if (!(contains(pos.current_->value.first) &&
        find(pos.current_->value.first).current_->value.second ==
            pos.current_->value.second)) {
    throw std::out_of_range("Iterator not found in map");
  }

  Node* node_to_delete = pos.current_;
  Node* child = nullptr;
  Node* parent = nullptr;
  bool original_color = node_to_delete->color;

  // Узел для удаления имеет двух детей
  if (node_to_delete->left != nullptr && node_to_delete->right != nullptr) {
    // Находим преемника (наименьший узел в правом поддереве)
    Node* successor = find_min(node_to_delete->right);
    original_color = successor->color;
    child = successor
                ->right;  // Преемник всегда будет иметь не более одного ребенка
    parent = successor->parent;

    // Перемещаем указатели, заменяя удаляемый узел на его преемника
    if (successor->parent != node_to_delete) {
      if (child) child->parent = successor->parent;
      successor->parent->left = child;
      successor->right = node_to_delete->right;
      node_to_delete->right->parent = successor;
    }
    successor->parent = node_to_delete->parent;
    successor->left = node_to_delete->left;
    node_to_delete->left->parent = successor;

    if (node_to_delete->parent == nullptr) {
      root_ = successor;
    } else if (node_to_delete == node_to_delete->parent->left) {
      node_to_delete->parent->left = successor;
    } else {
      node_to_delete->parent->right = successor;
    }

    successor->color = node_to_delete->color;

  } else {  // Узел для удаления имеет одного ребенка или не имеет детей
    child = (node_to_delete->left != nullptr) ? node_to_delete->left
                                              : node_to_delete->right;
    parent = node_to_delete->parent;

    if (child != nullptr) {
      child->parent = parent;
    }

    if (parent == nullptr) {
      root_ = child;
    } else if (node_to_delete == parent->left) {
      parent->left = child;
    } else {
      parent->right = child;
    }
  }

  // Если удалённый узел был черным, выполняем балансировку
  if (original_color == BLACK) {
    balance_after_erase(child, parent);
  }

  delete node_to_delete;  // Удаляем узел
  --size_;  // Уменьшаем количество элементов
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  // Обмениваем указатели на корни деревьев
  Node* temp_root = root_;
  root_ = other.root_;
  other.root_ = temp_root;
  // Обмениваем размеры множеств
  size_t temp_size = size_;
  size_ = other.size_;
  other.size_ = temp_size;
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  size_t size = other.size();
  iterator merger = other.begin();
  for (size_t i = 0; i < size; i++) {
    try {
      if (this->at(merger.current_->value.first)) {
      }
    } catch (const std::out_of_range&) {
      // Ключ не найден, добавляем элемент в текущий map
      insert(*merger);
      other.erase(merger);
    }
    merger++;
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& value) const {
  if (size_ > 0) {
    if (find(value).current_->value.first == value) return true;
  }
  return false;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key& value) const {
  Node* result = nullptr;
  // Используем стек для обхода всех узлов и возврата первого совпадения
  stack<Node*> stack;
  stack.push(root_);
  while (!stack.empty()) {
    Node* original_node = stack.top();
    stack.pop();
    // Вставляем значение узла из исходного дерева
    if (*(&value) == original_node->value.first) {
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

// Балансировка после вставки узла
template <typename Key, typename T>
void map<Key, T>::balance_after_insert(Node* node) {
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
template <typename Key, typename T>
void map<Key, T>::balance_after_erase(Node* node, Node* parent) {
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
      sibling = (node == parent->left)
                    ? parent->right
                    : parent->left;  // Обновляем ссылку на брата
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
        if (node == parent->left) {
          rotate_right(sibling);
        } else {
          rotate_left(sibling);
        }
        sibling = (node == parent->left)
                      ? parent->right
                      : parent->left;  // Обновляем ссылку на брата
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

template <typename Key, typename T>
void map<Key, T>::rotate_left(Node* node) {
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

template <typename Key, typename T>
void map<Key, T>::rotate_right(Node* node) {
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
template <typename Key, typename T>
template <typename... Args>
vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  vector<std::pair<iterator, bool>> results;
  // Проверка, пустой ли список аргументов
  if constexpr (sizeof...(args) > 0) {
    auto values = {std::forward<Args>(args)...};
    for (const auto& value : values) {
      auto it = insert(value).first;  // вставка значения
      bool inserted =
          it == find(value.first);  // проверка, является ли элемент новым
      results.push_back({it, inserted});
    }
  }
  return results;
}

// Конструктор итератора
template <typename Key, typename T>
map<Key, T>::iterator::iterator(Node* node) : current_(node) {}

// Конструктор по умолчанию
template <typename Key, typename T>
map<Key, T>::iterator::iterator() : current_(nullptr) {}

// Конструктор копирования
template <typename Key, typename T>
map<Key, T>::iterator::iterator(const iterator& other)
    : current_(other.current_) {}

template <typename Key, typename T>
typename map<Key, T>::value_type& map<Key, T>::iterator::operator*() {
  return current_->value;  // Возвращаем пару ключ-значение узла
}

// Оператор сравнения
template <typename Key, typename T>
bool map<Key, T>::iterator::operator==(const iterator& other) const {
  return current_ == other.current_;
}

template <typename Key, typename T>
bool map<Key, T>::iterator::operator!=(const iterator& other) const {
  return current_ != other.current_;
}

// Оператор присваивания для итератора
template <typename Key, typename T>
typename map<Key, T>::iterator& map<Key, T>::iterator::operator=(
    const iterator& other) {
  if (this != &other) {  // Проверка на самоприсваивание
    this->current_ = other.current_;
  }
  return *this;
}

// Перегрузка оператора инкремента (постфиксный)
template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::iterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

// Перегрузка оператора декремента (постфиксный)
template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::iterator::operator--(int) {
  iterator tmp = *this;
  --(*this);
  return tmp;
}

// Оператор инкремента (движение вперед)
template <typename Key, typename T>
typename map<Key, T>::iterator& map<Key, T>::iterator::operator++() {
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
template <typename Key, typename T>
typename map<Key, T>::iterator& map<Key, T>::iterator::operator--() {
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

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::iterator::find_min(Node* node) {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::iterator::find_max(Node* node) {
  // Находим самый правый узел в поддереве
  while (node && node->right) {
    node = node->right;
  }
  return node;
}

// Вспомогательные функции для поиска минимального и максимального узла
template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::find_min(Node* node) const {
  while (node->left) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename T>
typename map<Key, T>::Node* map<Key, T>::find_max(Node* node) const {
  while (node->right) {
    node = node->right;
  }
  return node;
}

template <typename Key, typename T>
T& s21::map<Key, T>::at(const Key& key) {
  if (contains(key)) {
    Node* node = find(key).current_;  // Используем метод find для поиска узла
    return node->value.second;  // Возвращаем значение, если узел найден
  } else {
    throw std::out_of_range("Key not found in map");
  }
}

template <typename Key, typename T>
T& s21::map<Key, T>::operator[](const Key& key) {
  if (contains(key)) {
    // Ищем элемент с заданным ключом
    Node* node = find(key).current_;
    // Если элемент найден, возвращаем его значение
    return node->value.second;
  } else {
    // Если элемент не найден, вставляем новый элемент с ключом и значением по
    // умолчанию
    auto [iter, inserted] = insert({key, T()});
    return iter.current_->value.second;
  }
}

}  // namespace s21
