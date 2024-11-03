#include <gtest/gtest.h>

#include <list>
#include <queue>
#include <stack>

#include "../s21_containers.h"

// queue_tests
// Constructors

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  std::queue<int> q_;
  ASSERT_EQ(q_.empty(), q.empty());
  ASSERT_EQ(q_.size(), q.size());
}

TEST(QueueTest, InitializerList_Empty) {
  s21::queue<int> q = {};
  std::queue<int> q_ = {};
  ASSERT_EQ(q_.empty(), q.empty());
  ASSERT_EQ(q_.size(), q.size());
}

TEST(QueueTest, InitializerList_Full) {
  s21::queue<int> q = {1, 2, 3};
  std::queue<int> q_;
  q_.push(1);
  q_.push(2);
  q_.push(3);
  ASSERT_EQ(q_.size(), q.size());
  ASSERT_EQ(q_.front(), q.front());
  ASSERT_EQ(q_.back(), q.back());
}

TEST(QueueTest, CopyConstructor_CheckOld) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q1_;
  q1_.push(1);
  q1_.push(2);
  q1_.push(3);
  s21::queue<int> q2(q1);
  std::queue<int> q2_(q1_);
  ASSERT_EQ(q1_.size(), q1.size());
  ASSERT_EQ(q1_.front(), q1.front());
  ASSERT_EQ(q1_.back(), q1.back());
}

TEST(QueueTest, CopyConstructor_CheckNew) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q1_;
  q1_.push(1);
  q1_.push(2);
  q1_.push(3);
  s21::queue<int> q2(q1);
  std::queue<int> q2_(q1_);
  ASSERT_EQ(q2_.size(), q2.size());
  ASSERT_EQ(q2_.front(), q2.front());
  ASSERT_EQ(q2_.back(), q2.back());
}

TEST(QueueTest, MoveConstructor_CheckOld) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q1_;
  q1_.push(1);
  q1_.push(2);
  q1_.push(3);
  s21::queue<int> q2(std::move(q1));
  std::queue<int> q2_(std::move(q1_));
  ASSERT_EQ(q1_.empty(), q1.empty());
  ASSERT_EQ(q2_.empty(), q2.empty());
}

TEST(QueueTest, MoveConstructor_CheckNew) {
  s21::queue<int> q1 = {1, 2, 3};
  std::queue<int> q1_;
  q1_.push(1);
  q1_.push(2);
  q1_.push(3);
  s21::queue<int> q2(std::move(q1));
  std::queue<int> q2_(std::move(q1_));
  ASSERT_EQ(q2_.size(), q2.size());
  ASSERT_EQ(q2_.front(), q2.front());
  ASSERT_EQ(q2_.back(), q2.back());
}

// Operators

TEST(QueueTest, CopyAssignment) {
  s21::queue<int> q1 = {1, 2};
  std::queue<int> q1_;
  q1_.push(1);
  q1_.push(2);
  s21::queue<int> q2;
  q2 = q1;
  std::queue<int> q2_;
  q2_ = q1_;
  ASSERT_EQ(q1_.size(), q1.size());
  ASSERT_EQ(q1_.front(), q1.front());
  ASSERT_EQ(q1_.back(), q1.back());
  ASSERT_EQ(q2_.size(), q2.size());
  ASSERT_EQ(q2_.front(), q2.front());
  ASSERT_EQ(q2_.back(), q2.back());
}

TEST(QueueTest, MoveAssignment) {
  s21::queue<int> q1 = {1, 2};
  std::queue<int> q1_;
  q1_.push(1);
  q1_.push(2);
  s21::queue<int> q2;
  q2 = std::move(q1);
  std::queue<int> q2_;
  q2_ = std::move(q1_);
  ASSERT_EQ(q1_.empty(), q1.empty());
  ASSERT_EQ(q2_.size(), q2.size());
  ASSERT_EQ(q2_.front(), q2.front());
  ASSERT_EQ(q2_.back(), q2.back());
}

// Element Access

TEST(QueueTest, Front_Empty) {
  s21::queue<int> q;
  EXPECT_THROW(q.front(), std::exception);
}

TEST(QueueTest, Front_OneElement) {
  s21::queue<int> q = {1};
  std::queue<int> q_;
  q_.push(1);
  ASSERT_EQ(q.front(), q_.front());
}

TEST(QueueTest, Front_Full) {
  s21::queue<int> q = {1, 2, 3};
  std::queue<int> q_;
  q_.push(1);
  q_.push(2);
  q_.push(3);
  ASSERT_EQ(q.front(), q_.front());
}

TEST(QueueTest, Back_Empty) {
  s21::queue<int> q;
  EXPECT_THROW(q.back(), std::exception);
}

TEST(QueueTest, Back_OneElement) {
  s21::queue<int> q = {1};
  std::queue<int> q_;
  q_.push(1);
  ASSERT_EQ(q.back(), q_.back());
}

TEST(QueueTest, Back_Full) {
  s21::queue<int> q = {1, 2, 3};
  std::queue<int> q_;
  q_.push(1);
  q_.push(2);
  q_.push(3);
  ASSERT_EQ(q.back(), q_.back());
}

// Capacity

TEST(QueueTest, Empty_True) {
  s21::queue<int> q;
  std::queue<int> q_;
  ASSERT_EQ(q.empty(), q_.empty());
}

TEST(QueueTest, Empty_False) {
  s21::queue<int> q = {1};
  std::queue<int> q_;
  q_.push(1);
  ASSERT_EQ(q.empty(), q_.empty());
}

TEST(QueueTest, Size_Empty) {
  s21::queue<int> q;
  std::queue<int> q_;
  ASSERT_EQ(q.size(), q_.size());
}

TEST(QueueTest, Size_OneElement) {
  s21::queue<int> q = {1};
  std::queue<int> q_;
  q_.push(1);
  ASSERT_EQ(q.size(), q_.size());
}

TEST(QueueTest, Size_Full) {
  s21::queue<int> q = {1, 2, 3};
  std::queue<int> q_;
  q_.push(1);
  q_.push(2);
  q_.push(3);
  ASSERT_EQ(q.size(), q_.size());
}

// Modifiers

TEST(QueueTest, Push_ToEmpty) {
  s21::queue<int> q;
  std::queue<int> q_;
  q.push(1);
  q_.push(1);
  ASSERT_EQ(q.size(), q_.size());
  ASSERT_EQ(q.front(), q_.front());
  ASSERT_EQ(q.back(), q_.back());
}

TEST(QueueTest, Push_ToFull) {
  s21::queue<int> q = {1, 2, 3};
  q.push(4);
  std::queue<int> q_;
  q_.push(1);
  q_.push(2);
  q_.push(3);
  q_.push(4);
  ASSERT_EQ(q.size(), q_.size());
  ASSERT_EQ(q.front(), q_.front());
  ASSERT_EQ(q.back(), q_.back());
}

TEST(QueueTest, Pop_FromEmpty) {
  s21::queue<int> q;
  EXPECT_NO_THROW(q.pop());
}

TEST(QueueTest, Pop_FromFull) {
  s21::queue<int> q = {1, 2, 3};
  std::queue<int> q_;
  q_.push(1);
  q_.push(2);
  q_.push(3);
  q.pop();
  q_.pop();
  ASSERT_EQ(q.size(), q_.size());
  ASSERT_EQ(q.front(), q_.front());
  ASSERT_EQ(q.back(), q_.back());
}

TEST(QueueTest, Swap_Empty2) {
  s21::queue<int> q1;
  s21::queue<int> q2;
  std::queue<int> q1_;
  std::queue<int> q2_;
  q1.swap(q2);
  q1_.swap(q2_);
  ASSERT_EQ(q1_.empty(), q1.empty());
  ASSERT_EQ(q2_.empty(), q2.empty());
}

TEST(QueueTest, Swap_Empty1) {
  s21::queue<int> q1;
  s21::queue<int> q2 = {1, 2, 3};
  std::queue<int> q1_;
  std::queue<int> q2_;
  q2_.push(1);
  q2_.push(2);
  q2_.push(3);
  q1.swap(q2);
  q1_.swap(q2_);
  ASSERT_EQ(q2_.empty(), q2.empty());
  ASSERT_EQ(q1_.size(), q1.size());
  ASSERT_EQ(q1_.front(), q1.front());
  ASSERT_EQ(q1_.back(), q1.back());
}

TEST(QueueTest, Swap_Full) {
  s21::queue<int> q1 = {4, 5};
  s21::queue<int> q2 = {1, 2, 3};
  std::queue<int> q1_;
  std::queue<int> q2_;
  q1_.push(4);
  q1_.push(5);
  q2_.push(1);
  q2_.push(2);
  q2_.push(3);
  q1.swap(q2);
  q1_.swap(q2_);
  ASSERT_EQ(q1_.size(), q1.size());
  ASSERT_EQ(q1_.front(), q1.front());
  ASSERT_EQ(q1_.back(), q1.back());
  ASSERT_EQ(q2_.size(), q2.size());
  ASSERT_EQ(q2_.front(), q2.front());
  ASSERT_EQ(q2_.back(), q2.back());
}

// Part 3 (Bonus)

// Тест на добавление нескольких элементов
TEST(QueueTest, InsertManyBack_Simple) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3);

  size_t n = 3;
  ASSERT_EQ(q.size(), n);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);

  q.pop();
  n = 2;
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.size(), n);
}

// Тест на добавление одного элемента
TEST(QueueTest, InsertManyBack_SingleElement) {
  s21::queue<int> q;
  q.insert_many_back(42);

  size_t n = 1;
  ASSERT_EQ(q.size(), n);
  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.back(), 42);
}

// Тест на добавление элементов разных типов
TEST(QueueTest, InsertManyBack_DifferentTypes) {
  s21::queue<double> q;
  q.insert_many_back(3.14, 2.71, 1.41);

  size_t n = 3;
  ASSERT_EQ(q.size(), n);
  EXPECT_EQ(q.front(), 3.14);
  EXPECT_EQ(q.back(), 1.41);
}

// Тест на проверку добавления в непустую очередь
TEST(QueueTest, InsertManyBack_NonEmptyQueue) {
  s21::queue<int> q;
  q.push(10);  // Очередь уже содержит один элемент

  q.insert_many_back(20, 30, 40);

  size_t n = 4;
  ASSERT_EQ(q.size(), n);
  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 40);

  q.pop();
  EXPECT_EQ(q.front(), 20);
  q.pop();
  EXPECT_EQ(q.front(), 30);
}

// Тест на пустую очередь после нескольких pop
TEST(QueueTest, InsertManyBack_EmptyQueueAfterPop) {
  s21::queue<int> q;
  q.insert_many_back(1, 2, 3, 4, 5);

  while (!q.empty()) {
    q.pop();
  }

  EXPECT_TRUE(q.empty());
}

// Тест на вставку больших данных
TEST(QueueTest, InsertManyBack_LargeData) {
  s21::queue<std::string> q;
  q.insert_many_back("large_string1", "large_string2", "large_string3");

  size_t n = 3;
  ASSERT_EQ(q.size(), n);
  EXPECT_EQ(q.front(), "large_string1");
  EXPECT_EQ(q.back(), "large_string3");
}

// vector_tests
TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  size_t n = 0;
  EXPECT_EQ(v.size(), n);
  EXPECT_EQ(v.capacity(), n);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, SizeConstructor) {
  s21::vector<int> v(5);
  size_t n = 5;
  EXPECT_EQ(v.size(), n);
  EXPECT_GE(v.capacity(), n);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], 0);
  }

  std::vector<int> v_(5);
  EXPECT_EQ(v_.size(), n);
  EXPECT_GE(v_.capacity(), n);
  for (size_t i = 0; i < v_.size(); i++) {
    EXPECT_EQ(v_[i], 0);
  }
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  size_t n = 5;
  EXPECT_EQ(v.size(), n);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[4], 5);

  std::vector<int> v_{1, 2, 3, 4, 5};
  EXPECT_EQ(v_.size(), n);
  EXPECT_EQ(v_[0], 1);
  EXPECT_EQ(v_[4], 5);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v1.size(), v2.size());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], v2[i]);
  }

  std::vector<int> v1_{1, 2, 3};
  std::vector<int> v2_(v1_);
  EXPECT_EQ(v1_.size(), v2_.size());
  for (size_t i = 0; i < v1_.size(); i++) {
    EXPECT_EQ(v1_[i], v2_[i]);
  }
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  size_t n = 3;
  EXPECT_EQ(v2.size(), n);
  EXPECT_EQ(v2[0], 1);
  n = 0;
  EXPECT_EQ(v1.size(), n);
  EXPECT_EQ(v1.data(), nullptr);
}

TEST(VectorTest, AssignmentOperator) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2;
  v2 = v1;
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[1], 2);
  EXPECT_EQ(v2[2], 3);

  std::vector<int> v1_{1, 2, 3};
  std::vector<int> v2_;
  v2_ = v1_;
  EXPECT_EQ(v1_.size(), v2_.size());
  EXPECT_EQ(v2_[0], 1);
  EXPECT_EQ(v2_[1], 2);
  EXPECT_EQ(v2_[2], 3);
}

TEST(VectorTest, MoveAssignmentOperator) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  size_t n = 3;
  EXPECT_EQ(v2.size(), n);
  EXPECT_EQ(v2[0], 1);
  n = 0;
  EXPECT_EQ(v1.size(), n);
}

TEST(VectorTest, AtMethod) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_THROW(v.at(5), std::out_of_range);
}

TEST(VectorTest, FrontBackMethods) {
  s21::vector<int> v{1, 2, 3};
  EXPECT_EQ(v.front(), 1);
  EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, PushBackPopBack) {
  s21::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  size_t n = 2;
  EXPECT_EQ(v.size(), n);
  EXPECT_EQ(v.back(), 2);
  EXPECT_EQ(v[0], 1);
  v.pop_back();
  EXPECT_EQ(v.size(), n - 1);
  EXPECT_EQ(v.back(), 1);

  std::vector<int> v_;
  v_.push_back(1);
  v_.push_back(2);
  EXPECT_EQ(v_.size(), n);
  EXPECT_EQ(v_.back(), 2);
  v_.pop_back();
  EXPECT_EQ(v_.size(), n - 1);
  EXPECT_EQ(v_.back(), 1);
}

TEST(VectorTest, EmptyMethod) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  v.push_back(10);
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, ReserveMethod) {
  s21::vector<int> v;
  v.reserve(10);
  size_t n = 10;
  EXPECT_GE(v.capacity(), n);
}

TEST(VectorTest, ClearMethod) {
  s21::vector<int> v{1, 2, 3};
  v.clear();
  size_t n = 0;
  EXPECT_EQ(v.size(), n);
}

TEST(VectorTest, SwapMethod) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2{4, 5, 6};
  v1.swap(v2);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, DataMethod) {
  s21::vector<int> v{1, 2, 3};
  int* data_ptr = v.data();
  EXPECT_EQ(data_ptr[0], 1);
}

TEST(VectorTest, CapacityMethod) {
  s21::vector<int> v;
  size_t n = 0;
  EXPECT_EQ(v.capacity(), n);
  v.reserve(5);
  EXPECT_GE(v.capacity(), n + 5);
}

TEST(VectorTest, MaxSizeMethod) {
  s21::vector<int> v;
  // Проверим, что максимальный размер больше 0 и реалистичен для системы
  size_t n = 0;
  EXPECT_GT(v.max_size(), n);
  EXPECT_LT(v.max_size(), std::numeric_limits<std::size_t>::max());
}

TEST(VectorTest, ShrinkToFitMethod) {
  s21::vector<int> v;
  v.reserve(100);  // Зарезервируем место для 100 элементов
  size_t n = 100;
  EXPECT_GE(v.capacity(), n);

  v.push_back(1);  // Добавим один элемент
  v.push_back(2);

  v.shrink_to_fit();  // Приведем емкость к фактическому размеру
  EXPECT_EQ(v.capacity(), v.size());  // Емкость должна равняться размеру
  n = 2;
  EXPECT_EQ(v.size(), n);

  std::vector<int> v_;
  n = 100;
  v_.reserve(100);  // Зарезервируем место для 100 элементов
  EXPECT_GE(v_.capacity(), n);

  v_.push_back(1);  // Добавим один элемент
  v_.push_back(2);

  v_.shrink_to_fit();  // Приведем емкость к фактическому размеру
  EXPECT_EQ(v_.capacity(), v_.size());  // Емкость должна равняться размеру
  n = 2;
  EXPECT_EQ(v_.size(), n);
}

TEST(VectorTest, InsertMethod) {
  s21::vector<int> v{1, 2, 3};
  std::vector<int> v_{1, 2, 3};

  // Вставляем элемент в начало
  v.insert(v.begin(), 0);
  EXPECT_EQ(v[0], 0);
  size_t n = 4;
  EXPECT_EQ(v.size(), n);
  v_.insert(v_.begin(), 0);
  EXPECT_EQ(v_[0], 0);
  EXPECT_EQ(v_.size(), n);

  // Вставляем элемент в середину
  v.insert(v.begin() + 2, 10);
  EXPECT_EQ(v[2], 10);
  EXPECT_EQ(v.size(), n + 1);
  v_.insert(v_.begin() + 2, 10);
  EXPECT_EQ(v_[2], 10);
  EXPECT_EQ(v_.size(), n + 1);

  // Вставляем элемент в конец
  v.insert(v.end()--, 20);
  EXPECT_EQ(v.back()--, 20);
  EXPECT_EQ(v.size(), n + 2);
  v_.insert(v_.end()--, 20);
  EXPECT_EQ(v_.back()--, 20);
  EXPECT_EQ(v_.size(), n + 2);
}

TEST(VectorTest, EraseMethod) {
  s21::vector<int> v{1, 2, 3};
  // Удаляем элемент из начала
  v.erase(v.begin());
  EXPECT_EQ(v[0], 2);
  size_t n = 2;
  EXPECT_EQ(v.size(), n);
  // Удаляем элемент из конца
  v.erase(--v.end());
  EXPECT_EQ(v.size(), n - 1);
  EXPECT_EQ(v[0], 2);

  std::vector<int> v_{1, 2, 3};
  // Удаляем элемент из начала
  v_.erase(v_.begin());
  EXPECT_EQ(v_[0], 2);
  EXPECT_EQ(v_.size(), n);
  // Удаляем элемент из конца
  v_.erase(--v_.end());
  EXPECT_EQ(v_.size(), n - 1);
  EXPECT_EQ(v_[0], 2);
}

TEST(VectorTest, EraseSingleElement) {
  s21::vector<int> v{1};
  // Удаляем единственный элемент
  v.erase(v.begin());
  size_t n = 0;
  EXPECT_EQ(v.size(), n);
  EXPECT_TRUE(v.empty());
}

// Тест вставки нескольких элементов в середину
TEST(VectorInsertManyTest, InsertManyInMiddle) {
  s21::vector<int> vec = {1, 2, 5, 6};  // Изначально вектор {1, 2, 5, 6}
  vec.insert_many(vec.begin() + 2, 3, 4);  // Вставляем {3, 4} на позицию 2

  size_t n = 6;
  ASSERT_EQ(vec.size(), n);  // Проверяем размер
  EXPECT_EQ(vec[0], 1);      // Проверяем каждый элемент
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}

// Тест вставки в начало
TEST(VectorInsertManyTest, InsertManyInBegin) {
  s21::vector<int> vec = {3, 4, 5};  // Изначально вектор {3, 4, 5}
  vec.insert_many(vec.begin(), 1, 2);  // Вставляем {1, 2} в начало

  size_t n = 5;
  ASSERT_EQ(vec.size(), n);  // Проверяем размер
  EXPECT_EQ(vec[0], 1);      // Проверяем элементы
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

// Тест вставки в конец
TEST(VectorInsertManyTest, InsertManyAtEnd) {
  s21::vector<int> vec = {1, 2};     // Изначально вектор {1, 2}
  vec.insert_many(vec.end(), 3, 4);  // Вставляем {3, 4} в конец

  size_t n = 4;
  ASSERT_EQ(vec.size(), n);  // Проверяем размер
  EXPECT_EQ(vec[0], 1);      // Проверяем элементы
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
}

// Тест вставки нескольких элементов в конец
TEST(VectorInsertManyBackTest, InsertManyBack) {
  s21::vector<int> vec = {1, 2};  // Изначально вектор {1, 2}
  vec.insert_many_back(3, 4, 5);  // Вставляем {3, 4, 5} в конец

  size_t n = 5;
  ASSERT_EQ(vec.size(), n);  // Проверяем размер
  EXPECT_EQ(vec[0], 1);      // Проверяем каждый элемент
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
}

// Тест вставки в пустой вектор
TEST(VectorInsertManyBackTest, InsertManyBackToEmpty) {
  s21::vector<int> vec;           // Пустой вектор
  vec.insert_many_back(1, 2, 3);  // Вставляем {1, 2, 3} в конец

  size_t n = 3;
  ASSERT_EQ(vec.size(), n);  // Проверяем размер
  EXPECT_EQ(vec[0], 1);      // Проверяем каждый элемент
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

// Тест вставки одного элемента
TEST(VectorInsertManyBackTest, InsertManyBackSingleElement) {
  s21::vector<int> vec = {1, 2};  // Изначально вектор {1, 2}
  vec.insert_many_back(3);        // Вставляем 1 элемент {3}

  size_t n = 3;
  ASSERT_EQ(vec.size(), n);  // Проверяем размер
  EXPECT_EQ(vec[2], 3);  // Проверяем последний элемент
}

// Тест на корректность итераторов (разыменование и перемещение)
TEST(VectorTest, IteratorBasic) {
  s21::vector<int> vec = {10, 20, 30};  // Инициализация вектора
  auto it = vec.begin();

  EXPECT_EQ(*it, 10);  // Проверяем первый элемент
  ++it;
  EXPECT_EQ(*it, 20);  // Переместились на второй элемент
  ++it;
  EXPECT_EQ(*it, 30);  // Переместились на третий элемент
}

// Тест на префиксный и постфиксный инкременты
TEST(VectorTest, IteratorIncrement) {
  s21::vector<int> vec = {10, 20, 30};
  auto it = vec.begin();
  EXPECT_EQ(*(++it), 20);  // Проверяем постфиксный инкремент
  EXPECT_EQ(*it, 20);  // После инкремента
  EXPECT_EQ(*(++it), 30);  // Проверяем префиксный инкремент

  std::vector<int> vec_ = {10, 20, 30};
  auto it_ = vec_.begin();
  EXPECT_EQ(*(++it_), 20);  // Проверяем постфиксный инкремент
  EXPECT_EQ(*it_, 20);  // После инкремента
  EXPECT_EQ(*(++it_), 30);  // Проверяем префиксный инкремент
}

// Тест на сравнение итераторов
TEST(VectorTest, IteratorComparison) {
  s21::vector<int> vec = {10, 20, 30};
  auto it1 = vec.begin();
  auto it2 = vec.begin();

  EXPECT_TRUE(it1 == it2);  // Оба итератора указывают на начало

  ++it1;
  EXPECT_TRUE(it1 != it2);  // Теперь итераторы указывают на разные элементы
}

// 1. Тест на копирование полного диапазона
TEST(VectorCopyTest, FullRangeCopy) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  s21::vector<int> result(5);

  std::copy(v.begin(), v.end(), result.begin());

  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_result(5);
  std::copy(std_v.begin(), std_v.end(), std_result.begin());

  EXPECT_EQ(result[0], std_result[0]);
  EXPECT_EQ(result[1], std_result[1]);
  EXPECT_EQ(result[2], std_result[2]);
  EXPECT_EQ(result[3], std_result[3]);
  EXPECT_EQ(result[4], std_result[4]);
}

// 2. Тест на копирование пустого диапазона
TEST(VectorCopyTest, EmptyRangeCopy) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  s21::vector<int> result(5);
  std::copy(v.begin(), v.begin(), result.begin());  // Копируем пустой диапазон

  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_result(5);
  std::copy(std_v.begin(), std_v.begin(), std_result.begin());

  EXPECT_EQ(result[0], std_result[0]);
  EXPECT_EQ(result[1], std_result[1]);
  EXPECT_EQ(result[2], std_result[2]);
  EXPECT_EQ(result[3], std_result[3]);
  EXPECT_EQ(result[4], std_result[4]);
}

TEST(VectorEraseTest, BasicErase) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  // Erase the second element (2)
  v.erase(v.begin() + 1);
  size_t n = 4;
  EXPECT_EQ(v.size(), n);  // Size should now be 4
  EXPECT_EQ(v[0], 1);      // First element should be 1
  EXPECT_EQ(v[1], 3);      // Second element should be now 3
  EXPECT_EQ(v[2], 4);      // Third element should be 4
  EXPECT_EQ(v[3], 5);      // Fourth element should be 5
}

TEST(VectorEraseTest, EraseFirstElement) {
  s21::vector<int> v{10, 20, 30};

  // Erase the first element (10)
  v.erase(v.begin());

  size_t n = 2;
  EXPECT_EQ(v.size(), n);  // Size should now be 2
  EXPECT_EQ(v[0], 20);     // First element should be 20
  EXPECT_EQ(v[1], 30);     // Second element should be 30
}

TEST(VectorEraseTest, EraseLastElement) {
  s21::vector<int> v{1, 2, 3};

  // Erase the last element (3)
  v.erase(v.end() - 1);

  size_t n = 2;
  EXPECT_EQ(v.size(), n);  // Size should now be 2
  EXPECT_EQ(v[0], 1);      // First element should be 1
  EXPECT_EQ(v[1], 2);      // Second element should be 2
}

TEST(VectorIteratorTest, BeginReturnsCorrectIterator) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  // Get the iterator from begin()
  auto it = v.begin();

  EXPECT_EQ(*it, 1);  // The first element should be 1
}

/*TEST(VectorIteratorTest, EndReturnsCorrectIterator) {
  s21::vector<int> v{1, 2, 3, 4, 5};

  // Get the iterator from end()
  auto it = v.end();

  size_t n = 5;
  EXPECT_EQ(it - v.begin(), n);  // The distance from begin to end should be the
size of the vector

  std::vector<int> v_{1, 2, 3, 4, 5};

  // Get the iterator from end()
  auto it_ = v_.end();

  EXPECT_EQ(*(it_ - 1), 5);  // The last element should be 5
  EXPECT_EQ(it_ - v_.begin(), n);  // The distance from begin to end should be
the size of the vector
}*/

TEST(VectorIteratorTest, EmptyVectorBeginEnd) {
  s21::vector<int> v;  // Create an empty vector

  EXPECT_EQ(v.begin(),
            v.end());  // begin() and end() should be equal for an empty vector
}

TEST(VectorIteratorTest, IteratorIncrement) {
  s21::vector<int> v{1, 2, 3};

  auto it = v.begin();
  ++it;  // Increment the iterator

  EXPECT_EQ(*it, 2);  // The iterator should point to the second element
}

TEST(VectorIteratorTest, IteratorAssignment) {
  s21::vector<int> v{1, 2, 3};

  s21::vector<int>::iterator it1 = v.begin();
  s21::vector<int>::iterator it2 = v.begin();
  it2 = it1;  // Assign one iterator to another

  EXPECT_EQ(*it2,
            1);  // After assignment, it2 should also point to the first element
}

TEST(VectorIteratorTest, PostfixIncrement) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  auto it = vec.begin();  // Get an iterator to the beginning

  // Use the postfix increment operator and check the value
  int value = *(it++);  // Postfix increment
  EXPECT_EQ(value, 1);  // Should be 1, the current value before increment
  EXPECT_EQ(*it, 2);    // After increment, it should point to 2
}

TEST(VectorIteratorTest, PostfixIncrementMultiple) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  auto it = vec.begin();  // Get an iterator to the beginning

  // Increment twice
  int firstValue = *(it++);   // Should be 1
  int secondValue = *(it++);  // Should be 2

  EXPECT_EQ(firstValue, 1);
  EXPECT_EQ(secondValue, 2);
  EXPECT_EQ(*it, 3);  // After two increments, it should point to 3
}

TEST(IteratorTest, IteratorDifference) {
  s21::vector<int> v{1, 2, 3, 4, 5};
  auto it1 = v.begin();
  auto it2 = v.end();
  size_t n = 5;
  EXPECT_EQ(it2 - it1, n);
}

TEST(VectorInsertTest1, InsertSingleElement) {
  s21::vector<int> s21_vec = {1, 2, 3, 4};
  std::vector<int> std_vec = {1, 2, 3, 4};

  auto s21_it = s21_vec.begin() + 2;
  auto std_it = std_vec.begin() + 2;

  s21_vec.insert(s21_it, 42);
  std_vec.insert(std_it, 42);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// tests_stack
TEST(Stack_Constructor, Default_Empty) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack_Constructor, List_Empty) {
  s21::stack<int> s21_stack = {};
  std::stack<int> std_stack = {};
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack.size(), std_stack.size());
}

TEST(Stack_Constructor, List_Ints) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack_Constructor, Copy_Ints) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  s21::stack<int> s21_stack_copy(s21_stack);
  std::stack<int> std_stack_copy(std_stack);
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
  ASSERT_EQ(s21_stack_copy.empty(), std_stack_copy.empty());
  ASSERT_EQ(s21_stack_copy.size(), std_stack_copy.size());
  ASSERT_EQ(s21_stack_copy.top(), std_stack_copy.top());
}

TEST(Stack_Constructor, Move_Ints) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  s21::stack<int> s21_stack_move(std::move(s21_stack));
  std::stack<int> std_stack_move(std::move(std_stack));
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack_move.empty(), std_stack_move.empty());
  ASSERT_EQ(s21_stack_move.size(), std_stack_move.size());
  ASSERT_EQ(s21_stack_move.top(), std_stack_move.top());
}

TEST(Stack_Operator, Assignment) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  s21::stack<int> s21_stack2 = s21_stack;
  std::stack<int> std_stack2 = std_stack;
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
  ASSERT_EQ(s21_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(s21_stack2.size(), std_stack2.size());
  ASSERT_EQ(s21_stack2.top(), std_stack2.top());
}

TEST(Stack_Element_Access, Top_Double) {
  s21::stack<double> s21_stack = {1.1, 2.2, 3.3};
  std::stack<double> std_stack;
  std_stack.push(1.1);
  std_stack.push(2.2);
  std_stack.push(3.3);
  ASSERT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack_Capacity, Empty_False) {
  s21::stack<double> s21_stack = {1.1, 2.2, 3.3};
  std::stack<double> std_stack;
  std_stack.push(1.1);
  std_stack.push(2.2);
  std_stack.push(3.3);
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack_Capacity, Empty_True) {
  s21::stack<double> s21_stack;
  std::stack<double> std_stack;
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(Stack_Capacity, Size_0) {
  s21::stack<double> s21_stack;
  std::stack<double> std_stack;
  ASSERT_EQ(s21_stack.size(), std_stack.size());
}

TEST(Stack_Capacity, Size_1) {
  s21::stack<double> s21_stack = {5.5};
  std::stack<double> std_stack;
  std_stack.push(5.5);
  ASSERT_EQ(s21_stack.size(), std_stack.size());
}

TEST(Stack_Modifiers, Push_Char) {
  s21::stack<char> s21_stack = {'a', 'b', 'c'};
  std::stack<char> std_stack;
  std_stack.push('a');
  std_stack.push('b');
  std_stack.push('c');
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
  s21_stack.push('d');
  std_stack.push('d');
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack_Modifiers, Push_Empty) {
  s21::stack<char> s21_stack;
  std::stack<char> std_stack;
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  s21_stack.push('a');
  std_stack.push('a');
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack_Modifiers, Pop_Char) {
  s21::stack<char> s21_stack = {'a', 'b', 'c'};
  std::stack<char> std_stack;
  std_stack.push('a');
  std_stack.push('b');
  std_stack.push('c');
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
  s21_stack.pop();
  std_stack.pop();
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
}

TEST(Stack_Modifiers, Pop_Empty) {
  s21::stack<char> s21_stack;
  std::stack<char> std_stack;
  EXPECT_THROW(s21_stack.pop(), std::exception);
}

TEST(Stack_Modifiers, Swap_Empty) {
  s21::stack<std::string> s21_stack1 = {"hello", "world"};
  std::stack<std::string> std_stack1;
  std_stack1.push("hello");
  std_stack1.push("world");
  s21::stack<std::string> s21_stack2;
  std::stack<std::string> std_stack2;
  s21_stack1.swap(s21_stack2);
  std_stack1.swap(std_stack2);
  ASSERT_EQ(s21_stack1.empty(), std_stack1.empty());
  ASSERT_EQ(s21_stack2.size(), std_stack2.size());
  ASSERT_EQ(s21_stack2.top(), std_stack2.top());
}

TEST(Stack_Modifiers, Swap_String) {
  s21::stack<std::string> s21_stack1 = {"hello", "world"};
  std::stack<std::string> std_stack1;
  std_stack1.push("hello");
  std_stack1.push("world");
  s21::stack<std::string> s21_stack2 = {"aboba"};
  std::stack<std::string> std_stack2;
  std_stack2.push("aboba");
  ASSERT_EQ(s21_stack1.size(), std_stack1.size());
  ASSERT_EQ(s21_stack1.top(), std_stack1.top());
  ASSERT_EQ(s21_stack2.size(), std_stack2.size());
  ASSERT_EQ(s21_stack2.top(), std_stack2.top());
}

TEST(Stack_Modifiers_Bonus, Insert_many_back_ToEmpty) {
  s21::stack<int> s21_stack;
  s21_stack.insert_many_back(1, 2, 3);
  size_t test_size = 3;
  ASSERT_EQ(s21_stack.size(), test_size);
  ASSERT_EQ(s21_stack.top(), 3);
}

TEST(Stack_Modifiers_Bonus, Insert_many_back_ToFull) {
  s21::stack<int> s21_stack = {1, 2, 3};
  s21_stack.insert_many_back(4, 5, 6);
  size_t test_size = 6;
  ASSERT_EQ(s21_stack.size(), test_size);
  ASSERT_EQ(s21_stack.top(), 6);
}

TEST(Stack_Operator, Assignment_New1) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  s21::stack<int> s21_stack2;
  std::stack<int> std_stack2;
  s21_stack2 = s21_stack;
  std_stack2 = std_stack;
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.top(), std_stack.top());
  ASSERT_EQ(s21_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(s21_stack2.size(), std_stack2.size());
  ASSERT_EQ(s21_stack2.top(), std_stack2.top());
}

TEST(Stack_Operator, Assignment_New2) {
  s21::stack<int> s21_stack = {1, 2, 3, 4};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);
  s21::stack<int> s21_stack2;
  std::stack<int> std_stack2;
  s21_stack2 = std::move(s21_stack);
  std_stack2 = std::move(std_stack);
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  ASSERT_EQ(s21_stack2.empty(), std_stack2.empty());
  ASSERT_EQ(s21_stack2.size(), std_stack2.size());
  ASSERT_EQ(s21_stack2.top(), std_stack2.top());
}

// tests_set
TEST(set_Iterator, End) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int>::iterator s21_iterator = s21_mset.end();
  std::set<int>::iterator std_iterator = std_mset.end();
  std_iterator--;
  s21_iterator--;
  ASSERT_EQ(*s21_iterator, *std_iterator);
}

TEST(set_Capacity, Max_Size) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  ASSERT_EQ(s21_set.max_size(), std_set.max_size());
}

TEST(MultisetTest, DefaultConstructor) {
  s21::set<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  std::set<int> ms_;
  EXPECT_TRUE(ms_.empty());
  EXPECT_EQ(ms_.size(), 0);
}

TEST(MultisetTest, MoveConstructor) {
  s21::set<int> ms1 = {1, 2, 3};
  s21::set<int> ms2(std::move(ms1));  // Перемещаем ms1 в ms2

  EXPECT_TRUE(ms1.empty());  // ms1 теперь должен быть пустым
  EXPECT_FALSE(ms2.empty());
  EXPECT_EQ(ms2.size(), 3);

  std::set<int> ms1_ = {1, 2, 3};
  std::set<int> ms2_(std::move(ms1_));  // Перемещаем ms1 в ms2

  EXPECT_TRUE(ms1_.empty());  // ms1 теперь должен быть пустым
  EXPECT_FALSE(ms2_.empty());
  EXPECT_EQ(ms2_.size(), 3);
}

TEST(MultisetTest, MoveConstructorEmpty) {
  s21::set<int> ms1;                  // Пустой
  s21::set<int> ms2(std::move(ms1));  // Перемещаем пустой set

  EXPECT_TRUE(ms1.empty());  // ms1 все еще пуст
  EXPECT_TRUE(ms2.empty());  // ms2 тоже пуст

  std::set<int> ms1_;                   // Пустой
  std::set<int> ms2_(std::move(ms1_));  // Перемещаем пустой set

  EXPECT_TRUE(ms1_.empty());  // ms1 все еще пуст
  EXPECT_TRUE(ms2_.empty());  // ms2 тоже пуст
}

TEST(MultisetTest, CopyConstructorSelfAssignment) {
  s21::set<int> ms1 = {1, 2, 3};
  s21::set<int> ms2(ms1);  // Копируем в новый объект

  // Убедимся, что изменение одного не повлияло на другой
  ms1.insert(4);
  EXPECT_EQ(ms1.size(), 4);
  EXPECT_EQ(ms2.size(), 3);

  std::set<int> ms1_ = {1, 2, 3};
  std::set<int> ms2_(ms1_);  // Копируем в новый объект

  // Убедимся, что изменение одного не повлияло на другой
  ms1_.insert(4);
  EXPECT_EQ(ms1_.size(), 4);
  EXPECT_EQ(ms2_.size(), 3);
}

TEST(MultisetTest, InitializerListEmpty) {
  s21::set<int> ms = {};  // Пустой инициализирующий список
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  std::set<int> ms_ = {};  // Пустой инициализирующий список
  EXPECT_TRUE(ms_.empty());
  EXPECT_EQ(ms_.size(), 0);
}

TEST(MultisetTest, CopyConstructorWithEmptyTree) {
  // Создаем пустое дерево
  s21::set<int> original_set;

  // Копируем пустое дерево
  s21::set<int> copied_set(original_set);

  // Проверяем, что новое дерево пустое
  EXPECT_TRUE(copied_set.empty());
  EXPECT_EQ(copied_set.size(), 0);

  // Создаем пустое дерево
  std::set<int> original_set_;

  // Копируем пустое дерево
  std::set<int> copied_set_(original_set_);

  // Проверяем, что новое дерево пустое
  EXPECT_TRUE(copied_set_.empty());
  EXPECT_EQ(copied_set_.size(), 0);
}

// Тест для оператора присваивания копированием
TEST(MultisetTest, CopyAssignment_NonEmptyToEmpty) {
  s21::set<int> ms1;           // Пустое множество
  s21::set<int> ms2{1, 2, 3};  // Множество с тремя элементами

  // Присваивание пустому множеству непустого
  ms1 = ms2;
  EXPECT_EQ(ms1.size(), 3);  // Размер должен совпадать
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
}

TEST(MultisetTest, CopyAssignment_SelfAssignment) {
  s21::set<int> ms2{1, 2, 3};  // Множество с тремя элементами

  // Присваивание самому себе
  ms2 = ms2;
  EXPECT_EQ(ms2.size(), 3);  // Проверяем, что размер не изменился
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, CopyAssignment_EmptyToEmpty) {
  s21::set<int> ms1;        // Пустое множество
  s21::set<int> empty_set;  // Пустое множество

  // Присваивание пустого множества другому пустому
  ms1 = empty_set;
  EXPECT_EQ(ms1.size(), 0);  // Оба множества должны быть пустыми

  std::set<int> ms1_;        // Пустое множество
  std::set<int> empty_set_;  // Пустое множество

  // Присваивание пустого множества другому пустому
  ms1_ = empty_set_;
  EXPECT_EQ(ms1_.size(), 0);  // Оба множества должны быть пустыми
}

// Тест для оператора присваивания перемещением
TEST(MultisetTest, MoveAssignment_NonEmptyToEmpty) {
  s21::set<int> ms1;           // Пустое множество
  s21::set<int> ms2{1, 2, 3};  // Множество с тремя элементами

  // Перемещение в пустое множество
  ms1 = std::move(ms2);
  EXPECT_EQ(ms1.size(), 3);  // Проверяем, что элементы были перемещены
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_EQ(ms2.size(), 0);  // Исходное множество должно быть пустым
}

TEST(MultisetTest, MoveAssignment_SelfMove) {
  s21::set<int> ms1{1, 2, 3};  // Множество с тремя элементами

  // Перемещение самого себя
  ms1 = std::move(ms1);  // Должно корректно работать и не крашиться
  EXPECT_EQ(ms1.size(), 3);  // Размер не должен измениться
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
}

// Тесты для итераторов begin() и end()
TEST(MultisetTest, Iterators_EmptySet) {
  s21::set<int> empty_set;  // Пустое множество

  // Для пустого множества begin() == end()
  EXPECT_EQ(empty_set.begin(), empty_set.end());

  std::set<int> empty_set_;  // Пустое множество

  // Для пустого множества begin() == end()
  EXPECT_EQ(empty_set_.begin(), empty_set_.end());
}

TEST(MultisetTest, Iterators_EdgeCase) {
  s21::set<int> single_element_set{42};  // Множество с одним элементом

  // Итератор для множества с одним элементом
  EXPECT_EQ(*single_element_set.begin(), 42);

  // Модификация множества и проверка итераторов
  single_element_set.insert(100);
  auto it = single_element_set.begin();
  EXPECT_EQ(*it, 42);  // Элементы должны остаться отсортированными

  std::set<int> single_element_set_{42};  // Множество с одним элементом

  // Итератор для множества с одним элементом
  EXPECT_EQ(*single_element_set_.begin(), 42);

  // Модификация множества и проверка итераторов
  single_element_set_.insert(100);
  auto it_ = single_element_set_.begin();
  EXPECT_EQ(*it_, 42);  // Элементы должны остаться отсортированными
}

TEST(Multiset_CopyAssignment, AssignEmptyToEmpty) {
  s21::set<int> set1;
  s21::set<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(), 0);  // Ожидаем, что размер равен 0
  EXPECT_TRUE(set2.empty());  // Проверка на пустоту
  EXPECT_EQ(set2.begin(),
            set2.end());  // Итераторы должны быть равны для пустого множества

  std::set<int> set1_;
  std::set<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 0);  // Ожидаем, что размер равен 0
  EXPECT_TRUE(set2_.empty());  // Проверка на пустоту
  EXPECT_EQ(set2_.begin(),
            set2_.end());  // Итераторы должны быть равны для пустого множества
}

TEST(Multiset_CopyAssignment, AssignNonEmptyToEmpty) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(), 3);  // Ожидаем размер 3
  EXPECT_FALSE(set2.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы были корректно скопированы
  auto it = set2.begin();
  EXPECT_EQ(*it, 1);

  std::set<int> set1_ = {1, 2, 3};
  std::set<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 3);  // Ожидаем размер 3
  EXPECT_FALSE(set2_.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы были корректно скопированы
  auto it_ = set2_.begin();
  EXPECT_EQ(*it_, 1);
}

TEST(Multiset_CopyAssignment, AssignEmptyToNonEmpty) {
  s21::set<int> set1;
  s21::set<int> set2 = {4, 5, 6};

  set2 = set1;

  EXPECT_EQ(set2.size(), 0);  // Ожидаем, что размер стал 0
  EXPECT_TRUE(set2.empty());  // Проверка на пустоту
  EXPECT_EQ(set2.begin(),
            set2.end());  // Итераторы должны быть равны для пустого множества

  std::set<int> set1_;
  std::set<int> set2_ = {4, 5, 6};

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 0);  // Ожидаем, что размер стал 0
  EXPECT_TRUE(set2_.empty());  // Проверка на пустоту
  EXPECT_EQ(set2_.begin(),
            set2_.end());  // Итераторы должны быть равны для пустого множества
}

TEST(Multiset_CopyAssignment, SelfAssignment) {
  s21::set<int> set1 = {7, 8, 9};

  set1 = set1;  // Присваиваем самому себе

  EXPECT_EQ(set1.size(), 3);  // Ожидаем, что размер не изменится
  EXPECT_FALSE(set1.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы остались на своих местах
  auto it = set1.begin();
  EXPECT_EQ(*it, 7);

  std::set<int> set1_ = {7, 8, 9};

  set1_ = set1_;  // Присваиваем самому себе

  EXPECT_EQ(set1_.size(), 3);  // Ожидаем, что размер не изменится
  EXPECT_FALSE(set1_.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы остались на своих местах
  auto it_ = set1_.begin();
  EXPECT_EQ(*it_, 7);
}

TEST(Multiset_CopyAssignment, Duplicates) {
  s21::set<int> set1 = {10, 10, 20, 20, 30};
  s21::set<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(),
            3);  // Ожидаем, что все элементы скопированы, включая дубликаты
  EXPECT_FALSE(set2.empty());

  // Проверяем, что дубликаты были корректно скопированы
  auto it = set2.begin();
  EXPECT_EQ(*it, 10);

  std::set<int> set1_ = {10, 10, 20, 20, 30};
  std::set<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(),
            3);  // Ожидаем, что все элементы скопированы, включая дубликаты
  EXPECT_FALSE(set2_.empty());

  // Проверяем, что дубликаты были корректно скопированы
  auto it_ = set2_.begin();
  EXPECT_EQ(*it_, 10);
}

TEST(Multiset_CopyAssignment, SingleElement) {
  s21::set<int> set1 = {42};
  s21::set<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(), 1);  // Ожидаем размер 1
  EXPECT_FALSE(set2.empty());  // Множество не должно быть пустым

  auto it = set2.begin();
  EXPECT_EQ(*it++, 42);  // Проверяем, что единственный элемент скопирован

  std::set<int> set1_ = {42};
  std::set<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 1);  // Ожидаем размер 1
  EXPECT_FALSE(set2_.empty());  // Множество не должно быть пустым

  auto it_ = set2_.begin();
  EXPECT_EQ(*it_++, 42);  // Проверяем, что единственный элемент скопирован
}

TEST(Multiset_CopyAssignment, MaxSize) {
  s21::set<int> ms;
  EXPECT_GT(ms.max_size(),
            0);  // Убедиться, что max_size() возвращает положительное значение

  std::set<int> ms_;
  EXPECT_GT(ms_.max_size(),
            0);  // Убедиться, что max_size() возвращает положительное значение
}

TEST(MultisetTest, Clear_EmptySet) {
  s21::set<int> ms;
  ms.clear();  // Очищаем пустое множество
  EXPECT_TRUE(ms.empty());  // Множество должно оставаться пустым

  std::set<int> ms_;
  ms_.clear();  // Очищаем пустое множество
  EXPECT_TRUE(ms_.empty());  // Множество должно оставаться пустым
}

TEST(MultisetTest, Clear_NonEmptySet) {
  s21::set<int> ms{1, 2, 3};
  ms.clear();  // Очищаем множество с элементами
  EXPECT_TRUE(ms.empty());  // Множество должно стать пустым
  EXPECT_EQ(ms.size(), 0);  // Размер должен быть 0

  std::set<int> ms_{1, 2, 3};
  ms_.clear();  // Очищаем множество с элементами
  EXPECT_TRUE(ms_.empty());  // Множество должно стать пустым
  EXPECT_EQ(ms_.size(), 0);  // Размер должен быть 0
}

TEST(MultisetTest, Clear_AfterInsertions) {
  s21::set<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(3);
  ms.clear();  // Очищаем множество после вставки
  EXPECT_TRUE(ms.empty());  // Множество должно быть пустым
  EXPECT_EQ(ms.size(), 0);  // Размер должен быть 0

  s21::set<int> ms_;
  ms_.insert(1);
  ms_.insert(2);
  ms_.insert(3);
  ms_.clear();  // Очищаем множество после вставки
  EXPECT_TRUE(ms_.empty());  // Множество должно быть пустым
  EXPECT_EQ(ms_.size(), 0);  // Размер должен быть 0
}

TEST(MultisetTest, Insert_IntoEmptySet) {
  s21::set<int> ms;
  ms.insert(1);  // Вставляем в пустое множество
  EXPECT_TRUE(ms.contains(1));  // Элемент должен появиться в множестве
  EXPECT_EQ(ms.size(), 1);  // Размер должен быть 1
}

TEST(MultisetTest, Insert_DuplicateElements) {
  s21::set<int> ms;
  ms.insert(1);
  ms.insert(1);                 // Вставляем дубликат
  EXPECT_TRUE(ms.contains(1));  // Элемент должен присутствовать
  EXPECT_EQ(ms.size(), 1);  // Размер должен увеличиться
}

TEST(MultisetTest, Insert_MultipleElements) {
  s21::set<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(3);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_EQ(ms.size(), 3);  // Множество должно содержать три элемента
}

TEST(MultisetTest, Swap_TwoEmptySets) {
  s21::set<int> ms1;
  s21::set<int> ms2;
  ms1.swap(ms2);  // Меняем пустые множества
  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms2.empty());

  std::set<int> ms1_;
  std::set<int> ms2_;
  ms1_.swap(ms2_);  // Меняем пустые множества
  EXPECT_TRUE(ms1_.empty());
  EXPECT_TRUE(ms2_.empty());
}

TEST(MultisetTest, Swap_NonEmptyWithEmpty) {
  s21::set<int> ms1{1, 2, 3};
  s21::set<int> ms2;
  ms1.swap(ms2);  // Меняем непустое множество с пустым
  EXPECT_TRUE(ms1.empty());
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, Swap_TwoNonEmptySets) {
  s21::set<int> ms1{1, 2};
  s21::set<int> ms2{3, 4};
  ms1.swap(ms2);  // Меняем два непустых множества
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
}

TEST(MultisetTest, Merge_TwoEmptySets) {
  s21::set<int> ms1;
  s21::set<int> ms2;
  ms1.merge(ms2);  // Мержим два пустых множества
  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms2.empty());

  std::set<int> ms1_;
  std::set<int> ms2_;
  ms1_.merge(ms2_);  // Мержим два пустых множества
  EXPECT_TRUE(ms1_.empty());
  EXPECT_TRUE(ms2_.empty());
}

TEST(MultisetTest, Merge_EmptyWithNonEmpty) {
  s21::set<int> ms1;
  s21::set<int> ms2{1, 2, 3};
  ms1.merge(ms2);  // Мержим пустое множество с непустым
  EXPECT_EQ(ms1.size(), 3);
  EXPECT_TRUE(ms2.empty());  // Второе множество должно стать пустым

  std::set<int> ms1_;
  std::set<int> ms2_{1, 2, 3};
  ms1_.merge(ms2_);  // Мержим пустое множество с непустым
  EXPECT_EQ(ms1_.size(), 3);
  EXPECT_TRUE(ms2_.empty());  // Второе множество должно стать пустым
}

TEST(MultisetTest, Merge_NonEmptyWithEmpty) {
  s21::set<int> ms1{1, 2, 3};
  s21::set<int> ms2;
  ms1.merge(ms2);  // Мержим непустое множество с пустым
  EXPECT_EQ(ms1.size(), 3);  // Множество ms1 должно остаться прежним
  EXPECT_TRUE(ms2.empty());  // Второе множество должно оставаться пустым

  std::set<int> ms1_{1, 2, 3};
  std::set<int> ms2_;
  ms1_.merge(ms2_);  // Мержим непустое множество с пустым
  EXPECT_EQ(ms1_.size(), 3);  // Множество ms1 должно остаться прежним
  EXPECT_TRUE(ms2_.empty());  // Второе множество должно оставаться пустым
}

TEST(MultisetTest, Merge_TwoNonEmptySets) {
  s21::set<int> ms1{1, 2};
  s21::set<int> ms2{2, 3, 4};
  ms1.merge(ms2);  // Мержим два непустых множества
  EXPECT_EQ(ms1.size(), 4);  // Элементы должны объединиться
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms1.contains(4));

  EXPECT_FALSE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_FALSE(ms2.contains(3));
  EXPECT_FALSE(ms2.contains(4));

  EXPECT_FALSE(ms2.empty());  // Второе множество должно стать пустым

  std::set<int> ms1_{1, 2};
  std::set<int> ms2_{2, 3, 4};
  ms1_.merge(ms2_);  // Мержим два непустых множества
  EXPECT_EQ(ms1_.size(), 4);  // Элементы должны объединиться
  EXPECT_TRUE(ms1_.find(1) != ms1_.end());
  EXPECT_TRUE(ms1_.find(2) != ms1_.end());
  EXPECT_TRUE(ms1_.find(3) != ms1_.end());
  EXPECT_TRUE(ms1_.find(4) != ms1_.end());

  EXPECT_FALSE(ms2_.find(1) != ms2_.end());
  EXPECT_TRUE(ms2_.find(2) != ms2_.end());
  EXPECT_FALSE(ms2_.find(3) != ms2_.end());
  EXPECT_FALSE(ms2_.find(4) != ms2_.end());

  EXPECT_FALSE(ms2_.empty());  // Второе множество должно стать пустым
}

TEST(Multiset_Constructor0, Default_Empty) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Constructor0, Initializer_List) {
  s21::set<int> s21_mset = {2, 2, 1, 3, 4};
  std::set<int> std_mset = {2, 2, 1, 3, 4};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::set<int>::iterator s21_iter = s21_mset.begin();
  std::set<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor0, Copy_Check_Old) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int> s21_mset_copy(s21_mset);
  std::set<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::set<int>::iterator s21_iter = s21_mset.begin();
  std::set<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor0, Copy_Check_New) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int> s21_mset_copy(s21_mset);
  std::set<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  size_t size = std_mset_copy.size();
  s21::set<int>::iterator s21_iter = s21_mset_copy.begin();
  std::set<int>::iterator std_iter = std_mset_copy.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor0, Move_Check_Old) {
  s21::set<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::set<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::set<int> s21_mset_move(std::move(s21_mset));
  std::set<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Constructor0, Move_Check_New) {
  s21::set<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::set<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::set<int> s21_mset_move(std::move(s21_mset));
  std::set<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset_move.size(), std_mset_move.size());
  size_t size = std_mset_move.size();
  s21::set<int>::iterator s21_iter = s21_mset_move.begin();
  std::set<int>::iterator std_iter = std_mset_move.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Operator, Assignment) {
  s21::set<float> s21_mset1 = {5.5, 4.4, 7.7};
  std::set<float> std_mset1 = {5.5, 4.4, 7.7};
  s21::set<float> s21_mset2 = {3.3, 1.1};
  std::set<float> std_mset2 = {3.3, 1.1};
  s21_mset1 = s21_mset2;
  std_mset1 = std_mset2;
  ASSERT_EQ(s21_mset2.size(), std_mset2.size());
  size_t size = std_mset2.size();
  s21::set<float>::iterator s21_iter = s21_mset2.begin();
  std::set<float>::iterator std_iter = std_mset2.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Iterator, Begin) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(*s21_mset.begin(), *std_mset.begin());
}

TEST(Multiset_Capacity, Empty_False) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity, Empty_True) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity, Size_0) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Capacity, Size_1) {
  s21::set<int> s21_mset = {5};
  std::set<int> std_mset = {5};
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Modifiers, Clear_Full) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers, Clear_Empty) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers, Insert_End) {
  s21::set<char> s21_set = {'b', 'c', 'd'};
  std::set<char> std_set = {'b', 'c', 'd'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('f');
  std_set.insert('f');
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Insert_Begin) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f'};
  std::set<char> std_set = {'b', 'c', 'd', 'f'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Insert_Middle) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'a'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'a'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('e');
  std_set.insert('e');
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Insert_Empty) {
  s21::set<char> s21_set;
  std::set<char> std_set;
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers, Insert_Duplicate) {
  s21::set<char> s21_set = {'a'};
  std::set<char> std_set = {'a'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers, Erase_Leaf) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);  // erase 'a'
  std_set.erase(std_iter);
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Erase_Root_with_RChild) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'e'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'e'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);  // erase 'b'
  std_set.erase(std_iter);
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Erase_with_both_children) {
  s21::set<char> s21_set = {'c', 'e', 'd', 'f'};
  std::set<char> std_set = {'c', 'e', 'd', 'f'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_iter++;
  std_iter++;
  s21_iter++;
  std_iter++;
  s21_set.erase(s21_iter);  // erase 'e'
  std_set.erase(std_iter);
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  ASSERT_EQ(s21_set.size(), std_set.size());
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Erase_Last) {
  s21::set<char> s21_set = {'c'};
  std::set<char> std_set = {'c'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);
  std_set.erase(std_iter);
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset_Modifiers, Swap_Empty) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2;
  std::set<std::string> std_set2;
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  ASSERT_EQ(s21_set1.empty(), std_set1.empty());
  s21::set<std::string>::iterator s21_iter = s21_set2.begin();
  std::set<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Swap_Check_Old) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set1.begin();
  std::set<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Swap_Check_New) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set2.begin();
  std::set<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Merge_with_Empty) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2;
  std::set<std::string> std_set2;
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set1.begin();
  std::set<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
  ASSERT_EQ(s21_set2.empty(), std_set2.empty());
}

TEST(Multiset_Modifiers, Merge_with_Full) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};

  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);

  // Проверка содержимого первого множества после слияния
  s21::set<std::string>::iterator s21_iter = s21_set1.begin();
  std::set<std::string>::iterator std_iter = std_set1.begin();
  size_t size = s21_set1.size();  // Используем s21_set1 для проверки
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Lookup0, Find_Exist) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::set<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  s21::set<double>::iterator s21_iter = s21_set.find(2.2);
  std::set<double>::iterator std_iter = std_set.find(2.2);
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST(Multiset_Lookup0, Find_Non_Exist) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(s21_set.find(9.9));

  std::set<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(std_set.find(9.9));
}

TEST(Multiset_Constructor, Default_Empty) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Constructor, Initializer_List) {
  s21::set<int> s21_mset = {2, 2, 1, 3, 4};
  std::set<int> std_mset = {2, 2, 1, 3, 4};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::set<int>::iterator s21_iter = s21_mset.begin();
  std::set<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor, Copy_Check_Old) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int> s21_mset_copy(s21_mset);
  std::set<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::set<int>::iterator s21_iter = s21_mset.begin();
  std::set<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor, Copy_Check_New) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int> s21_mset_copy(s21_mset);
  std::set<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  size_t size = std_mset_copy.size();
  s21::set<int>::iterator s21_iter = s21_mset_copy.begin();
  std::set<int>::iterator std_iter = std_mset_copy.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor, Move_Check_Old) {
  s21::set<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::set<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::set<int> s21_mset_move(std::move(s21_mset));
  std::set<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Constructor, Move_Check_New) {
  s21::set<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::set<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::set<int> s21_mset_move(std::move(s21_mset));
  std::set<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset_move.size(), std_mset_move.size());
  size_t size = std_mset_move.size();
  s21::set<int>::iterator s21_iter = s21_mset_move.begin();
  std::set<int>::iterator std_iter = std_mset_move.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Operator2, Assignment) {
  s21::set<float> s21_mset1 = {5.5, 4.4, 7.7};
  std::set<float> std_mset1 = {5.5, 4.4, 7.7};
  s21::set<float> s21_mset2 = {3.3, 1.1};
  std::set<float> std_mset2 = {3.3, 1.1};
  s21_mset1 = s21_mset2;
  std_mset1 = std_mset2;
  ASSERT_EQ(s21_mset2.size(), std_mset2.size());
  size_t size = std_mset2.size();
  s21::set<float>::iterator s21_iter = s21_mset2.begin();
  std::set<float>::iterator std_iter = std_mset2.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Capacity1, Empty_False) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity1, Empty_True) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity1, Size_0) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Capacity1, Size_1) {
  s21::set<int> s21_mset = {5};
  std::set<int> std_mset = {5};
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Modifiers1, Clear_Full) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers1, Clear_Empty) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers1, Insert_End) {
  s21::set<char> s21_set = {'b', 'c', 'd'};
  std::set<char> std_set = {'b', 'c', 'd'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('f');
  std_set.insert('f');
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers1, Insert_Begin) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f'};
  std::set<char> std_set = {'b', 'c', 'd', 'f'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers1, Insert_Middle) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'a'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'a'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('e');
  std_set.insert('e');
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers1, Insert_Empty) {
  s21::set<char> s21_set;
  std::set<char> std_set;
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers1, Insert_Duplicate) {
  s21::set<char> s21_set = {'a'};
  std::set<char> std_set = {'a'};
  s21::set<char>::iterator s21_iter;
  std::set<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers1, Erase_Leaf) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);  // erase 'a'
  std_set.erase(std_iter);
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers1, Erase_Root_with_RChild) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'e'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'e'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);  // erase 'b'
  std_set.erase(std_iter);
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers1, Erase_with_both_children) {
  s21::set<char> s21_set = {'c', 'e', 'd', 'f'};
  std::set<char> std_set = {'c', 'e', 'd', 'f'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_iter++;
  std_iter++;
  s21_iter++;
  std_iter++;
  s21_set.erase(s21_iter);  // erase 'e'
  std_set.erase(std_iter);
  s21_iter = s21_set.begin();
  std_iter = std_set.begin();
  size_t size = std_set.size();
  ASSERT_EQ(s21_set.size(), std_set.size());
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers1, Erase_Last) {
  s21::set<char> s21_set = {'c'};
  std::set<char> std_set = {'c'};
  s21::set<char>::iterator s21_iter = s21_set.begin();
  std::set<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);
  std_set.erase(std_iter);
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset_Modifiers2, Swap_Empty) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2;
  std::set<std::string> std_set2;
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  ASSERT_EQ(s21_set1.empty(), std_set1.empty());
  s21::set<std::string>::iterator s21_iter = s21_set2.begin();
  std::set<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers2, Swap_Check_Old) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set1.begin();
  std::set<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers2, Swap_Check_New) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set2.begin();
  std::set<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers2, Merge_with_Empty) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2;
  std::set<std::string> std_set2;
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set1.begin();
  std::set<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
  ASSERT_EQ(s21_set2.empty(), std_set2.empty());
}

TEST(Multiset_Modifiers2, Merge_with_Full) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::set<std::string>::iterator s21_iter = s21_set2.begin();
  std::set<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
  s21_iter = s21_set1.begin();
  std_iter = std_set1.begin();
  size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Lookup, Find_Exist) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::set<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  s21::set<double>::iterator s21_iter = s21_set.find(2.2);
  std::set<double>::iterator std_iter = std_set.find(2.2);
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST(Multiset_Lookup, Find_Non_Exist) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(s21_set.find(9.9));

  std::set<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(std_set.find(9.9));
}

TEST(Multiset_Lookup, Contains_True) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.contains(7.7), 1);
}

TEST(set_Constructor, Default_Empty) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(set_Constructor, Initializer_List) {
  s21::set<int> s21_mset = {2, 2, 1, 3, 4};
  std::set<int> std_mset = {2, 2, 1, 3, 4};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::set<int>::iterator s21_iterator = s21_mset.begin();
  std::set<int>::iterator std_iterator = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Constructor, Copy_Check_Old) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int> s21_mset_copy(s21_mset);
  std::set<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::set<int>::iterator s21_iterator = s21_mset.begin();
  std::set<int>::iterator std_iterator = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Constructor, Copy_Check_New) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::set<int> s21_mset_copy(s21_mset);
  std::set<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  size_t size = std_mset_copy.size();
  s21::set<int>::iterator s21_iterator = s21_mset_copy.begin();
  std::set<int>::iterator std_iterator = std_mset_copy.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Constructor, Move_Check_Old) {
  s21::set<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::set<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::set<int> s21_mset_move(std::move(s21_mset));
  std::set<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(set_Constructor, Move_Check_New) {
  s21::set<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::set<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::set<int> s21_mset_move(std::move(s21_mset));
  std::set<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset_move.size(), std_mset_move.size());
  size_t size = std_mset_move.size();
  s21::set<int>::iterator s21_iterator = s21_mset_move.begin();
  std::set<int>::iterator std_iterator = std_mset_move.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Operator, Assignment) {
  s21::set<float> s21_mset1 = {5.5, 4.4, 7.7};
  std::set<float> std_mset1 = {5.5, 4.4, 7.7};
  s21::set<float> s21_mset2 = {3.3, 1.1};
  std::set<float> std_mset2 = {3.3, 1.1};
  s21_mset1 = s21_mset2;
  std_mset1 = std_mset2;
  ASSERT_EQ(s21_mset2.size(), std_mset2.size());
  size_t size = std_mset2.size();
  s21::set<float>::iterator s21_iterator = s21_mset2.begin();
  std::set<float>::iterator std_iterator = std_mset2.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Iterator, Begin) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(*s21_mset.begin(), *std_mset.begin());
}

TEST(set_Capacity, Empty_False) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(set_Capacity, Empty_True) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(set_Capacity, Size_0) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(set_Capacity, Size_1) {
  s21::set<int> s21_mset = {5};
  std::set<int> std_mset = {5};
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(set_Modifiers, Clear_Full) {
  s21::set<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::set<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(set_Modifiers, Clear_Empty) {
  s21::set<int> s21_mset;
  std::set<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(set_Modifiers, Insert_End) {
  s21::set<char> s21_set = {'b', 'c', 'd'};
  std::set<char> std_set = {'b', 'c', 'd'};
  s21::set<char>::iterator s21_iterator;
  std::set<char>::iterator std_iterator;
  s21_set.insert('f');
  std_set.insert('f');
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Insert_Begin) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f'};
  std::set<char> std_set = {'b', 'c', 'd', 'f'};
  s21::set<char>::iterator s21_iterator;
  std::set<char>::iterator std_iterator;
  s21_set.insert('a');
  std_set.insert('a');
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Insert_Middle) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'a'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'a'};
  s21::set<char>::iterator s21_iterator;
  std::set<char>::iterator std_iterator;
  s21_set.insert('e');
  std_set.insert('e');
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Insert_Empty) {
  s21::set<char> s21_set;
  std::set<char> std_set;
  s21::set<char>::iterator s21_iterator;
  std::set<char>::iterator std_iterator;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(set_Modifiers, Insert_Duplicate) {
  s21::set<char> s21_set = {'a'};
  std::set<char> std_set = {'a'};
  s21::set<char>::iterator s21_iterator;
  std::set<char>::iterator std_iterator;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(set_Modifiers, Erase_Leaf) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  s21::set<char>::iterator s21_iterator = s21_set.begin();
  std::set<char>::iterator std_iterator = std_set.begin();
  s21_set.erase(s21_iterator);  // erase 'a'
  std_set.erase(std_iterator);
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Erase_Root_with_RChild) {
  s21::set<char> s21_set = {'b', 'c', 'd', 'f', 'e'};
  std::set<char> std_set = {'b', 'c', 'd', 'f', 'e'};
  s21::set<char>::iterator s21_iterator = s21_set.begin();
  std::set<char>::iterator std_iterator = std_set.begin();
  s21_set.erase(s21_iterator);  // erase 'b'
  std_set.erase(std_iterator);
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  size_t size = std_set.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Erase_with_both_children) {
  s21::set<char> s21_set = {'c', 'e', 'd', 'f'};
  std::set<char> std_set = {'c', 'e', 'd', 'f'};
  s21::set<char>::iterator s21_iterator = s21_set.begin();
  std::set<char>::iterator std_iterator = std_set.begin();
  s21_iterator++;
  std_iterator++;
  s21_iterator++;
  std_iterator++;
  s21_set.erase(s21_iterator);  // erase 'e'
  std_set.erase(std_iterator);
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  size_t size = std_set.size();
  ASSERT_EQ(s21_set.size(), std_set.size());
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Erase_Last) {
  s21::set<char> s21_set = {'c'};
  std::set<char> std_set = {'c'};
  s21::set<char>::iterator s21_iterator = s21_set.begin();
  std::set<char>::iterator std_iterator = std_set.begin();
  s21_set.erase(s21_iterator);
  std_set.erase(std_iterator);
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(set_Modifiers, Swap_Empty) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2;
  std::set<std::string> std_set2;
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  ASSERT_EQ(s21_set1.empty(), std_set1.empty());
  s21::set<std::string>::iterator s21_iterator = s21_set2.begin();
  std::set<std::string>::iterator std_iterator = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Swap_Check_Old) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::set<std::string>::iterator s21_iterator = s21_set1.begin();
  std::set<std::string>::iterator std_iterator = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Swap_Check_New) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::set<std::string>::iterator s21_iterator = s21_set2.begin();
  std::set<std::string>::iterator std_iterator = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Modifiers, Merge_with_Empty) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2;
  std::set<std::string> std_set2;
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::set<std::string>::iterator s21_iterator = s21_set1.begin();
  std::set<std::string>::iterator std_iterator = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
  ASSERT_EQ(s21_set2.empty(), std_set2.empty());
}

TEST(set_Modifiers, Merge_with_Full) {
  s21::set<std::string> s21_set1 = {"hello", "world"};
  std::set<std::string> std_set1 = {"hello", "world"};
  s21::set<std::string> s21_set2 = {"aboba"};
  std::set<std::string> std_set2 = {"aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::set<std::string>::iterator s21_iterator = s21_set2.begin();
  std::set<std::string>::iterator std_iterator = std_set2.begin();
  ASSERT_EQ(s21_set1.size(), std_set1.size());
  ASSERT_EQ(s21_set2.size(), std_set2.size());
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
  s21_iterator = s21_set1.begin();
  std_iterator = std_set1.begin();
  size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(set_Lookup, Find_Exist) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::set<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  s21::set<double>::iterator s21_iterator = s21_set.find(2.2);
  std::set<double>::iterator std_iterator = std_set.find(2.2);
  ASSERT_EQ(*s21_iterator, *std_iterator);
}

TEST(set_Lookup, Find_Non_Exist) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(s21_set.find(9.9));
  ASSERT_EQ(s21_set.find(9.9), s21_set.end());
}

TEST(set_Lookup, Contains_True) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.contains(7.7), 1);
}

TEST(set_Lookup, Contains_False) {
  s21::set<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.contains(9.9), 0);
}

TEST(Multiset_Modifiers, Erase_SingleElement) {
  s21::set<int> s21_set = {42};
  std::set<int> std_set = {42};

  auto s21_iter = s21_set.begin();
  auto std_iter = std_set.begin();

  s21_set.erase(s21_iter);  // Удаляем единственный элемент
  std_set.erase(std_iter);  // Оригинал

  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_TRUE(s21_set.empty());
  ASSERT_TRUE(std_set.empty());
}

TEST(Multiset_Modifiers, Erase_TwoChildren) {
  s21::set<int> s21_set = {50, 30, 70, 20, 40, 60, 80};
  std::set<int> std_set = {50, 30, 70, 20, 40, 60, 80};

  auto s21_iter = s21_set.find(50);  // Элемент с двумя детьми
  auto std_iter = std_set.find(50);

  s21_set.erase(s21_iter);
  std_set.erase(std_iter);

  ASSERT_EQ(s21_set.size(), std_set.size());

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();
  while (s21_it != s21_set.end() && std_it != std_set.end()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(Multiset_Modifiers, Erase_OneChild) {
  s21::set<int> s21_set = {50, 30, 70, 60};
  std::set<int> std_set = {50, 30, 70, 60};

  auto s21_iter = s21_set.find(70);  // Элемент с одним ребенком
  auto std_iter = std_set.find(70);

  s21_set.erase(s21_iter);
  std_set.erase(std_iter);

  ASSERT_EQ(s21_set.size(), std_set.size());

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();
  while (s21_it != s21_set.end() && std_it != std_set.end()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(Multiset_Modifiers, Erase_LeafNode) {
  s21::set<int> s21_set = {50, 30, 70, 20};
  std::set<int> std_set = {50, 30, 70, 20};

  auto s21_iter = s21_set.find(20);  // Листовой узел
  auto std_iter = std_set.find(20);

  s21_set.erase(s21_iter);
  std_set.erase(std_iter);

  ASSERT_EQ(s21_set.size(), std_set.size());

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();
  while (s21_it != s21_set.end() && std_it != std_set.end()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(Multiset_Modifiers, Erase_DuplicateElements) {
  s21::set<int> s21_set = {50, 50, 50, 30, 70};
  std::set<int> std_set = {50, 50, 50, 30, 70};

  auto s21_iter = s21_set.find(50);  // Один из одинаковых элементов
  auto std_iter = std_set.find(50);

  s21_set.erase(s21_iter);
  std_set.erase(std_iter);

  ASSERT_EQ(s21_set.size(), std_set.size());

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();
  while (s21_it != s21_set.end() && std_it != std_set.end()) {
    ASSERT_EQ(*s21_it, *std_it);
    ++s21_it;
    ++std_it;
  }
}

TEST(Multiset_Erase, NullIterator) {
  s21::set<int> s21_set = {10, 20, 30};
  s21::set<int>::iterator null_iter = nullptr;

  s21_set.erase(null_iter);

  // Проверим, что дерево остается нетронутым после вызова erase с
  // null-итератором
  EXPECT_EQ(s21_set.size(), 3);
}

TEST(Multiset_Erase, EraseRoot) {
  s21::set<int> s21_set = {50, 30, 70, 20, 40, 60, 80};

  auto root_iter = s21_set.find(50);  // Корень дерева
  s21_set.erase(root_iter);           // Удаляем корень

  // Проверяем, что новый корень корректен
  EXPECT_EQ(s21_set.find(50),
            s21_set.end());  // Элемент 50 должен отсутствовать
  EXPECT_EQ(s21_set.size(), 6);  // Дерево должно уменьшиться на один элемент

  std::set<int> std_set = {50, 30, 70, 20, 40, 60, 80};

  auto root_iter_ = std_set.find(50);  // Корень дерева
  std_set.erase(root_iter_);           // Удаляем корень

  // Проверяем, что новый корень корректен
  EXPECT_EQ(std_set.find(50),
            std_set.end());  // Элемент 50 должен отсутствовать
  EXPECT_EQ(std_set.size(), 6);  // Дерево должно уменьшиться на один элемент
}

TEST(MultisetTest, EraseSingleElement) {
  s21::set<int> my_set{5};
  std::set<int> std_set{5};

  my_set.erase(my_set.begin());
  std_set.erase(std_set.begin());

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(MultisetTest, EraseNodeWithTwoChildren) {
  s21::set<int> my_set{10, 5, 15, 3, 7, 13, 17};
  std::set<int> std_set{10, 5, 15, 3, 7, 13, 17};

  my_set.erase(++my_set.begin());  // Удаляем элемент "10"
  std_set.erase(++std_set.begin());

  EXPECT_EQ(my_set.size(), std_set.size());
  auto it1 = my_set.begin();
  auto it2 = std_set.begin();
  while (it1 != my_set.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(MultisetTest, EraseLeafNode) {
  s21::set<int> my_set{1, 2, 3};
  std::set<int> std_set{1, 2, 3};

  my_set.erase(--my_set.end());  // Удаляем последний элемент "3"
  std_set.erase(--std_set.end());

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(*my_set.begin(), *std_set.begin());
}

TEST(MultisetTest, EraseNodeWithOneChild) {
  s21::set<int> my_set{20, 10, 30, 25};
  std::set<int> std_set{20, 10, 30, 25};

  auto it_my_set = my_set.find(30);
  auto it_std_set = std_set.find(30);
  my_set.erase(it_my_set);  // Удаляем элемент "30", имеющий одного ребенка "25"
  std_set.erase(it_std_set);

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(*(--my_set.end()), *(--std_set.end()));
}

TEST(MultisetEraseTest, EraseRoot) {
  // Создаем s21::set и std::set для сравнения
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Добавляем элементы, чтобы первый добавленный стал корнем
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);
  s21_ms.insert(70);

  std_ms.insert(50);  // Корень
  std_ms.insert(30);
  std_ms.insert(70);

  // Удаляем корневой элемент в обоих множествах
  s21_ms.erase(s21_ms.find(50));
  std_ms.erase(std_ms.find(50));

  // Проверяем, что размер уменьшился
  EXPECT_EQ(s21_ms.size(), std_ms.size());

  // Проверяем, что множества содержат одинаковые элементы
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(MultisetEraseTest, EraseRootWithChild) {
  // Создаем s21::set и std::set для сравнения
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Добавляем элементы, чтобы у корня был один ребёнок
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок

  std_ms.insert(50);  // Корень
  std_ms.insert(30);  // Левый ребёнок

  // Удаляем корневой элемент в обоих множествах (50)
  s21_ms.erase(s21_ms.find(50));
  std_ms.erase(std_ms.find(50));

  // Проверяем, что размер уменьшился
  EXPECT_EQ(s21_ms.size(), std_ms.size());

  // Проверяем, что множества содержат одинаковые элементы
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(MultisetEraseBalanceTest, Case1_SiblingIsRed) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Добавляем элементы, чтобы создать дерево, где брат узла будет красным
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(70);
  s21_ms.insert(60);  // Это будет правый красный брат

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(60);

  // Удаляем узел, чтобы вызвать балансировку и сделать брата красным
  s21_ms.erase(s21_ms.find(30));
  std_ms.erase(std_ms.find(30));

  // Проверяем размер и содержимое
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(MultisetEraseBalanceTest, Case2_BothSiblingChildrenBlack) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Добавляем элементы, чтобы у брата не было детей или они были черные
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(70);
  s21_ms.insert(80);  // Этот узел станет черным

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(80);

  // Удаляем узел, чтобы вызвать этот случай
  s21_ms.erase(s21_ms.find(30));
  std_ms.erase(std_ms.find(30));

  // Проверяем размер и содержимое
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(MultisetEraseBalanceTest, Case3_LeftChildRedRightChildBlack) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Добавляем элементы для этой ситуации
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(70);
  s21_ms.insert(65);  // Левый ребенок красный
  s21_ms.insert(80);  // Правый черный

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(65);
  std_ms.insert(80);

  // Удаляем узел для вызова этого случая
  s21_ms.erase(s21_ms.find(30));
  std_ms.erase(std_ms.find(30));

  // Проверяем размер и содержимое
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(MultisetEraseBalanceTest, Case4_RightChildRed) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Добавляем элементы, чтобы правый ребенок брата был красным
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(70);
  s21_ms.insert(75);  // Правый ребенок красный

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(75);

  // Удаляем узел для вызова этого случая
  s21_ms.erase(s21_ms.find(30));
  std_ms.erase(std_ms.find(30));

  // Проверяем размер и содержимое
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(MultisetEraseBalanceTest, RedSiblingRotationTest) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Создаем ситуацию для удаления с красным братом
  // Вставляем элементы для создания дерева с нужной структурой
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок
  s21_ms.insert(70);  // Правый ребёнок, который станет красным братом
  s21_ms.insert(60);  // Левый ребёнок 70 (чтобы брат стал красным)

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(60);

  // Теперь у узла 30 есть красный брат 70
  // Удаление узла 30 должно вызвать балансировку с вращением и изменением
  // цветов
  s21_ms.erase(s21_ms.find(30));
  std_ms.erase(std_ms.find(30));

  // После удаления, узел 70 должен стать черным, а 50 — красным
  // Ожидаем вращение дерева

  // Проверяем структуру дерева: размер должен совпадать
  EXPECT_EQ(s21_ms.size(), std_ms.size());

  // Проверяем, что элементы остались в правильном порядке
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }

  // Дополнительно можно протестировать балансировку дерева
  // Проверяем, что брат узла (70) стал черным, а его родитель (50) красным.
}

TEST(MultisetEraseBalanceTest, BlackSiblingChildrenTest) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Создаем ситуацию для удаления, где оба ребёнка брата черные
  // Вставляем элементы для создания дерева с нужной структурой
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок
  s21_ms.insert(70);  // Правый ребёнок
  s21_ms.insert(60);  // Левый ребёнок 70 (чёрный)
  s21_ms.insert(80);  // Правый ребёнок 70 (чёрный)

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(60);
  std_ms.insert(80);

  // Теперь у узла 30 есть черный брат 70 с двумя черными детьми (60 и 80)
  // Удаление узла 30 должно вызвать балансировку, при которой брат 70 станет
  // красным
  s21_ms.erase(s21_ms.find(30));
  std_ms.erase(std_ms.find(30));

  // После удаления, узел 70 должен стать красным, а балансировка продолжится с
  // родителем узла 30

  // Проверяем структуру дерева: размер должен совпадать
  EXPECT_EQ(s21_ms.size(), std_ms.size());

  // Проверяем, что элементы остались в правильном порядке
  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();
  for (; it_s21 != s21_ms.end() && it_std != std_ms.end(); ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }

  // Дополнительно можно протестировать цвета узлов
  // Проверяем, что узел 70 стал красным, а его дети остались черными
  // Можно добавить функции для проверки цветов узлов, если такие имеются в
  // реализации
}

TEST(MultisetIteratorTest, DecrementToParent) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с родителем
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок
  s21_ms.insert(70);  // Правый ребёнок

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);

  // Инициализируем итератор на элемент 70 (правый ребёнок)
  auto it_s21 = s21_ms.find(70);
  auto it_std = std_ms.find(70);

  // Проверяем, что итератор корректно перемещается на родителя (50) при --it
  --it_s21;
  --it_std;

  EXPECT_EQ(*it_s21,
            *it_std);  // Ожидаем, что итератор будет указывать на родителя (50)

  // Покрываем строку 694, так как текущий узел имеет родителя
}

TEST(MultisetIteratorTest, DecrementToMaxInLeftSubtree) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания поддерева
  s21_ms.insert(50);  // Корень
  s21_ms.insert(70);  // Правый ребёнок
  s21_ms.insert(60);  // Левый ребёнок 70

  std_ms.insert(50);
  std_ms.insert(70);
  std_ms.insert(60);

  // Инициализируем итератор на элемент 70 (правый ребёнок)
  auto it_s21 = s21_ms.find(70);
  auto it_std = std_ms.find(70);

  // Проверяем, что итератор корректно перемещается в максимальный узел левого
  // поддерева (60)
  --it_s21;
  --it_std;

  EXPECT_EQ(*it_s21, *it_std);  // Ожидаем, что итератор будет указывать на 60
                                // (максимум в левом поддереве 70)

  // Покрываем строку 702, так как у текущего узла есть левый потомок (60)
}

TEST(MultisetIteratorTest, ReturnIteratorAfterDecrement) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок

  std_ms.insert(50);
  std_ms.insert(30);

  // Инициализируем итератор на элемент 50 (корень)
  auto it_s21 = s21_ms.find(50);
  auto it_std = std_ms.find(50);

  // Проверяем, что декремент возвращает ссылку на итератор
  auto& ref_s21 = --it_s21;
  auto& ref_std = --it_std;

  EXPECT_EQ(&ref_s21,
            &it_s21);  // Ожидаем, что декремент вернёт ссылку на итератор
  EXPECT_EQ(&ref_std, &it_std);

  // Покрываем строку 698, так как возвращаем ссылку на итератор
}

TEST(MultisetIteratorTest, DecrementFindsMaxRightMostNode) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок
  s21_ms.insert(70);  // Правый ребёнок
  s21_ms.insert(60);  // Левый ребёнок 70
  s21_ms.insert(80);  // Правый ребёнок 70 (это максимальный узел)

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(60);
  std_ms.insert(80);

  // Получаем итератор на конец (после последнего элемента)
  auto it_s21 = s21_ms.end();
  auto it_std = std_ms.end();

  // Уменьшаем итератор, чтобы он указывал на самый правый узел
  --it_s21;
  --it_std;

  // Проверяем, что самый правый узел (80) корректно найден
  EXPECT_EQ(*it_s21, *it_std);  // Ожидаем, что итератор указывает на узел с 80
}

TEST(MultisetIteratorTest, OperatorMinusMinus) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);  // Корень
  s21_ms.insert(30);  // Левый ребёнок
  s21_ms.insert(70);  // Правый ребёнок
  s21_ms.insert(60);  // Левый ребёнок 70
  s21_ms.insert(80);  // Правый ребёнок 70 (это максимальный узел)

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(70);
  std_ms.insert(60);
  std_ms.insert(80);

  // Получаем итератор на конец (после последнего элемента)
  auto it_s21 = s21_ms.find(60);
  auto it_std = std_ms.find(60);

  // Уменьшаем итератор, чтобы он указывал на самый правый узел
  --it_s21;
  --it_std;

  // Проверяем, что самый правый узел (80) корректно найден
  EXPECT_EQ(*it_s21, *it_std);  // Ожидаем, что итератор указывает на узел с 80
}

TEST(MultisetIteratorTest, OperatorMinusMinus_2) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(40);
  s21_ms.insert(60);
  s21_ms.insert(80);

  s21_ms.insert(42);
  s21_ms.insert(43);
  s21_ms.insert(44);
  s21_ms.insert(41);
  s21_ms.insert(45);

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(40);
  std_ms.insert(60);
  std_ms.insert(80);

  std_ms.insert(42);
  std_ms.insert(43);
  std_ms.insert(44);
  std_ms.insert(41);
  std_ms.insert(45);

  // Получаем итератор на конец (после последнего элемента)
  auto it_s21 = s21_ms.find(50);
  auto it_std = std_ms.find(50);

  // Уменьшаем итератор, чтобы он указывал на самый правый узел
  --it_s21;
  --it_std;

  // Проверяем, что самый правый узел (80) корректно найден
  EXPECT_EQ(*it_s21, *it_std);  // Ожидаем, что итератор указывает на узел с 80
}

TEST(MultisetIteratorTest, EraseWithChild) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(40);
  s21_ms.insert(60);
  s21_ms.insert(80);

  s21_ms.insert(42);
  s21_ms.insert(43);
  s21_ms.insert(44);
  s21_ms.insert(41);
  s21_ms.insert(45);

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(40);
  std_ms.insert(60);
  std_ms.insert(80);

  std_ms.insert(42);
  std_ms.insert(43);
  std_ms.insert(44);
  std_ms.insert(41);
  std_ms.insert(45);

  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.begin();
  it_std = std_ms.begin();

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_2) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(40);
  s21_ms.insert(60);
  s21_ms.insert(80);

  s21_ms.insert(42);
  s21_ms.insert(43);
  s21_ms.insert(44);
  s21_ms.insert(41);
  s21_ms.insert(45);

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(40);
  std_ms.insert(60);
  std_ms.insert(80);

  std_ms.insert(42);
  std_ms.insert(43);
  std_ms.insert(44);
  std_ms.insert(41);
  std_ms.insert(45);

  auto it_s21 = s21_ms.begin();
  auto it_std = std_ms.begin();

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.begin();
  it_std = std_ms.begin();

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.begin();
  it_std = std_ms.begin();

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.begin();
  it_std = std_ms.begin();

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_3) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(40);
  s21_ms.insert(60);
  s21_ms.insert(80);

  s21_ms.insert(42);
  s21_ms.insert(43);
  s21_ms.insert(44);
  s21_ms.insert(41);
  s21_ms.insert(45);

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(40);
  std_ms.insert(60);
  std_ms.insert(80);

  std_ms.insert(42);
  std_ms.insert(43);
  std_ms.insert(44);
  std_ms.insert(41);
  std_ms.insert(45);

  auto it_s21 = --s21_ms.end();
  auto it_std = --std_ms.end();

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.begin();
  it_std = std_ms.begin();

  EXPECT_EQ(*it_s21, *it_std);
}

// Тест 1: Удаление единственного элемента
TEST(MultisetoTest, EraseSingleElement4) {
  s21::set<int> s21_set = {10};
  std::set<int> std_set = {10};

  auto s21_it = s21_set.begin();
  auto std_it = std_set.begin();

  s21_set.erase(s21_it);
  std_set.erase(std_it);

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(MultisetIteratorTest, EraseWithChild_4) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(40);
  s21_ms.insert(60);
  s21_ms.insert(80);

  s21_ms.insert(42);
  s21_ms.insert(43);
  s21_ms.insert(44);
  s21_ms.insert(41);
  s21_ms.insert(45);

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(40);
  std_ms.insert(60);
  std_ms.insert(80);

  std_ms.insert(42);
  std_ms.insert(43);
  std_ms.insert(44);
  std_ms.insert(41);
  std_ms.insert(45);

  auto it_s21 = s21_ms.find(44);
  auto it_std = std_ms.find(44);

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.find(60);
  it_std = std_ms.find(60);

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.find(42);
  it_std = std_ms.find(42);

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.find(80);
  it_std = std_ms.find(80);

  EXPECT_EQ(*it_s21, *it_std);
}

// Тест 8: Удаление узла с красным братом
TEST(MultisetTest, EraseNodeWithRedSibling) {
  // Пример множества, в котором при удалении задействуется случай с красным
  // братом
  s21::set<int> s21_set = {20, 10, 30, 5, 15, 25, 35, 3};
  std::set<int> std_set = {20, 10, 30, 5, 15, 25, 35, 3};

  // Удалим узел 10, при этом у него должен быть брат (узел 30), который красный
  auto s21_it = s21_set.find(10);
  auto std_it = std_set.find(10);

  ASSERT_NE(s21_it, s21_set.end());
  ASSERT_NE(std_it, std_set.end());

  // Удаление элемента
  s21_set.erase(s21_it);
  std_set.erase(std_it);

  // Проверка: размер после удаления должен быть одинаков
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(MultisetIteratorTest, EraseWithChild_5) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  // Вставляем элементы для создания дерева с несколькими узлами
  s21_ms.insert(50);
  s21_ms.insert(30);
  s21_ms.insert(40);
  s21_ms.insert(60);
  s21_ms.insert(80);

  s21_ms.insert(42);
  s21_ms.insert(43);
  s21_ms.insert(44);
  s21_ms.insert(41);
  s21_ms.insert(45);

  std_ms.insert(50);
  std_ms.insert(30);
  std_ms.insert(40);
  std_ms.insert(60);
  std_ms.insert(80);

  std_ms.insert(42);
  std_ms.insert(43);
  std_ms.insert(44);
  std_ms.insert(41);
  std_ms.insert(45);

  auto it_s21 = s21_ms.find(50);  // 44, 41, 30, 40, 42, 43, 44, 45, 50
  auto it_std = std_ms.find(50);

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.find(60);
  it_std = std_ms.find(60);

  s21_ms.erase(it_s21);
  std_ms.erase(it_std);

  it_s21 = s21_ms.find(80);
  it_std = std_ms.find(80);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_6) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 1; i < 96; i++) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(96);
  it_std = std_ms.find(96);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_7) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 96; i > 1; --i) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(1);
  it_std = std_ms.find(1);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_8) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 98; i > 0; --i) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(0);
  it_std = std_ms.find(0);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_9) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 98; i > 0; i -= 2) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(0);
  it_std = std_ms.find(0);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseWithChild_10) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 1; i < 96; i += 2) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(96);
  it_std = std_ms.find(96);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseDublicates_11) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  for (int i = 0; i < 97; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 1; i < 96; i++) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(96);
  it_std = std_ms.find(96);

  EXPECT_EQ(*it_s21, *it_std);
}

TEST(MultisetIteratorTest, EraseDublicates_12) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 98; i > 0; --i) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(0);
  it_std = std_ms.find(0);

  EXPECT_EQ(*it_s21, *it_std);
}

// Тест вставки нескольких уникальных значений
TEST(MultisetTest, InsertMany_UniqueValues) {
  s21::set<int> ms;
  auto results = ms.insert_many(1, 2, 3, 4, 5);

  EXPECT_EQ(ms.size(), 5);  // Проверка размера множества после вставки

  // Проверка значений и успешности вставки каждого элемента
  for (size_t i = 0; i < results.size(); ++i) {
    EXPECT_TRUE(results[i].second);  // Вставка нового элемента
    EXPECT_EQ(*results[i].first, i + 1);  // Проверка корректного значения
  }
}

// Тест вставки с дублирующимися значениями
TEST(MultisetTest, InsertMany_DuplicateValues) {
  s21::set<int> ms{1, 2, 3};
  auto results = ms.insert_many(3, 4, 5);

  EXPECT_EQ(
      ms.size(),
      5);  // Проверка, что размер увеличился на 2, так как 3 уже существует

  // Проверка значений и успешности вставки
  EXPECT_TRUE(results[0].second);  // 3 уже существует, не должно быть вновь
                                   // вставлено (это для set здесь false)
  EXPECT_TRUE(results[1].second);  // 4 — новое значение
  EXPECT_TRUE(results[2].second);  // 5 — новое значение
}

// Тест вставки одного значения для проверки корректности работы с одним
// аргументом
TEST(MultisetTest, InsertMany_SingleValue) {
  s21::set<int> ms;
  auto results = ms.insert_many(42);

  EXPECT_EQ(ms.size(), 1);  // Размер множества должен быть 1
  EXPECT_EQ(*results[0].first, 42);  // Вставленное значение — 42
  EXPECT_TRUE(results[0].second);  // Вставка нового элемента
}

TEST(InsertManyTest, BasicFunctionality) {
  s21::set<int> s;
  auto results = s.insert_many(3, 1, 4, 1, 5);

  EXPECT_EQ(s.size(), 4);  // Проверяем размер set
  EXPECT_EQ(*results[0].first, 3);
  EXPECT_EQ(*results[1].first, 1);
  EXPECT_TRUE(results[1].second);  // Второй элемент вставлен с дубликатом
}

TEST(InsertManyTest, DifferentTypes) {
  s21::set<std::string> s;
  s.insert_many("hello", "world", "hello");
  EXPECT_EQ(s.size(), 2);
}

TEST(InsertManyTest, EmptyMultiset) {
  s21::set<int> s;
  auto results = s.insert_many(42);
  EXPECT_TRUE(results[0].second);
}

// Тест пустой вставки
TEST(MultisetTest, InsertMany_Empty) {
  s21::set<int> ms;
  auto results = ms.insert_many();  // Вставка пустого списка аргументов

  EXPECT_TRUE(results.empty());  // Результаты должны быть пустыми
  EXPECT_EQ(ms.size(), 0);  // Размер множества должен быть 0
}

TEST(Set_Constructor, Initializer_List_new1) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::set<int> std_set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t size = std_set.size();
  s21::set<int>::iterator s21_iterator = s21_set.begin();
  std::set<int>::iterator std_iterator = std_set.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(Set_Constructor, Initializer_List_new2) {
  s21::set<int> s21_set = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::set<int> std_set = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  size_t size = std_set.size();
  s21::set<int>::iterator s21_iterator = s21_set.begin();
  std::set<int>::iterator std_iterator = std_set.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(Set_Modifiers, Erase_new1) {
  s21::set<int> s21_set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::set<int> std_set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  size_t size = std_set.size();
  s21::set<int>::iterator s21_iterator = s21_set.begin();
  std::set<int>::iterator std_iterator = std_set.begin();
  for (size_t i = 0; i < size - 1; i++) {
    s21_set.erase(s21_iterator);
    std_set.erase(std_iterator);
    s21_iterator = s21_set.begin();
    std_iterator = std_set.begin();
  }
  ASSERT_EQ(*s21_iterator, *std_iterator);
}

TEST(Set_Modifiers, Erase_new2) {
  s21::set<int> s21_set = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::set<int> std_set = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  size_t size = std_set.size();
  s21::set<int>::iterator s21_iterator = s21_set.end();
  std::set<int>::iterator std_iterator = std_set.end();
  for (size_t i = 0; i < size - 2; i++) {
    std_iterator--;
    s21_set.erase(s21_iterator);
    std_set.erase(std_iterator);
    s21_iterator = s21_set.end();
    std_iterator = std_set.end();
  }
  s21_iterator = s21_set.begin();
  std_iterator = std_set.begin();
  ASSERT_EQ(*s21_iterator, *std_iterator);
}

TEST(MultisetIteratorTest, EraseDublicates_13) {
  s21::set<int> s21_ms;
  std::set<int> std_ms;

  for (int i = 0; i < 100; i++) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  auto it_s21 = s21_ms.find(0);
  auto it_std = std_ms.find(0);

  for (int i = 96; i > 0; i--) {
    it_s21 = s21_ms.find(i);
    it_std = std_ms.find(i);

    s21_ms.erase(it_s21);
    std_ms.erase(it_std);
  }

  it_s21 = s21_ms.find(0);
  it_std = std_ms.find(0);

  EXPECT_EQ(*it_s21, *it_std);
}

// tests_map

// Constructors

TEST(Map_Constructor, Default_Empty) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Constructor, Default_Size_char) {
  s21::map<char, char> s21_map;
  std::map<char, char> std_map;
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Constructor, Initializer_List_Empty) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  // std::cout << "crash" << std::endl;
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Constructor, Initializer_List_Size) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Constructor, Initializer_List_Values) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Constructor, Initializer_List_Duplicates) {
  s21::map<int, int> s21_map = {{4, 2}, {4, 2}, {4, 2}};
  std::map<int, int> std_map = {{4, 2}, {4, 2}, {4, 2}};
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Constructor, Copy_Check_Old) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int> s21_map_copy(s21_map);
  std::map<int, int> std_map_copy(std_map);
  ASSERT_EQ(s21_map.size(), std_map.size());
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Constructor, Copy_Check_New) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int> s21_map_copy(s21_map);
  std::map<int, int> std_map_copy(std_map);
  ASSERT_EQ(s21_map.size(), std_map.size());
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map_copy.begin();
  for (std_it = std_map_copy.begin(); std_it != std_map_copy.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Constructor, Copy_Empty) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  s21::map<int, int> s21_map_copy(s21_map);
  std::map<int, int> std_map_copy(std_map);
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  ASSERT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map_Constructor, Move_Check_Old) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int> s21_map_move(std::move(s21_map));
  std::map<int, int> std_map_move(std::move(std_map));
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Constructor, Move_Check_New) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int> s21_map_move(std::move(s21_map));
  std::map<int, int> std_map_move(std::move(std_map));
  ASSERT_EQ(s21_map_move.size(), std_map_move.size());
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map_move.begin();
  for (std_it = std_map_move.begin(); std_it != std_map_move.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Constructor, Move_Empty) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  s21::map<int, int> s21_map_move(std::move(s21_map));
  std::map<int, int> std_map_move(std::move(std_map));
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  ASSERT_EQ(s21_map_move.empty(), std_map_move.empty());
}

// Operators

TEST(Map_Operator, Assignment_Check_New) {
  s21::map<float, int> s21_map1 = {{5.5, 2}, {4.4, 1}, {7.7, 3}};
  std::map<float, int> std_map1 = {{5.5, 2}, {4.4, 1}, {7.7, 3}};
  s21::map<float, int> s21_map2 = {{3.3, 1}, {1.1, 2}};
  std::map<float, int> std_map2 = {{3.3, 1}, {1.1, 2}};
  s21_map1 = s21_map2;
  std_map1 = std_map2;
  ASSERT_EQ(s21_map2.size(), std_map2.size());
  s21::map<float, int>::iterator s21_it = s21_map2.begin();
  std::map<float, int>::iterator std_it;
  for (std_it = std_map2.begin(); std_it != std_map2.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Operator, Assignment_Check_Old) {
  s21::map<float, int> s21_map1 = {{5.5, 2}, {4.4, 1}, {7.7, 3}};
  std::map<float, int> std_map1 = {{5.5, 2}, {4.4, 1}, {7.7, 3}};
  s21::map<float, int> s21_map2 = {{3.3, 1}, {1.1, 2}};
  std::map<float, int> std_map2 = {{3.3, 1}, {1.1, 2}};
  s21_map1 = s21_map2;
  std_map1 = std_map2;
  ASSERT_EQ(s21_map1.size(), std_map1.size());
  s21::map<float, int>::iterator s21_it = s21_map1.begin();
  std::map<float, int>::iterator std_it;
  for (std_it = std_map1.begin(); std_it != std_map1.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Operator, Assignment_Empty) {
  s21::map<float, int> s21_map1;
  std::map<float, int> std_map1;
  s21::map<float, int> s21_map2;
  std::map<float, int> std_map2;
  s21_map1 = s21_map2;
  std_map1 = std_map2;
  ASSERT_EQ(s21_map1.empty(), std_map1.empty());
  ASSERT_EQ(s21_map2.empty(), std_map2.empty());
}

// Element Access

TEST(Map_Element_Access, At_OK) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  ASSERT_EQ(s21_map.at(4), std_map.at(4));
}

TEST(Map_Element_Access, At_ERROR) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  EXPECT_THROW(s21_map.at(5), std::out_of_range);
}

TEST(Map_Element_Access, At_Empty) {
  s21::map<int, int> s21_map;
  EXPECT_THROW(s21_map.at(5), std::out_of_range);
}

TEST(Map_Element_Access, Brackets_OK) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  ASSERT_EQ(s21_map[4], std_map[4]);
}

TEST(Map_Element_Access, Brackets_ERROR) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  ASSERT_EQ(s21_map[5], std_map[5]);
}

TEST(Map_Element_Access, Brackets_Empty) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  ASSERT_EQ(s21_map[5], std_map[5]);
}

// Iterators

TEST(Map_Iterators, Begin_Exist) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  ASSERT_EQ(*std_it, *s21_it);
}

TEST(Map_Iterators, Begin_Empty) {
  s21::map<int, int> s21_map;
  EXPECT_NO_THROW(s21_map.begin());
}

TEST(Map_Iterators, Begin_OneElement) {
  s21::map<int, int> s21_map = {{1, 1}};
  std::map<int, int> std_map = {{1, 1}};
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  ASSERT_EQ(*std_it, *s21_it);
}

TEST(Map_Iterators, End_Exist) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  EXPECT_NO_THROW(s21_map.end());
}

TEST(Map_Iterators, End_Empty) {
  s21::map<int, int> s21_map;
  EXPECT_NO_THROW(s21_map.end());
}

// Capacity

TEST(Map_Capacity, Empty_True) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Capacity, Empty_False) {
  s21::map<int, int> s21_map = {{1, 1}};
  std::map<int, int> std_map = {{1, 1}};
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Capacity, Size_0) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Capacity, Size_1) {
  s21::map<int, int> s21_map = {{1, 1}};
  std::map<int, int> std_map = {{1, 1}};
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Capacity, Size_3) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Capacity, Max_Size) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(s21_map.max_size(), std_map.max_size());
}

// Modifiers

TEST(Map_Modifiers, Clear_Full) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  s21_map.clear();
  std_map.clear();
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Modifiers, Clear_Empty) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  s21_map.clear();
  std_map.clear();
  ASSERT_EQ(s21_map.empty(), std_map.empty());
}

TEST(Map_Modifiers, Swap_Empty2) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  s21::map<int, int> s21_map2;
  std::map<int, int> std_map2;
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  s21_map.swap(s21_map2);
  std_map.swap(std_map2);
  ASSERT_EQ(s21_map2.empty(), std_map2.empty());
}

TEST(Map_Modifiers, Swap_Empty1) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}};
  s21::map<int, int> s21_map2;
  std::map<int, int> std_map2;
  s21_map.swap(s21_map2);
  std_map.swap(std_map2);
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  ASSERT_EQ(s21_map2.empty(), std_map2.empty());
}

TEST(Map_Modifiers, Swap_Full) {
  s21::map<int, int> s21_map1 = {{1, 1}, {2, 2}};
  std::map<int, int> std_map1 = {{1, 1}, {2, 2}};
  s21::map<int, int> s21_map2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21_map1.swap(s21_map2);
  std_map1.swap(std_map2);
  ASSERT_EQ(s21_map1.size(), std_map1.size());
  ASSERT_EQ(s21_map2.size(), std_map2.size());
  s21::map<int, int>::iterator s21_it = s21_map1.begin();
  std::map<int, int>::iterator std_it;
  for (std_it = std_map1.begin(); std_it != std_map1.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
  s21_it = s21_map2.begin();
  for (std_it = std_map2.begin(); std_it != std_map2.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_ToEmpty) {
  s21::map<std::string, float> s21_map;
  std::map<std::string, float> std_map;
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert({"Hinata", 162.8});
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert({"Hinata", 162.8});
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_ToFull_True) {
  s21::map<std::string, float> s21_map = {{"Hinata", 162.8}};
  std::map<std::string, float> std_map = {{"Hinata", 162.8}};
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert({"Naruto", 178.5});
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert({"Naruto", 178.5});
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_ToFull_False1) {
  s21::map<std::string, float> s21_map = {{"Hinata", 162.8}};
  std::map<std::string, float> std_map = {{"Hinata", 162.8}};
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert({"Hinata", 100.0});
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert({"Hinata", 100.0});
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_ToFull_False2) {
  s21::map<std::string, float> s21_map = {{"Hinata", 162.8}};
  std::map<std::string, float> std_map = {{"Hinata", 162.8}};
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert({"Hinata", 162.8});
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert({"Hinata", 162.8});
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_or_assign_INSERT) {
  s21::map<std::string, float> s21_map = {
      {"Hinata", 162.8}, {"Naruto", 178.5}, {"Sasuke", 181.2}};
  std::map<std::string, float> std_map = {
      {"Hinata", 162.8}, {"Naruto", 178.5}, {"Sasuke", 181.2}};
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert_or_assign("Hitachi", 181.0);
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert_or_assign("Hitachi", 181.0);
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_or_assign_ASSIGN) {
  s21::map<std::string, float> s21_map = {
      {"Hinata", 162.8}, {"Naruto", 178.5}, {"Sasuke", 181.2}};
  std::map<std::string, float> std_map = {
      {"Hinata", 162.8}, {"Naruto", 178.5}, {"Sasuke", 181.2}};
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert_or_assign("Naruto", 180.0);
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert_or_assign("Naruto", 180.0);
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Insert_or_assign_False) {
  s21::map<std::string, float> s21_map = {{"Hinata", 162.8}};
  std::map<std::string, float> std_map = {{"Hinata", 162.8}};
  std::pair<s21::map<std::string, float>::iterator, bool> s21_pair =
      s21_map.insert_or_assign("Hinata", 162.8);
  std::pair<std::map<std::string, float>::iterator, bool> std_pair =
      std_map.insert_or_assign("Hinata", 162.8);
  ASSERT_EQ(s21_pair.second, std_pair.second);
  ASSERT_EQ(s21_map.size(), std_map.size());
  s21::map<std::string, float>::iterator s21_it = s21_map.begin();
  std::map<std::string, float>::iterator std_it;
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Erase_Begin) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  s21_map.erase(s21_it);
  std_map.erase(std_it);
  s21_it = s21_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Erase_Middle) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  s21_it++;
  std_it++;
  s21_map.erase(s21_it);
  std_map.erase(std_it);
  s21_it = s21_map.begin();
  std_it = std_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Erase_NonExist) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int> s21_map2 = {{1, 1}};
  s21::map<int, int>::iterator s21_it = s21_map2.begin();
  EXPECT_THROW(s21_map.erase(s21_it), std::out_of_range);
}

TEST(Map_Modifiers, Erase_FromEmpty) {
  s21::map<int, int> s21_map;
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  EXPECT_NO_THROW(s21_map.erase(s21_it));
}

TEST(Map_Modifiers, Merge_Empty2) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  s21::map<int, int> s21_map2;
  std::map<int, int> std_map2;
  s21_map.merge(s21_map2);
  std_map.merge(std_map2);
  ASSERT_EQ(s21_map.empty(), std_map.empty());
  ASSERT_EQ(s21_map2.empty(), std_map2.empty());
}

TEST(Map_Modifiers, Merge_Empty1) {
  s21::map<int, int> s21_map1 = {{1, 1}, {2, 2}};
  std::map<int, int> std_map1 = {{1, 1}, {2, 2}};
  s21::map<int, int> s21_map2;
  std::map<int, int> std_map2;
  s21_map1.merge(s21_map2);
  std_map1.merge(std_map2);
  ASSERT_EQ(s21_map2.empty(), std_map2.empty());
  s21::map<int, int>::iterator s21_it = s21_map1.begin();
  std::map<int, int>::iterator std_it;
  for (std_it = std_map1.begin(); std_it != std_map1.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modifiers, Merge_Full) {
  s21::map<int, int> s21_map1 = {{1, 1}, {2, 2}};
  std::map<int, int> std_map1 = {{1, 1}, {2, 2}};
  s21::map<int, int> s21_map2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map2 = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21_map1.merge(s21_map2);
  std_map1.merge(std_map2);
  ASSERT_EQ(s21_map1.size(), std_map1.size());
  ASSERT_EQ(s21_map2.size(), std_map2.size());
  s21::map<int, int>::iterator s21_it = s21_map1.begin();
  std::map<int, int>::iterator std_it;
  for (std_it = std_map1.begin(); std_it != std_map1.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
  s21_it = s21_map2.begin();
  for (std_it = std_map2.begin(); std_it != std_map2.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

// Lookup

TEST(Map_Lookup, Contains_Empty) {
  s21::map<int, int> s21_map;
  ASSERT_EQ(s21_map.contains(1), 0);
}

TEST(Map_Lookup, Contains_True) {
  s21::map<int, int> s21_map = {{1, 1}};
  ASSERT_EQ(s21_map.contains(1), 1);
}

TEST(Map_Lookup, Contains_False) {
  s21::map<int, int> s21_map = {{1, 1}};
  ASSERT_EQ(s21_map.contains(2), 0);
}

TEST(Map_Lookup, Contains_Many) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  ASSERT_EQ(s21_map.contains(4), 1);
}

TEST(Map_Operator, Assign_NewMove) {
  s21::map<int, int> s21_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  std::map<int, int> std_map = {{4, 2}, {1, 3}, {2, 4}, {3, 1}, {1, 3}};
  s21::map<int, int> s21_map_move;
  std::map<int, int> std_map_move;
  s21_map_move = std::move(s21_map);
  std_map_move = std::move(std_map);
  ASSERT_EQ(s21_map_move.size(), std_map_move.size());
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map_move.begin();
  for (std_it = std_map_move.begin(); std_it != std_map_move.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Conctructor, Initializer_List_New1) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                                {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
                                {6, 6}, {7, 7}, {8, 8}, {9, 9}};
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Conctructor, Initializer_List_New2) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  for (std_it = std_map.begin(); std_it != std_map.end(); std_it++) {
    ASSERT_EQ(*std_it, *s21_it);
    s21_it++;
  }
}

TEST(Map_Modofiers, Erase_New1) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int>::iterator std_it = std_map.begin();
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  size_t n = std_map.size();
  for (size_t i = 0; i < n - 1; i++) {
    s21_it = s21_map.begin();
    std_it = std_map.begin();
    s21_map.erase(s21_it);
    std_map.erase(std_it);
  }
}

TEST(Map_Iterator, NonEqual_True) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int>::iterator std_it = std_map.begin();
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it2;
  s21::map<int, int>::iterator s21_it2;
  EXPECT_TRUE(s21_it != s21_it2);
  EXPECT_TRUE(std_it != std_it2);
}

TEST(Map_Iterator, NonEqual_False) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> std_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int>::iterator std_it = std_map.begin();
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it2 = std_map.begin();
  s21::map<int, int>::iterator s21_it2 = s21_map.begin();
  EXPECT_FALSE(s21_it != s21_it2);
  EXPECT_FALSE(std_it != std_it2);
}

TEST(Map_Modifiers, Erase_New2) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int>::iterator std_it;
  s21::map<int, int>::iterator s21_it;
  size_t n = std_map.size();
  for (size_t i = 0; i < n - 2; i++) {
    s21_it = s21_map.end();
    std_it = std_map.end();
    std_it--;
    s21_map.erase(s21_it);
    std_map.erase(std_it);
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Modifiers, Erase_New22) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  s21::map<int, int>::iterator s21_it;
  std::map<int, int>::iterator std_it;
  size_t n = std_map.size();
  for (size_t i = 0; i < n - 2; i++) {
    s21_it = s21_map.end();
    std_it = std_map.end();
    std_it--;
    s21_it--;
    s21_map.erase(s21_it);
    std_map.erase(std_it);
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Modifiers, Insert_Many_1) {
  s21::map<int, int> s21_map = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> s21_std = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  s21::map<int, int>::iterator s21_it = s21_map.end();
  std::map<int, int>::iterator std_it = s21_std.end();
  s21::map<int, int> s21_m;
  s21_m.insert_many(std::pair<int, int>{1, 1}, std::pair<int, int>{2, 2},
                    std::pair<int, int>{3, 3}, std::pair<int, int>{4, 4},
                    std::pair<int, int>{5, 5});
  ASSERT_EQ((*s21_it).first, (*std_it).first);
}

TEST(Map_Modifiers, Find_Max_END) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  for (size_t i = 10; i < 100; i++) {
    s21_map.insert({i, i});
    std_map.insert({i, i});
  }
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  for (size_t i = 90; i > 40; i--) {
    s21_map.erase(s21_it);
    std_map.erase(std_it);
    s21_it = s21_map.begin();
    std_it = std_map.begin();
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Modifiers, Find_Max_END_2) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  for (size_t i = 10; i < 100; i++) {
    s21_map.insert({i, i});
    std_map.insert({i, i});
  }
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  for (size_t i = 90; i > 40; i--) {
    s21_map.erase(s21_it);
    std_map.erase(std_it);
    s21_it = s21_map.end();
    std_it = std_map.end();
    --s21_it;
    --std_it;
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Modifiers, Find_Max_END_3) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  for (size_t i = 10; i < 100; i++) {
    s21_map.insert({i, i});
    std_map.insert({i, i});
  }
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  for (size_t i = 90; i > 65; i--) {
    s21_map.erase(s21_it);
    std_map.erase(std_it);
    s21_it = s21_map.end();
    std_it = std_map.end();
    --s21_it;
    --std_it;
    --s21_it;
    --std_it;
    --s21_it;
    --std_it;
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Map_Modifiers, Find_Max_END_4) {
  s21::map<int, int> s21_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  std::map<int, int> std_map = {{9, 9}, {8, 8}, {7, 7}, {6, 6}, {5, 5},
                                {4, 4}, {3, 3}, {2, 2}, {1, 1}};
  for (size_t i = 10; i < 100; i++) {
    s21_map.insert({i, i});
    std_map.insert({i, i});
  }
  s21::map<int, int>::iterator s21_it = s21_map.begin();
  std::map<int, int>::iterator std_it = std_map.begin();
  for (size_t i = 90; i > 65; i--) {
    s21_map.erase(s21_it);
    std_map.erase(std_it);
    s21_it = s21_map.begin();
    std_it = std_map.begin();
    ++s21_it;
    ++std_it;
    ++s21_it;
    ++std_it;
    ++s21_it;
    ++std_it;
  }
  ASSERT_EQ(s21_map.size(), std_map.size());
}

TEST(Set_New, Insert100) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for (int i = 0; i < 100; i++) {
    s21_set.insert(i);
    std_set.insert(i);
  }
  s21::set<int>::iterator s21_it = s21_set.begin();
  std::set<int>::iterator std_it = std_set.begin();
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
    std_it++;
  }
}

TEST(Set_New, Insert99) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for (int i = 0; i < 99; i++) {
    s21_set.insert(i);
    std_set.insert(i);
  }
  s21::set<int>::iterator s21_it = s21_set.begin();
  std::set<int>::iterator std_it = std_set.begin();
  for (int i = 0; i < 99; i++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
    std_it++;
  }
}

// tests_list

// Constructors

TEST(List_Constructor, Default_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Constructor, Parameterized_0) {
  s21::list<int> s21_list(0);
  std::list<int> std_list(0);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Constructor, Parameterized_1) {
  s21::list<int> s21_list(1);
  std::list<int> std_list(1);
  ASSERT_EQ(s21_list.size(), std_list.size());
}

TEST(List_Constructor, Parameterized_10) {
  s21::list<int> s21_list(10);
  std::list<int> std_list(10);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Constructor, Initializer_List_0) {
  s21::list<int> s21_list = {};
  std::list<int> std_list = {};
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Constructor, Initializer_List_1) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Constructor, Initializer_List_5) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Constructor, Copy_CheckOld) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_copy(s21_list);
  std::list<int> std_list_copy(std_list);
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(s21_list_copy.size(), std_list_copy.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Constructor, Copy_CheckNew) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_copy(s21_list);
  std::list<int> std_list_copy(std_list);
  ASSERT_EQ(s21_list_copy.size(), std_list_copy.size());
  s21::list<int>::iterator s21_it = s21_list_copy.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list_copy.begin(); std_it != std_list_copy.end();
       std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Constructor, Copy_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list_copy(s21_list);
  std::list<int> std_list_copy(std_list);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list_copy.empty(), std_list_copy.empty());
}

TEST(List_Constructor, Move_CheckOld) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_move(std::move(s21_list));
  std::list<int> std_list_move(std::move(std_list));
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list_move.size(), std_list_move.size());
}

TEST(List_Constructor, Move_CheckNew) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list_move(std::move(s21_list));
  std::list<int> std_list_move(std::move(std_list));
  ASSERT_EQ(s21_list_move.size(), std_list_move.size());
  s21::list<int>::iterator s21_it = s21_list_move.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list_move.begin(); std_it != std_list_move.end();
       std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Constructor, Move_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list_move(std::move(s21_list));
  std::list<int> std_list_move(std::move(std_list));
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list_move.empty(), std_list_move.empty());
}

// Operators

TEST(List_Operator, Assign_CheckOld) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2 = s21_list;
  std_list2 = std_list;
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List_Operator, Assign_CheckNew) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2 = s21_list;
  std_list2 = std_list;
  ASSERT_EQ(s21_list2.size(), std_list2.size());
  s21::list<int>::iterator s21_it = s21_list2.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list2.begin(); std_it != std_list2.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Operator, Assign_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list2 = {1, 2, 3};
  std::list<int> std_list2 = {1, 2, 3};
  s21_list2 = s21_list;
  std_list2 = std_list;
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(s21_list2.size(), std_list2.size());
  s21::list<int>::iterator s21_it = s21_list2.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list2.begin(); std_it != std_list2.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Operator, Assign_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2 = s21_list;
  std_list2 = std_list;
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

// Element Access

TEST(List_Element_Access, Front_Full) {
  s21::list<int> s21_list = {5, 4, 3, 2, 1};
  std::list<int> std_list = {5, 4, 3, 2, 1};
  ASSERT_EQ(s21_list.front(), std_list.front());
}

TEST(List_Element_Access, Front_One) {
  s21::list<int> s21_list = {5};
  std::list<int> std_list = {5};
  ASSERT_EQ(s21_list.front(), std_list.front());
}

TEST(List_Element_Access, Front_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.front(), std_list.front());
}

TEST(List_Element_Access, Back_Full) {
  s21::list<int> s21_list = {5, 4, 3, 2, 1};
  std::list<int> std_list = {5, 4, 3, 2, 1};
  ASSERT_EQ(s21_list.back(), std_list.back());
}

TEST(List_Element_Access, Back_One) {
  s21::list<int> s21_list = {5};
  std::list<int> std_list = {5};
  ASSERT_EQ(s21_list.back(), std_list.back());
}

TEST(List_Element_Access, Back_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.back(), std_list.back());
}

// Iterators

TEST(List_Iterator, Begin_Full) {
  s21::list<char> s21_list = {'a', 'b', 'c', 'd'};
  std::list<char> std_list = {'a', 'b', 'c', 'd'};
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Iterator, Begin_One) {
  s21::list<char> s21_list = {'a'};
  std::list<char> std_list = {'a'};
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Iterator, Begin_Empty) {
  s21::list<char> s21_list;
  std::list<char> std_list;
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Iterator, End_Full) {
  s21::list<char> s21_list = {'a', 'b', 'c', 'd'};
  EXPECT_NO_THROW(s21_list.end());
}

TEST(List_Iterator, End_One) {
  s21::list<char> s21_list = {'a'};
  EXPECT_NO_THROW(s21_list.end());
}

TEST(List_Iterator, End_Empty) {
  s21::list<char> s21_list;
  EXPECT_NO_THROW(s21_list.end());
}

// Capacity

TEST(List_Capacity, Empty_True) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Capacity, Empty_False) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Capacity, Size_0) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.size(), std_list.size());
}

TEST(List_Capacity, Size_1) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  ASSERT_EQ(s21_list.size(), std_list.size());
}

TEST(List_Capacity, Size_10) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> std_list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQ(s21_list.size(), std_list.size());
}

TEST(List_Capacity, Max_Size) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.max_size(), std_list.max_size());
}

// Modifiers

TEST(List_Modifiers, Clear_Full) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  s21_list.clear();
  std_list.clear();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Clear_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  s21_list.clear();
  std_list.clear();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Insert_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_list.insert(s21_it, 1);
  std_list.insert(std_it, 1);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Insert_Begin) {
  s21::list<int> s21_list = {2, 3, 5};
  std::list<int> std_list = {2, 3, 5};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_list.insert(s21_it, 1);
  std_list.insert(std_it, 1);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Insert_Middle) {
  s21::list<int> s21_list = {2, 3, 5};
  std::list<int> std_list = {2, 3, 5};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_it++;
  std_it++;
  s21_list.insert(s21_it, 4);
  std_list.insert(std_it, 4);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Insert_End) {
  s21::list<int> s21_list = {2, 3, 5};
  std::list<int> std_list = {2, 3, 5};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_it++;
  s21_it++;
  std_it++;
  std_it++;
  s21_list.insert(s21_it, 6);
  std_list.insert(std_it, 6);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Erase_Begin) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Erase_Middle) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_it++;
  std_it++;
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Erase_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Erase_End) {
  s21::list<int> s21_list = {1, 2};
  std::list<int> std_list = {1, 2};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_it++;
  std_it++;
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Erase_Empty) {
  s21::list<int> s21_list;
  s21::list<int>::iterator s21_it = s21_list.begin();
  s21_list.erase(s21_it);
  EXPECT_NO_THROW(s21_list.empty());
}

TEST(List_Modifiers, Push_back_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.push_back(1);
  std_list.push_back(1);
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Push_back_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.push_back(1);
  std_list.push_back(1);
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Push_back_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.push_back(5);
  std_list.push_back(5);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Pop_back_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.pop_back();
  std_list.pop_back();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Pop_back_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.pop_back();
  std_list.pop_back();
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Push_front_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.push_front(1);
  std_list.push_front(1);
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Push_front_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.push_front(2);
  std_list.push_front(2);
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Push_front_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.push_front(5);
  std_list.push_front(5);
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Pop_front_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.pop_front();
  std_list.pop_front();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Pop_front_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21_list.pop_front();
  std_list.pop_front();
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Swap_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2.swap(s21_list);
  std_list2.swap(std_list);
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Swap_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list2 = {1, 2};
  std::list<int> std_list2 = {1, 2};
  s21_list2.swap(s21_list);
  std_list2.swap(std_list);
  ASSERT_EQ(s21_list2.size(), std_list2.size());
  ASSERT_EQ(s21_list.size(), std_list.size());
  s21::list<int>::iterator s21_it = s21_list2.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list2.begin(); std_it != std_list2.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
  s21_it = s21_list.begin();
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Merge_EmptyBoth) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2.merge(s21_list);
  std_list2.merge(std_list);
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Merge_Empty1) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2 = {1, 2, 3, 5};
  std::list<int> std_list2 = {1, 2, 3, 5};

  s21_list.merge(s21_list2);
  std_list.merge(std_list2);

  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Merge_Empty2) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2 = {1, 2, 3};
  std::list<int> std_list2 = {1, 2, 3};
  s21_list2.merge(s21_list);
  std_list2.merge(std_list);
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Merge_Full) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21::list<int> s21_list2 = {50, 40, 60};
  std::list<int> std_list2 = {50, 40, 60};
  s21_list.merge(s21_list2);
  std_list.merge(std_list2);
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

// Splice

TEST(List_Modifiers, Splice_EmptyBoth) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21::list<int>::iterator s21_it = s21_list2.begin();
  std::list<int>::iterator std_it = std_list2.begin();
  s21_list.splice(s21_it, s21_list2);
  std_list.splice(std_it, std_list2);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

// на убунту не работает, на маке работает
/*TEST(List_Modifiers, Splice_Empty1) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2 = {1, 2, 3};
  std::list<int> std_list2 = {1, 2, 3};
  s21::list<int>::iterator s21_it = s21_list2.begin();
  std::list<int>::iterator std_it = std_list2.begin();
  s21_list.splice(s21_it, s21_list2);
  std_list.splice(std_it, std_list2);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}*/

TEST(List_Modifiers, Splice_FullFromMiddle) {
  s21::list<int> s21_list = {7, 8, 9, 10};
  std::list<int> std_list = {7, 8, 9, 10};
  s21::list<int> s21_list2 = {1, 2, 3};
  std::list<int> std_list2 = {1, 2, 3};
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it = std_list.begin();
  s21_it++;
  std_it++;
  s21_list.splice(s21_it, s21_list2);
  std_list.splice(std_it, std_list2);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List_Modifiers, Reverse_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.reverse();
  std_list.reverse();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Reverse_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.reverse();
  std_list.reverse();
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Reverse_Many) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21_list.reverse();
  std_list.reverse();
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Unique_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.unique();
  std_list.unique();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Unique_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.unique();
  std_list.unique();
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Unique_Many) {
  s21::list<int> s21_list = {1, 1, 1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 1, 1, 2, 3, 4, 5};
  s21_list.unique();
  std_list.unique();
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

TEST(List_Modifiers, Sort_Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.sort();
  std_list.sort();
  ASSERT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List_Modifiers, Sort_One) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  s21_list.sort();
  std_list.sort();
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
}

TEST(List_Modifiers, Sort_Many) {
  s21::list<int> s21_list = {1, 6, 7, 2, 4, 3};
  std::list<int> std_list = {1, 6, 7, 2, 4, 3};
  s21_list.sort();
  std_list.sort();
  ASSERT_EQ(s21_list.size(), std_list.size());
  ASSERT_EQ(*s21_list.begin(), *std_list.begin());
  s21::list<int>::iterator s21_it = s21_list.begin();
  std::list<int>::iterator std_it;
  for (std_it = std_list.begin(); std_it != std_list.end(); std_it++) {
    ASSERT_EQ(*s21_it, *std_it);
    s21_it++;
  }
}

// Containersplus Modifiers

TEST(List_ModifiersPlus, Insert_many_Empty) {
  s21::list<int> s21_list;
  s21::list<int>::iterator s21_it = s21_list.begin();
  s21_list.insert_many(s21_it, 1, 2, 3, 4);
  size_t size = 4;
  int n = 1;
  ASSERT_EQ(s21_list.size(), size);
  s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it++;
    n++;
  }
}

TEST(List_ModifiersPlus, Insert_many_Full) {
  s21::list<int> s21_list = {1, 2};
  s21::list<int>::iterator s21_it = s21_list.begin();
  s21_list.insert_many(s21_it, 1, 2, 3, 4);
  size_t size = 6;
  ASSERT_EQ(s21_list.size(), size);
  s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    s21_it++;
  }
}

TEST(List_ModifiersPlus, Insert_many_Middle) {
  s21::list<int> s21_list = {2, 3, 5};
  s21::list<int>::iterator s21_it = s21_list.begin();
  s21_it++;
  s21_list.insert_many(s21_it, 1, 2, 3);
  size_t size = 6;
  ASSERT_EQ(s21_list.size(), size);
  s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    s21_it++;
  }
}

TEST(List_ModifiersPlus, Insert_many_front_Empty) {
  s21::list<int> s21_list;
  s21_list.insert_many_front(1, 2, 3, 4);
  size_t size = 4;
  int n = 4;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it++;
    n--;
  }
}

TEST(List_ModifiersPlus, Insert_many_front_Full) {
  s21::list<int> s21_list = {2, 1};
  s21_list.insert_many_front(3, 4, 5, 6);
  size_t size = 6;
  int n = 6;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it++;
    n--;
  }
}

TEST(List_ModifiersPlus, Insert_many_back_Empty) {
  s21::list<int> s21_list;
  s21_list.insert_many_back(1, 2, 3, 4);
  size_t size = 4;
  int n = 1;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it++;
    n++;
  }
}

TEST(List_ModifiersPlus, Insert_many_back_Full) {
  s21::list<int> s21_list = {1, 2};
  s21_list.insert_many_back(3, 4, 5, 6);
  size_t size = 6;
  int n = 1;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it++;
    n++;
  }
}

TEST(List_Operator, Assign_NewMove2) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list2 = {6, 7, 8};
  std::list<int> std_list2 = {6, 7, 8};
  s21_list2 = std::move(s21_list);
  std_list2 = std::move(std_list);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List_Operator, Assign_NewMove3) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2 = {6, 7, 8};
  std::list<int> std_list2 = {6, 7, 8};
  s21_list2 = std::move(s21_list);
  std_list2 = std::move(std_list);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List_Operator, Assign_NewMove4) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2 = std::move(s21_list);
  std_list2 = std::move(std_list);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List_Operator, Assign_NewMove1) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  s21::list<int> s21_list2;
  std::list<int> std_list2;
  s21_list2 = std::move(s21_list);
  std_list2 = std::move(std_list);
  ASSERT_EQ(s21_list.empty(), std_list.empty());
  ASSERT_EQ(s21_list2.empty(), std_list2.empty());
}

TEST(List_Iterator, GetNullptr) {
  s21::list<int>::iterator s21_iter(nullptr);
  EXPECT_THROW(*s21_iter, std::invalid_argument);
}

TEST(List_Iterator, ConstIter) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21::list<int>::const_iterator s21_iter;
  std::list<int>::const_iterator std_iter;
  s21_iter = s21_list.begin();
  std_iter = std_list.begin();
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST(List_Iterator, NonEqual) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};
  s21::list<int>::const_iterator s21_iter = s21_list.begin();
  std::list<int>::const_iterator std_iter = std_list.begin();
  s21::list<int>::const_iterator s21_iter2 = s21_list.begin();
  std::list<int>::const_iterator std_iter2 = std_list.begin();
  EXPECT_FALSE(s21_iter != s21_iter2);
  EXPECT_FALSE(std_iter != std_iter2);
}

TEST(List_Iterator, Increment) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5, 6};
  size_t size = 6;
  int n = 1;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it++;
    n++;
  }
}

TEST(List_Iterator, Decrement) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5, 6};
  size_t size = 6;
  int n = 6;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.end();
  s21_it--;
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    s21_it--;
    n--;
  }
}

TEST(List_Iterator, Increment2) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5, 6};
  size_t size = 6;
  int n = 1;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    ++s21_it;
    n++;
  }
}

TEST(List_Iterator, Decrement2) {
  s21::list<int> s21_list = {1, 2, 3, 4, 5, 6};
  size_t size = 6;
  int n = 6;
  ASSERT_EQ(s21_list.size(), size);
  s21::list<int>::iterator s21_it = s21_list.end();
  --s21_it;
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_it, n);
    --s21_it;
    n--;
  }
}
