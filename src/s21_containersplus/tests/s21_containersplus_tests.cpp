#include <gtest/gtest.h>

#include <climits>

#include "../s21_containersplus.h"

// multiset_tests

TEST(multiset_Iterator, End) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int>::iterator s21_iterator = s21_mset.end();
  std::multiset<int>::iterator std_iterator = std_mset.end();
  std_iterator--;
  s21_iterator--;
  ASSERT_EQ(*s21_iterator, *std_iterator);
}

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  std::multiset<int> ms_;
  EXPECT_TRUE(ms_.empty());
  EXPECT_EQ(ms_.size(), 0);
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), 5);
  EXPECT_EQ(ms.count(3), 1);  // 3 присутствует
  EXPECT_EQ(ms.count(6), 0);  // 6 отсутствует

  std::multiset<int> ms_ = {1, 2, 3, 4, 5};
  EXPECT_FALSE(ms_.empty());
  EXPECT_EQ(ms_.size(), 5);
  EXPECT_EQ(ms_.count(3), 1);  // 3 присутствует
  EXPECT_EQ(ms_.count(6), 0);  // 6 отсутствует
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1 = {1, 2, 2, 3};
  s21::multiset<int> ms2(ms1);  // Копируем ms1 в ms2

  EXPECT_FALSE(ms2.empty());
  EXPECT_EQ(ms2.size(), 4);
  EXPECT_EQ(ms2.count(2), 2);  // Проверяем, что количество 2 верно

  std::multiset<int> ms1_ = {1, 2, 2, 3};
  std::multiset<int> ms2_(ms1_);  // Копируем ms1 в ms2

  EXPECT_FALSE(ms2_.empty());
  EXPECT_EQ(ms2_.size(), 4);
  EXPECT_EQ(ms2_.count(2), 2);  // Проверяем, что количество 2 верно
}

TEST(MultisetTest, CopyConstructorSimple) {
  s21::multiset<int> ms1 = {2, 1, 2, 2, 3, 2, 2};
  s21::multiset<int> ms2(ms1);  // Используем конструктор копирования

  std::multiset<int> ms1_ = {2, 1, 2, 2, 3, 2, 2};
  std::multiset<int> ms2_(ms1_);  // Используем конструктор копирования

  EXPECT_EQ(ms2.count(2), 5);   // Ожидаем 2 вхождения
  EXPECT_EQ(ms2_.count(2), 5);  // Ожидаем 2 вхождения
}

TEST(MultisetTest, CopyConstructor0) {
  s21::multiset<int> ms1 = {2, 2, 3, 4, 5};
  s21::multiset<int> ms2(ms1);  // Используем конструктор копирования

  std::multiset<int> ms1_ = {2, 2, 3, 4, 5};
  std::multiset<int> ms2_(ms1_);  // Используем конструктор копирования

  EXPECT_EQ(ms2.count(2), 2);  // Ожидаем 2 вхождения
  EXPECT_EQ(ms2.count(2), 2);  // Ожидаем 1 вхождение
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));  // Перемещаем ms1 в ms2

  EXPECT_TRUE(ms1.empty());  // ms1 теперь должен быть пустым
  EXPECT_FALSE(ms2.empty());
  EXPECT_EQ(ms2.size(), 3);

  std::multiset<int> ms1_ = {1, 2, 3};
  std::multiset<int> ms2_(std::move(ms1_));  // Перемещаем ms1 в ms2

  EXPECT_TRUE(ms1_.empty());  // ms1 теперь должен быть пустым
  EXPECT_FALSE(ms2_.empty());
  EXPECT_EQ(ms2_.size(), 3);
}

TEST(MultisetTest, MoveConstructorEmpty) {
  s21::multiset<int> ms1;                  // Пустой
  s21::multiset<int> ms2(std::move(ms1));  // Перемещаем пустой multiset

  EXPECT_TRUE(ms1.empty());  // ms1 все еще пуст
  EXPECT_TRUE(ms2.empty());  // ms2 тоже пуст

  std::multiset<int> ms1_;                   // Пустой
  std::multiset<int> ms2_(std::move(ms1_));  // Перемещаем пустой multiset

  EXPECT_TRUE(ms1_.empty());  // ms1 все еще пуст
  EXPECT_TRUE(ms2_.empty());  // ms2 тоже пуст
}

TEST(MultisetTest, CopyConstructorSelfAssignment) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(ms1);  // Копируем в новый объект

  // Убедимся, что изменение одного не повлияло на другой
  ms1.insert(4);
  EXPECT_EQ(ms1.size(), 4);
  EXPECT_EQ(ms2.size(), 3);

  std::multiset<int> ms1_ = {1, 2, 3};
  std::multiset<int> ms2_(ms1_);  // Копируем в новый объект

  // Убедимся, что изменение одного не повлияло на другой
  ms1_.insert(4);
  EXPECT_EQ(ms1_.size(), 4);
  EXPECT_EQ(ms2_.size(), 3);
}

TEST(MultisetTest, InitializerListEmpty) {
  s21::multiset<int> ms = {};  // Пустой инициализирующий список
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);

  std::multiset<int> ms_ = {};  // Пустой инициализирующий список
  EXPECT_TRUE(ms_.empty());
  EXPECT_EQ(ms_.size(), 0);
}

TEST(MultisetTest, CopyConstructorWithEmptyTree) {
  // Создаем пустое дерево
  s21::multiset<int> original_multiset;

  // Копируем пустое дерево
  s21::multiset<int> copied_multiset(original_multiset);

  // Проверяем, что новое дерево пустое
  EXPECT_TRUE(copied_multiset.empty());
  EXPECT_EQ(copied_multiset.size(), 0);

  // Создаем пустое дерево
  std::multiset<int> original_multiset_;

  // Копируем пустое дерево
  std::multiset<int> copied_multiset_(original_multiset_);

  // Проверяем, что новое дерево пустое
  EXPECT_TRUE(copied_multiset_.empty());
  EXPECT_EQ(copied_multiset_.size(), 0);
}

// Тест для оператора присваивания копированием
TEST(MultisetTest, CopyAssignment_NonEmptyToEmpty) {
  s21::multiset<int> ms1;  // Пустое множество
  s21::multiset<int> ms2{1, 2, 3};  // Множество с тремя элементами

  // Присваивание пустому множеству непустого
  ms1 = ms2;
  EXPECT_EQ(ms1.size(), 3);  // Размер должен совпадать
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
}

TEST(MultisetTest, CopyAssignment_SelfAssignment) {
  s21::multiset<int> ms2{1, 2, 3};  // Множество с тремя элементами

  // Присваивание самому себе
  ms2 = ms2;
  EXPECT_EQ(ms2.size(), 3);  // Проверяем, что размер не изменился
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, CopyAssignment_EmptyToEmpty) {
  s21::multiset<int> ms1;        // Пустое множество
  s21::multiset<int> empty_set;  // Пустое множество

  // Присваивание пустого множества другому пустому
  ms1 = empty_set;
  EXPECT_EQ(ms1.size(), 0);  // Оба множества должны быть пустыми

  std::multiset<int> ms1_;        // Пустое множество
  std::multiset<int> empty_set_;  // Пустое множество

  // Присваивание пустого множества другому пустому
  ms1_ = empty_set_;
  EXPECT_EQ(ms1_.size(), 0);  // Оба множества должны быть пустыми
}

// Тест для оператора присваивания перемещением
TEST(MultisetTest, MoveAssignment_NonEmptyToEmpty) {
  s21::multiset<int> ms1;  // Пустое множество
  s21::multiset<int> ms2{1, 2, 3};  // Множество с тремя элементами

  // Перемещение в пустое множество
  ms1 = std::move(ms2);
  EXPECT_EQ(ms1.size(), 3);  // Проверяем, что элементы были перемещены
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_EQ(ms2.size(), 0);  // Исходное множество должно быть пустым
}

TEST(MultisetTest, MoveAssignment_SelfMove) {
  s21::multiset<int> ms1{1, 2, 3};  // Множество с тремя элементами

  // Перемещение самого себя
  ms1 = std::move(ms1);  // Должно корректно работать и не крашиться
  EXPECT_EQ(ms1.size(), 3);  // Размер не должен измениться
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
}

// Тесты для итераторов begin() и end()
TEST(MultisetTest, Iterators_EmptySet) {
  s21::multiset<int> empty_set;  // Пустое множество

  // Для пустого множества begin() == end()
  EXPECT_EQ(empty_set.begin(), empty_set.end());

  std::multiset<int> empty_set_;  // Пустое множество

  // Для пустого множества begin() == end()
  EXPECT_EQ(empty_set_.begin(), empty_set_.end());
}

TEST(MultisetTest, Iterators_EdgeCase) {
  s21::multiset<int> single_element_set{42};  // Множество с одним элементом

  // Итератор для множества с одним элементом
  EXPECT_EQ(*single_element_set.begin(), 42);

  // Модификация множества и проверка итераторов
  single_element_set.insert(100);
  auto it = single_element_set.begin();
  EXPECT_EQ(*it, 42);  // Элементы должны остаться отсортированными

  std::multiset<int> single_element_set_{42};  // Множество с одним элементом

  // Итератор для множества с одним элементом
  EXPECT_EQ(*single_element_set_.begin(), 42);

  // Модификация множества и проверка итераторов
  single_element_set_.insert(100);
  auto it_ = single_element_set_.begin();
  EXPECT_EQ(*it_, 42);  // Элементы должны остаться отсортированными
}

TEST(Multiset_CopyAssignment, AssignEmptyToEmpty) {
  s21::multiset<int> set1;
  s21::multiset<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(), 0);  // Ожидаем, что размер равен 0
  EXPECT_TRUE(set2.empty());  // Проверка на пустоту
  EXPECT_EQ(set2.begin(),
            set2.end());  // Итераторы должны быть равны для пустого множества

  std::multiset<int> set1_;
  std::multiset<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 0);  // Ожидаем, что размер равен 0
  EXPECT_TRUE(set2_.empty());  // Проверка на пустоту
  EXPECT_EQ(set2_.begin(),
            set2_.end());  // Итераторы должны быть равны для пустого множества
}

TEST(Multiset_CopyAssignment, AssignNonEmptyToEmpty) {
  s21::multiset<int> set1 = {1, 2, 3};
  s21::multiset<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(), 3);  // Ожидаем размер 3
  EXPECT_FALSE(set2.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы были корректно скопированы
  auto it = set2.begin();
  EXPECT_EQ(*it, 1);

  std::multiset<int> set1_ = {1, 2, 3};
  std::multiset<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 3);  // Ожидаем размер 3
  EXPECT_FALSE(set2_.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы были корректно скопированы
  auto it_ = set2_.begin();
  EXPECT_EQ(*it_, 1);
}

TEST(Multiset_CopyAssignment, AssignEmptyToNonEmpty) {
  s21::multiset<int> set1;
  s21::multiset<int> set2 = {4, 5, 6};

  set2 = set1;

  EXPECT_EQ(set2.size(), 0);  // Ожидаем, что размер стал 0
  EXPECT_TRUE(set2.empty());  // Проверка на пустоту
  EXPECT_EQ(set2.begin(),
            set2.end());  // Итераторы должны быть равны для пустого множества

  std::multiset<int> set1_;
  std::multiset<int> set2_ = {4, 5, 6};

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 0);  // Ожидаем, что размер стал 0
  EXPECT_TRUE(set2_.empty());  // Проверка на пустоту
  EXPECT_EQ(set2_.begin(),
            set2_.end());  // Итераторы должны быть равны для пустого множества
}

TEST(Multiset_CopyAssignment, SelfAssignment) {
  s21::multiset<int> set1 = {7, 8, 9};

  set1 = set1;  // Присваиваем самому себе

  EXPECT_EQ(set1.size(), 3);  // Ожидаем, что размер не изменится
  EXPECT_FALSE(set1.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы остались на своих местах
  auto it = set1.begin();
  EXPECT_EQ(*it, 7);

  std::multiset<int> set1_ = {7, 8, 9};

  set1_ = set1_;  // Присваиваем самому себе

  EXPECT_EQ(set1_.size(), 3);  // Ожидаем, что размер не изменится
  EXPECT_FALSE(set1_.empty());  // Множество не должно быть пустым

  // Проверяем, что элементы остались на своих местах
  auto it_ = set1_.begin();
  EXPECT_EQ(*it_, 7);
}

TEST(Multiset_CopyAssignment, Duplicates) {
  s21::multiset<int> set1 = {10, 10, 20, 20, 30};
  s21::multiset<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(),
            5);  // Ожидаем, что все элементы скопированы, включая дубликаты
  EXPECT_FALSE(set2.empty());

  // Проверяем, что дубликаты были корректно скопированы
  auto it = set2.begin();
  EXPECT_EQ(*it, 10);

  std::multiset<int> set1_ = {10, 10, 20, 20, 30};
  std::multiset<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(),
            5);  // Ожидаем, что все элементы скопированы, включая дубликаты
  EXPECT_FALSE(set2_.empty());

  // Проверяем, что дубликаты были корректно скопированы
  auto it_ = set2_.begin();
  EXPECT_EQ(*it_, 10);
}

TEST(Multiset_CopyAssignment, SingleElement) {
  s21::multiset<int> set1 = {42};
  s21::multiset<int> set2;

  set2 = set1;

  EXPECT_EQ(set2.size(), 1);  // Ожидаем размер 1
  EXPECT_FALSE(set2.empty());  // Множество не должно быть пустым

  auto it = set2.begin();
  EXPECT_EQ(*it++, 42);  // Проверяем, что единственный элемент скопирован

  std::multiset<int> set1_ = {42};
  std::multiset<int> set2_;

  set2_ = set1_;

  EXPECT_EQ(set2_.size(), 1);  // Ожидаем размер 1
  EXPECT_FALSE(set2_.empty());  // Множество не должно быть пустым

  auto it_ = set2_.begin();
  EXPECT_EQ(*it_++, 42);  // Проверяем, что единственный элемент скопирован
}

TEST(Multiset_CopyAssignment, MaxSize) {
  s21::multiset<int> ms;
  EXPECT_GT(ms.max_size(),
            0);  // Убедиться, что max_size() возвращает положительное значение

  std::multiset<int> ms_;
  EXPECT_GT(ms_.max_size(),
            0);  // Убедиться, что max_size() возвращает положительное значение
}

TEST(MultisetTest, Clear_EmptySet) {
  s21::multiset<int> ms;
  ms.clear();  // Очищаем пустое множество
  EXPECT_TRUE(ms.empty());  // Множество должно оставаться пустым

  std::multiset<int> ms_;
  ms_.clear();  // Очищаем пустое множество
  EXPECT_TRUE(ms_.empty());  // Множество должно оставаться пустым
}

TEST(MultisetTest, Clear_NonEmptySet) {
  s21::multiset<int> ms{1, 2, 3};
  ms.clear();  // Очищаем множество с элементами
  EXPECT_TRUE(ms.empty());  // Множество должно стать пустым
  EXPECT_EQ(ms.size(), 0);  // Размер должен быть 0

  std::multiset<int> ms_{1, 2, 3};
  ms_.clear();  // Очищаем множество с элементами
  EXPECT_TRUE(ms_.empty());  // Множество должно стать пустым
  EXPECT_EQ(ms_.size(), 0);  // Размер должен быть 0
}

TEST(MultisetTest, Clear_AfterInsertions) {
  s21::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(3);
  ms.clear();  // Очищаем множество после вставки
  EXPECT_TRUE(ms.empty());  // Множество должно быть пустым
  EXPECT_EQ(ms.size(), 0);  // Размер должен быть 0

  s21::multiset<int> ms_;
  ms_.insert(1);
  ms_.insert(2);
  ms_.insert(3);
  ms_.clear();  // Очищаем множество после вставки
  EXPECT_TRUE(ms_.empty());  // Множество должно быть пустым
  EXPECT_EQ(ms_.size(), 0);  // Размер должен быть 0
}

TEST(MultisetTest, Insert_IntoEmptySet) {
  s21::multiset<int> ms;
  ms.insert(1);  // Вставляем в пустое множество
  EXPECT_TRUE(ms.contains(1));  // Элемент должен появиться в множестве
  EXPECT_EQ(ms.size(), 1);  // Размер должен быть 1
}

TEST(MultisetTest, Insert_DuplicateElements) {
  s21::multiset<int> ms;
  ms.insert(1);
  ms.insert(1);  // Вставляем дубликат
  EXPECT_TRUE(ms.contains(1));  // Элемент должен яичница присутствовать
  EXPECT_EQ(ms.size(), 2);  // Размер должен увеличиться
}

TEST(MultisetTest, Insert_MultipleElements) {
  s21::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(3);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
  EXPECT_EQ(ms.size(), 3);  // Множество должно содержать три элемента
}

TEST(MultisetTest, Swap_TwoEmptySets) {
  s21::multiset<int> ms1;
  s21::multiset<int> ms2;
  ms1.swap(ms2);  // Меняем пустые множества
  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms2.empty());

  std::multiset<int> ms1_;
  std::multiset<int> ms2_;
  ms1_.swap(ms2_);  // Меняем пустые множества
  EXPECT_TRUE(ms1_.empty());
  EXPECT_TRUE(ms2_.empty());
}

TEST(MultisetTest, Swap_NonEmptyWithEmpty) {
  s21::multiset<int> ms1{1, 2, 3};
  s21::multiset<int> ms2;
  ms1.swap(ms2);  // Меняем непустое множество с пустым
  EXPECT_TRUE(ms1.empty());
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, Swap_TwoNonEmptySets) {
  s21::multiset<int> ms1{1, 2};
  s21::multiset<int> ms2{3, 4};
  ms1.swap(ms2);  // Меняем два непустых множества
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
}

TEST(MultisetTest, Merge_TwoEmptySets) {
  s21::multiset<int> ms1;
  s21::multiset<int> ms2;
  ms1.merge(ms2);  // Мержим два пустых множества
  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms2.empty());

  std::multiset<int> ms1_;
  std::multiset<int> ms2_;
  ms1_.merge(ms2_);  // Мержим два пустых множества
  EXPECT_TRUE(ms1_.empty());
  EXPECT_TRUE(ms2_.empty());
}

TEST(MultisetTest, Merge_EmptyWithNonEmpty) {
  s21::multiset<int> ms1;
  s21::multiset<int> ms2{1, 2, 3};
  ms1.merge(ms2);  // Мержим пустое множество с непустым
  EXPECT_EQ(ms1.size(), 3);
  EXPECT_TRUE(ms2.empty());  // Второе множество должно стать пустым

  std::multiset<int> ms1_;
  std::multiset<int> ms2_{1, 2, 3};
  ms1_.merge(ms2_);  // Мержим пустое множество с непустым
  EXPECT_EQ(ms1_.size(), 3);
  EXPECT_TRUE(ms2_.empty());  // Второе множество должно стать пустым
}

TEST(MultisetTest, Merge_NonEmptyWithEmpty) {
  s21::multiset<int> ms1{1, 2, 3};
  s21::multiset<int> ms2;
  ms1.merge(ms2);  // Мержим непустое множество с пустым
  EXPECT_EQ(ms1.size(), 3);  // Множество ms1 должно остаться прежним
  EXPECT_TRUE(ms2.empty());  // Второе множество должно оставаться пустым

  std::multiset<int> ms1_{1, 2, 3};
  std::multiset<int> ms2_;
  ms1_.merge(ms2_);  // Мержим непустое множество с пустым
  EXPECT_EQ(ms1_.size(), 3);  // Множество ms1 должно остаться прежним
  EXPECT_TRUE(ms2_.empty());  // Второе множество должно оставаться пустым
}

TEST(MultisetTest, Merge_TwoNonEmptySets) {
  s21::multiset<int> ms1{1, 2};
  s21::multiset<int> ms2{2, 3, 4};
  ms1.merge(ms2);  // Мержим два непустых множества
  EXPECT_EQ(ms1.size(), 5);  // Элементы должны объединиться
  EXPECT_TRUE(ms1.contains(1));
  EXPECT_TRUE(ms1.contains(2));
  EXPECT_TRUE(ms1.contains(3));
  EXPECT_TRUE(ms1.contains(4));

  EXPECT_FALSE(ms2.contains(1));
  EXPECT_FALSE(ms2.contains(2));
  EXPECT_FALSE(ms2.contains(3));
  EXPECT_FALSE(ms2.contains(4));

  EXPECT_TRUE(ms2.empty());  // Второе множество должно стать пустым

  std::multiset<int> ms1_{1, 2};
  std::multiset<int> ms2_{2, 3, 4};
  ms1_.merge(ms2_);  // Мержим два непустых множества
  EXPECT_EQ(ms1_.size(), 5);  // Элементы должны объединиться
  EXPECT_TRUE(ms1_.find(1) != ms1_.end());
  EXPECT_TRUE(ms1_.find(2) != ms1_.end());
  EXPECT_TRUE(ms1_.find(3) != ms1_.end());
  EXPECT_TRUE(ms1_.find(4) != ms1_.end());

  EXPECT_FALSE(ms2_.find(1) != ms2_.end());
  EXPECT_FALSE(ms2_.find(2) != ms2_.end());
  EXPECT_FALSE(ms2_.find(3) != ms2_.end());
  EXPECT_FALSE(ms2_.find(4) != ms2_.end());

  EXPECT_TRUE(ms2_.empty());  // Второе множество должно стать пустым
}

TEST(Multiset_Constructor0, Default_Empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Constructor0, Initializer_List) {
  s21::multiset<int> s21_mset = {2, 2, 1, 3, 4};
  std::multiset<int> std_mset = {2, 2, 1, 3, 4};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::multiset<int>::iterator s21_iter = s21_mset.begin();
  std::multiset<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor0, Copy_Check_Old) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::multiset<int>::iterator s21_iter = s21_mset.begin();
  std::multiset<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor0, Copy_Check_New) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  size_t size = std_mset_copy.size();
  s21::multiset<int>::iterator s21_iter = s21_mset_copy.begin();
  std::multiset<int>::iterator std_iter = std_mset_copy.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor0, Move_Check_Old) {
  s21::multiset<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::multiset<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::multiset<int> s21_mset_move(std::move(s21_mset));
  std::multiset<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Constructor0, Move_Check_New) {
  s21::multiset<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::multiset<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::multiset<int> s21_mset_move(std::move(s21_mset));
  std::multiset<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset_move.size(), std_mset_move.size());
  size_t size = std_mset_move.size();
  s21::multiset<int>::iterator s21_iter = s21_mset_move.begin();
  std::multiset<int>::iterator std_iter = std_mset_move.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Operator, Assignment) {
  s21::multiset<float> s21_mset1 = {5.5, 4.4, 7.7};
  std::multiset<float> std_mset1 = {5.5, 4.4, 7.7};
  s21::multiset<float> s21_mset2 = {3.3, 1.1};
  std::multiset<float> std_mset2 = {3.3, 1.1};
  s21_mset1 = s21_mset2;
  std_mset1 = std_mset2;
  ASSERT_EQ(s21_mset2.size(), std_mset2.size());
  size_t size = std_mset2.size();
  s21::multiset<float>::iterator s21_iter = s21_mset2.begin();
  std::multiset<float>::iterator std_iter = std_mset2.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Iterator, Begin) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(*s21_mset.begin(), *std_mset.begin());
}

TEST(Multiset_Capacity, Empty_False) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity, Empty_True) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity, Size_0) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Capacity, Size_1) {
  s21::multiset<int> s21_mset = {5};
  std::multiset<int> std_mset = {5};
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Modifiers, Clear_Full) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers, Clear_Empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers, Insert_End) {
  s21::multiset<char> s21_set = {'b', 'c', 'd'};
  std::multiset<char> std_set = {'b', 'c', 'd'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
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
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
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
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'a'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'a'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
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
  s21::multiset<char> s21_set;
  std::multiset<char> std_set;
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers, Insert_Duplicate) {
  s21::multiset<char> s21_set = {'a'};
  std::multiset<char> std_set = {'a'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers, Erase_Leaf) {
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
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
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'e'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'e'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
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
  s21::multiset<char> s21_set = {'c', 'e', 'd', 'f'};
  std::multiset<char> std_set = {'c', 'e', 'd', 'f'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
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
  s21::multiset<char> s21_set = {'c'};
  std::multiset<char> std_set = {'c'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);
  std_set.erase(std_iter);
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset_Modifiers, Swap_Empty) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2;
  std::multiset<std::string> std_set2;
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  ASSERT_EQ(s21_set1.empty(), std_set1.empty());
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Swap_Check_Old) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set1.begin();
  std::multiset<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Swap_Check_New) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Merge_with_Empty) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2;
  std::multiset<std::string> std_set2;
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set1.begin();
  std::multiset<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
  ASSERT_EQ(s21_set2.empty(), std_set2.empty());
}

TEST(Multiset_Modifiers, Merge_with_Full) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};

  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);

  // Проверка содержимого первого множества после слияния
  s21::multiset<std::string>::iterator s21_iter = s21_set1.begin();
  std::multiset<std::string>::iterator std_iter = std_set1.begin();
  size_t size = s21_set1.size();  // Используем s21_set1 для проверки
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers, Merge_with_Duplicate) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"hello", "aboba"};
  std::multiset<std::string> std_set2 = {"hello", "aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
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

TEST(Multiset_Lookup0, Find_Exist) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  s21::multiset<double>::iterator s21_iter = s21_set.find(2.2);
  std::multiset<double>::iterator std_iter = std_set.find(2.2);
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST(Multiset_Lookup0, Find_Non_Exist) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(s21_set.find(9.9));

  std::multiset<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(std_set.find(9.9));
}

TEST(Multiset_Lookup0, Count_0) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(9.9), std_set.count(9.9));
}

TEST(Multiset_Lookup0, Count_1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(4.4), std_set.count(4.4));
}

TEST(Multiset_Lookup0, Count_3) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(s21_set.count(5.5), std_set.count(5.5));
}

TEST(Multiset_Constructor, Default_Empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Constructor, Initializer_List) {
  s21::multiset<int> s21_mset = {2, 2, 1, 3, 4};
  std::multiset<int> std_mset = {2, 2, 1, 3, 4};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::multiset<int>::iterator s21_iter = s21_mset.begin();
  std::multiset<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor, Copy_Check_Old) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::multiset<int>::iterator s21_iter = s21_mset.begin();
  std::multiset<int>::iterator std_iter = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor, Copy_Check_New) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  size_t size = std_mset_copy.size();
  s21::multiset<int>::iterator s21_iter = s21_mset_copy.begin();
  std::multiset<int>::iterator std_iter = std_mset_copy.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Constructor, Move_Check_Old) {
  s21::multiset<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::multiset<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::multiset<int> s21_mset_move(std::move(s21_mset));
  std::multiset<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Constructor, Move_Check_New) {
  s21::multiset<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::multiset<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::multiset<int> s21_mset_move(std::move(s21_mset));
  std::multiset<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset_move.size(), std_mset_move.size());
  size_t size = std_mset_move.size();
  s21::multiset<int>::iterator s21_iter = s21_mset_move.begin();
  std::multiset<int>::iterator std_iter = std_mset_move.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Operator2, Assignment) {
  s21::multiset<float> s21_mset1 = {5.5, 4.4, 7.7};
  std::multiset<float> std_mset1 = {5.5, 4.4, 7.7};
  s21::multiset<float> s21_mset2 = {3.3, 1.1};
  std::multiset<float> std_mset2 = {3.3, 1.1};
  s21_mset1 = s21_mset2;
  std_mset1 = std_mset2;
  ASSERT_EQ(s21_mset2.size(), std_mset2.size());
  size_t size = std_mset2.size();
  s21::multiset<float>::iterator s21_iter = s21_mset2.begin();
  std::multiset<float>::iterator std_iter = std_mset2.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Capacity1, Empty_False) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity1, Empty_True) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Capacity1, Size_0) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Capacity1, Size_1) {
  s21::multiset<int> s21_mset = {5};
  std::multiset<int> std_mset = {5};
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(Multiset_Modifiers1, Clear_Full) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers1, Clear_Empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(Multiset_Modifiers1, Insert_End) {
  s21::multiset<char> s21_set = {'b', 'c', 'd'};
  std::multiset<char> std_set = {'b', 'c', 'd'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
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
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
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
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'a'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'a'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
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
  s21::multiset<char> s21_set;
  std::multiset<char> std_set;
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers1, Insert_Duplicate) {
  s21::multiset<char> s21_set = {'a'};
  std::multiset<char> std_set = {'a'};
  s21::multiset<char>::iterator s21_iter;
  std::multiset<char>::iterator std_iter;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(Multiset_Modifiers1, Erase_Leaf) {
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
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
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'e'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'e'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
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
  s21::multiset<char> s21_set = {'c', 'e', 'd', 'f'};
  std::multiset<char> std_set = {'c', 'e', 'd', 'f'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
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
  s21::multiset<char> s21_set = {'c'};
  std::multiset<char> std_set = {'c'};
  s21::multiset<char>::iterator s21_iter = s21_set.begin();
  std::multiset<char>::iterator std_iter = std_set.begin();
  s21_set.erase(s21_iter);
  std_set.erase(std_iter);
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Multiset_Modifiers2, Swap_Empty) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2;
  std::multiset<std::string> std_set2;
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  ASSERT_EQ(s21_set1.empty(), std_set1.empty());
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers2, Swap_Check_Old) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set1.begin();
  std::multiset<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers2, Swap_Check_New) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Multiset_Modifiers2, Merge_with_Empty) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2;
  std::multiset<std::string> std_set2;
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set1.begin();
  std::multiset<std::string>::iterator std_iter = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
  ASSERT_EQ(s21_set2.empty(), std_set2.empty());
}

TEST(Multiset_Modifiers2, Merge_with_Full) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
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

TEST(Multiset_Modifiers2, Merge_with_Duplicate) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"hello", "aboba"};
  std::multiset<std::string> std_set2 = {"hello", "aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iter = s21_set2.begin();
  std::multiset<std::string>::iterator std_iter = std_set2.begin();
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
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  s21::multiset<double>::iterator s21_iter = s21_set.find(2.2);
  std::multiset<double>::iterator std_iter = std_set.find(2.2);
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST(Multiset_Lookup, Find_Non_Exist) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(s21_set.find(9.9));

  std::multiset<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(std_set.find(9.9));
}

TEST(Multiset_Lookup, Contains_True) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.contains(7.7), 1);
}

TEST(Multiset_Lookup, Count_0) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(9.9), std_set.count(9.9));
}

TEST(Multiset_Lookup, Count_1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(4.4), std_set.count(4.4));
}

TEST(Multiset_Lookup, Count_2) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(5.5), std_set.count(5.5));
}

TEST(multiset_Constructor, Default_Empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(multiset_Constructor, Initializer_List) {
  s21::multiset<int> s21_mset = {2, 2, 1, 3, 4};
  std::multiset<int> std_mset = {2, 2, 1, 3, 4};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::multiset<int>::iterator s21_iterator = s21_mset.begin();
  std::multiset<int>::iterator std_iterator = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Constructor, Copy_Check_Old) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset.size(), std_mset.size());
  size_t size = std_mset.size();
  s21::multiset<int>::iterator s21_iterator = s21_mset.begin();
  std::multiset<int>::iterator std_iterator = std_mset.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Constructor, Copy_Check_New) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  s21::multiset<int> s21_mset_copy(s21_mset);
  std::multiset<int> std_mset_copy(std_mset);
  ASSERT_EQ(s21_mset_copy.size(), std_mset_copy.size());
  size_t size = std_mset_copy.size();
  s21::multiset<int>::iterator s21_iterator = s21_mset_copy.begin();
  std::multiset<int>::iterator std_iterator = std_mset_copy.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Constructor, Move_Check_Old) {
  s21::multiset<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::multiset<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::multiset<int> s21_mset_move(std::move(s21_mset));
  std::multiset<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(multiset_Constructor, Move_Check_New) {
  s21::multiset<int> s21_mset = {5, 5, 3, 4, 2, 6, 6};
  std::multiset<int> std_mset = {5, 5, 3, 4, 2, 6, 6};
  s21::multiset<int> s21_mset_move(std::move(s21_mset));
  std::multiset<int> std_mset_move(std::move(std_mset));
  ASSERT_EQ(s21_mset_move.size(), std_mset_move.size());
  size_t size = std_mset_move.size();
  s21::multiset<int>::iterator s21_iterator = s21_mset_move.begin();
  std::multiset<int>::iterator std_iterator = std_mset_move.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Operator, Assignment) {
  s21::multiset<float> s21_mset1 = {5.5, 4.4, 7.7};
  std::multiset<float> std_mset1 = {5.5, 4.4, 7.7};
  s21::multiset<float> s21_mset2 = {3.3, 1.1};
  std::multiset<float> std_mset2 = {3.3, 1.1};
  s21_mset1 = s21_mset2;
  std_mset1 = std_mset2;
  ASSERT_EQ(s21_mset2.size(), std_mset2.size());
  size_t size = std_mset2.size();
  s21::multiset<float>::iterator s21_iterator = s21_mset2.begin();
  std::multiset<float>::iterator std_iterator = std_mset2.begin();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Iterator, Begin) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(*s21_mset.begin(), *std_mset.begin());
}

TEST(multiset_Capacity, Empty_False) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(multiset_Capacity, Empty_True) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(multiset_Capacity, Size_0) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(multiset_Capacity, Size_1) {
  s21::multiset<int> s21_mset = {5};
  std::multiset<int> std_mset = {5};
  ASSERT_EQ(s21_mset.size(), std_mset.size());
}

TEST(multiset_Modifiers, Clear_Full) {
  s21::multiset<int> s21_mset = {5, 7, 3, 4, 2, 6, 8};
  std::multiset<int> std_mset = {5, 7, 3, 4, 2, 6, 8};
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(multiset_Modifiers, Clear_Empty) {
  s21::multiset<int> s21_mset;
  std::multiset<int> std_mset;
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
  s21_mset.clear();
  std_mset.clear();
  ASSERT_EQ(s21_mset.empty(), std_mset.empty());
}

TEST(multiset_Modifiers, Insert_End) {
  s21::multiset<char> s21_set = {'b', 'c', 'd'};
  std::multiset<char> std_set = {'b', 'c', 'd'};
  s21::multiset<char>::iterator s21_iterator;
  std::multiset<char>::iterator std_iterator;
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

TEST(multiset_Modifiers, Insert_Begin) {
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f'};
  s21::multiset<char>::iterator s21_iterator;
  std::multiset<char>::iterator std_iterator;
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

TEST(multiset_Modifiers, Insert_Middle) {
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'a'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'a'};
  s21::multiset<char>::iterator s21_iterator;
  std::multiset<char>::iterator std_iterator;
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

TEST(multiset_Modifiers, Insert_Empty) {
  s21::multiset<char> s21_set;
  std::multiset<char> std_set;
  s21::multiset<char>::iterator s21_iterator;
  std::multiset<char>::iterator std_iterator;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(multiset_Modifiers, Insert_Duplicate) {
  s21::multiset<char> s21_set = {'a'};
  std::multiset<char> std_set = {'a'};
  s21::multiset<char>::iterator s21_iterator;
  std::multiset<char>::iterator std_iterator;
  s21_set.insert('a');
  std_set.insert('a');
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(*s21_set.begin(), *std_set.begin());
}

TEST(multiset_Modifiers, Erase_Leaf) {
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'a', 'e'};
  s21::multiset<char>::iterator s21_iterator = s21_set.begin();
  std::multiset<char>::iterator std_iterator = std_set.begin();
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

TEST(multiset_Modifiers, Erase_Root_with_RChild) {
  s21::multiset<char> s21_set = {'b', 'c', 'd', 'f', 'e'};
  std::multiset<char> std_set = {'b', 'c', 'd', 'f', 'e'};
  s21::multiset<char>::iterator s21_iterator = s21_set.begin();
  std::multiset<char>::iterator std_iterator = std_set.begin();
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

TEST(multiset_Modifiers, Erase_with_both_children) {
  s21::multiset<char> s21_set = {'c', 'e', 'd', 'f'};
  std::multiset<char> std_set = {'c', 'e', 'd', 'f'};
  s21::multiset<char>::iterator s21_iterator = s21_set.begin();
  std::multiset<char>::iterator std_iterator = std_set.begin();
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

TEST(multiset_Modifiers, Erase_Last) {
  s21::multiset<char> s21_set = {'c'};
  std::multiset<char> std_set = {'c'};
  s21::multiset<char>::iterator s21_iterator = s21_set.begin();
  std::multiset<char>::iterator std_iterator = std_set.begin();
  s21_set.erase(s21_iterator);
  std_set.erase(std_iterator);
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(multiset_Modifiers, Swap_Empty) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2;
  std::multiset<std::string> std_set2;
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  ASSERT_EQ(s21_set1.empty(), std_set1.empty());
  s21::multiset<std::string>::iterator s21_iterator = s21_set2.begin();
  std::multiset<std::string>::iterator std_iterator = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Modifiers, Swap_Check_Old) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::multiset<std::string>::iterator s21_iterator = s21_set1.begin();
  std::multiset<std::string>::iterator std_iterator = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Modifiers, Swap_Check_New) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  s21::multiset<std::string>::iterator s21_iterator = s21_set2.begin();
  std::multiset<std::string>::iterator std_iterator = std_set2.begin();
  size_t size = std_set2.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
}

TEST(multiset_Modifiers, Merge_with_Empty) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2;
  std::multiset<std::string> std_set2;
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iterator = s21_set1.begin();
  std::multiset<std::string>::iterator std_iterator = std_set1.begin();
  size_t size = std_set1.size();
  for (size_t i = 0; i < size; i++) {
    ASSERT_EQ(*s21_iterator, *std_iterator);
    s21_iterator++;
    std_iterator++;
  }
  ASSERT_EQ(s21_set2.empty(), std_set2.empty());
}

TEST(multiset_Modifiers, Merge_with_Full) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"aboba"};
  std::multiset<std::string> std_set2 = {"aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iterator = s21_set2.begin();
  std::multiset<std::string>::iterator std_iterator = std_set2.begin();
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

TEST(multiset_Modifiers, Merge_with_Duplicate) {
  s21::multiset<std::string> s21_set1 = {"hello", "world"};
  std::multiset<std::string> std_set1 = {"hello", "world"};
  s21::multiset<std::string> s21_set2 = {"hello", "aboba"};
  std::multiset<std::string> std_set2 = {"hello", "aboba"};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  s21::multiset<std::string>::iterator s21_iterator = s21_set2.begin();
  std::multiset<std::string>::iterator std_iterator = std_set2.begin();
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

TEST(multiset_Lookup, Find_Exist) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  s21::multiset<double>::iterator s21_iterator = s21_set.find(2.2);
  std::multiset<double>::iterator std_iterator = std_set.find(2.2);
  ASSERT_EQ(*s21_iterator, *std_iterator);
}

TEST(multiset_Lookup, Find_Non_Exist) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  EXPECT_NO_THROW(s21_set.find(9.9));
  ASSERT_EQ(s21_set.find(9.9), s21_set.end());
}

TEST(multiset_Lookup, Contains_True) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.contains(7.7), 1);
}

TEST(multiset_Lookup, Contains_False) {
  s21::multiset<double> s21_set = {5.5, 4.4, 7.7, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.contains(9.9), 0);
}

TEST(multiset_Lookup, Count_0) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(9.9), std_set.count(9.9));
}

TEST(multiset_Lookup, Count_1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 6.6};
  ASSERT_EQ(s21_set.count(4.4), std_set.count(4.4));
}

TEST(multiset_Lookup, Lower_Bound_Empty) {
  s21::multiset<double> s21_set;
  ASSERT_EQ(s21_set.lower_bound(5.5), nullptr);
}

TEST(multiset_Lookup, Lower_Bound_Begin) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.lower_bound(1.1), *std_set.lower_bound(1.1));
}

TEST(multiset_Lookup, Lower_Bound_Middle1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.lower_bound(5.5), *std_set.lower_bound(5.5));
}

TEST(multiset_Lookup, Lower_Bound_Middle2) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.lower_bound(6.6), *std_set.lower_bound(6.6));
}

TEST(multiset_Lookup, Lower_Bound_End) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.lower_bound(8.8), *std_set.lower_bound(8.8));
}

TEST(multiset_Lookup, Lower_Bound_Non) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(s21_set.lower_bound(9.9), nullptr);
}

TEST(multiset_Lookup, Upper_Bound_Empty) {
  s21::multiset<double> s21_set;
  ASSERT_EQ(s21_set.upper_bound(5.5), nullptr);
}

TEST(multiset_Lookup, Upper_Bound_Begin) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.upper_bound(1.1), *std_set.upper_bound(1.1));
}

TEST(multiset_Lookup, Upper_Bound_Middle1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.upper_bound(5.5), *std_set.upper_bound(5.5));
}

TEST(multiset_Lookup, Upper_Bound_Middle2) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.upper_bound(6.6), *std_set.upper_bound(6.6));
}

TEST(multiset_Lookup, Upper_Bound_End) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(s21_set.upper_bound(8.8), nullptr);
}

TEST(multiset_Lookup, Upper_Bound_Non1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(*s21_set.upper_bound(1.05), *std_set.upper_bound(1.05));
}

TEST(multiset_Lookup, Upper_Bound_Non2) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  ASSERT_EQ(s21_set.upper_bound(9.9), nullptr);
}

TEST(multiset_Lookup, Equal_Range_Empty) {
  s21::multiset<double> s21_set;
  std::pair<typename s21::multiset<double>::iterator,
            typename s21::multiset<double>::iterator>
      s21_pair = s21_set.equal_range(1.1);
  ASSERT_EQ(s21_pair.first, nullptr);
  ASSERT_EQ(s21_pair.second, nullptr);
}

TEST(multiset_Lookup, Equal_Range_Begin) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::pair<typename s21::multiset<double>::iterator,
            typename s21::multiset<double>::iterator>
      s21_pair = s21_set.equal_range(1.1);
  std::pair<typename std::multiset<double>::iterator,
            typename std::multiset<double>::iterator>
      std_pair = std_set.equal_range(1.1);
  ASSERT_EQ(*s21_pair.first, *std_pair.first);
  ASSERT_EQ(*s21_pair.second, *std_pair.second);
}

TEST(multiset_Lookup, Equal_Range_Middle1) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::pair<typename s21::multiset<double>::iterator,
            typename s21::multiset<double>::iterator>
      s21_pair = s21_set.equal_range(5.5);
  std::pair<typename std::multiset<double>::iterator,
            typename std::multiset<double>::iterator>
      std_pair = std_set.equal_range(5.5);
  ASSERT_EQ(*s21_pair.first, *std_pair.first);
  ASSERT_EQ(*s21_pair.second, *std_pair.second);
}

TEST(multiset_Lookup, Equal_Range_Middle2) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::pair<typename s21::multiset<double>::iterator,
            typename s21::multiset<double>::iterator>
      s21_pair = s21_set.equal_range(6.6);
  std::pair<typename std::multiset<double>::iterator,
            typename std::multiset<double>::iterator>
      std_pair = std_set.equal_range(6.6);
  ASSERT_EQ(*s21_pair.first, *std_pair.first);
  ASSERT_EQ(*s21_pair.second, *std_pair.second);
}

TEST(multiset_Lookup, Equal_Range_End) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::multiset<double> std_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::pair<typename s21::multiset<double>::iterator,
            typename s21::multiset<double>::iterator>
      s21_pair = s21_set.equal_range(8.8);
  std::pair<typename std::multiset<double>::iterator,
            typename std::multiset<double>::iterator>
      std_pair = std_set.equal_range(8.8);
  ASSERT_EQ(*s21_pair.first, *std_pair.first);
  ASSERT_EQ(s21_pair.second, nullptr);
}

TEST(multiset_Lookup, Equal_Range_Non) {
  s21::multiset<double> s21_set = {5.5, 4.4, 5.5, 8.8, 1.1, 2.2, 3.3, 5.5};
  std::pair<typename s21::multiset<double>::iterator,
            typename s21::multiset<double>::iterator>
      s21_pair = s21_set.equal_range(9.9);
  ASSERT_EQ(s21_pair.first, nullptr);
  ASSERT_EQ(s21_pair.second, nullptr);
}

TEST(Multiset_Modifiers, Erase_SingleElement) {
  s21::multiset<int> s21_set = {42};
  std::multiset<int> std_set = {42};

  auto s21_iter = s21_set.begin();
  auto std_iter = std_set.begin();

  s21_set.erase(s21_iter);  // Удаляем единственный элемент
  std_set.erase(std_iter);  // Оригинал

  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_TRUE(s21_set.empty());
  ASSERT_TRUE(std_set.empty());
}

TEST(Multiset_Modifiers, Erase_TwoChildren) {
  s21::multiset<int> s21_set = {50, 30, 70, 20, 40, 60, 80};
  std::multiset<int> std_set = {50, 30, 70, 20, 40, 60, 80};

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
  s21::multiset<int> s21_set = {50, 30, 70, 60};
  std::multiset<int> std_set = {50, 30, 70, 60};

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
  s21::multiset<int> s21_set = {50, 30, 70, 20};
  std::multiset<int> std_set = {50, 30, 70, 20};

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
  s21::multiset<int> s21_set = {50, 50, 50, 30, 70};
  std::multiset<int> std_set = {50, 50, 50, 30, 70};

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
  s21::multiset<int> s21_set = {10, 20, 30};
  s21::multiset<int>::iterator null_iter = nullptr;

  s21_set.erase(null_iter);

  // Проверим, что дерево остается нетронутым после вызова erase с
  // null-итератором
  EXPECT_EQ(s21_set.size(), 3);
}

TEST(Multiset_Erase, EraseRoot) {
  s21::multiset<int> s21_set = {50, 30, 70, 20, 40, 60, 80};

  auto root_iter = s21_set.find(50);  // Корень дерева
  s21_set.erase(root_iter);           // Удаляем корень

  // Проверяем, что новый корень корректен
  EXPECT_EQ(s21_set.find(50),
            s21_set.end());  // Элемент 50 должен отсутствовать
  EXPECT_EQ(s21_set.size(), 6);  // Дерево должно уменьшиться на один элемент

  std::multiset<int> std_set = {50, 30, 70, 20, 40, 60, 80};

  auto root_iter_ = std_set.find(50);  // Корень дерева
  std_set.erase(root_iter_);           // Удаляем корень

  // Проверяем, что новый корень корректен
  EXPECT_EQ(std_set.find(50),
            std_set.end());  // Элемент 50 должен отсутствовать
  EXPECT_EQ(std_set.size(), 6);  // Дерево должно уменьшиться на один элемент
}

// Тест 1: Вставка в пустое множество
TEST(MultisetInsertTest, InsertIntoEmpty) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  s21_ms.insert(5);
  std_ms.insert(5);

  EXPECT_EQ(s21_ms.size(), std_ms.size());  // Ожидаем, что размер будет
  EXPECT_EQ(s21_ms.count(5), std_ms.count(5));  // Ожидаем, что
}

// Тест 2: Вставка дубликатов
TEST(MultisetInsertTest, InsertDuplicates) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  s21_ms.insert(5);
  s21_ms.insert(5);
  std_ms.insert(5);
  std_ms.insert(5);

  EXPECT_EQ(s21_ms.size(), std_ms.size());  // Размеры должны совпадать
  EXPECT_EQ(s21_ms.count(5), std_ms.count(5));  // Количество дубликатов должно
}

// Тест 3: Вставка уникальных значений
TEST(MultisetInsertTest, InsertUniqueValues) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  s21_ms.insert(1);
  s21_ms.insert(2);
  s21_ms.insert(3);
  std_ms.insert(1);
  std_ms.insert(2);
  std_ms.insert(3);

  EXPECT_EQ(s21_ms.size(), std_ms.size());  // Размеры должны совпадать
  EXPECT_EQ(s21_ms.count(1), std_ms.count(1));
  EXPECT_EQ(s21_ms.count(2), std_ms.count(2));
  EXPECT_EQ(s21_ms.count(3), std_ms.count(3));
}

// Тест 4: Вставка на границах (минимальные и максимальные значения)
TEST(MultisetInsertTest, InsertMinMaxValues) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  s21_ms.insert(INT_MIN);
  s21_ms.insert(INT_MAX);
  std_ms.insert(INT_MIN);
  std_ms.insert(INT_MAX);

  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.count(INT_MIN), std_ms.count(INT_MIN));
  EXPECT_EQ(s21_ms.count(INT_MAX), std_ms.count(INT_MAX));
}

// Тест 5: Множественная вставка с дубликатами
TEST(MultisetInsertTest, InsertMultipleWithDuplicates) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  for (int i = 0; i < 100; ++i) {
    s21_ms.insert(i % 10);  // Вставляем значения с повторениями
    std_ms.insert(i % 10);
  }

  EXPECT_EQ(s21_ms.size(), std_ms.size());  // Размеры должны совпадать

  // Проверяем количество каждого значения
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_ms.count(i), std_ms.count(i));
  }
}

// Тест 6: Вставка большого количества элементов
TEST(MultisetInsertTest, InsertLargeAmountOfElements) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  for (int i = 0; i < 1000; ++i) {
    s21_ms.insert(i);
    std_ms.insert(i);
  }

  EXPECT_EQ(s21_ms.size(), std_ms.size());
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(s21_ms.count(i), std_ms.count(i));
  }
}

// Тест 7: Вставка отрицательных значений
TEST(MultisetInsertTest, InsertNegativeValues) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

  s21_ms.insert(-10);
  s21_ms.insert(-5);
  s21_ms.insert(-1);
  std_ms.insert(-10);
  std_ms.insert(-5);
  std_ms.insert(-1);

  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.count(-10), std_ms.count(-10));
  EXPECT_EQ(s21_ms.count(-5), std_ms.count(-5));
  EXPECT_EQ(s21_ms.count(-1), std_ms.count(-1));
}

TEST(MultisetTest, EraseSingleElement) {
  s21::multiset<int> my_set{5};
  std::multiset<int> std_set{5};

  my_set.erase(my_set.begin());
  std_set.erase(std_set.begin());

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(MultisetTest, EraseNodeWithTwoChildren) {
  s21::multiset<int> my_set{10, 5, 15, 3, 7, 13, 17};
  std::multiset<int> std_set{10, 5, 15, 3, 7, 13, 17};

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
  s21::multiset<int> my_set{1, 2, 3};
  std::multiset<int> std_set{1, 2, 3};

  my_set.erase(--my_set.end());  // Удаляем последний элемент "3"
  std_set.erase(--std_set.end());

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(*my_set.begin(), *std_set.begin());
}

TEST(MultisetTest, EraseNodeWithOneChild) {
  s21::multiset<int> my_set{20, 10, 30, 25};
  std::multiset<int> std_set{20, 10, 30, 25};

  auto it_my_set = my_set.find(30);
  auto it_std_set = std_set.find(30);
  my_set.erase(it_my_set);  // Удаляем элемент "30", имеющий одного ребенка "25"
  std_set.erase(it_std_set);

  EXPECT_EQ(my_set.size(), std_set.size());
  EXPECT_EQ(*(--my_set.end()), *(--std_set.end()));
}

TEST(MultisetEraseTest, EraseRoot) {
  // Создаем s21::multiset и std::multiset для сравнения
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  // Создаем s21::multiset и std::multiset для сравнения
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_multiset = {10};
  std::multiset<int> std_multiset = {10};

  auto s21_it = s21_multiset.begin();
  auto std_it = std_multiset.begin();

  s21_multiset.erase(s21_it);
  std_multiset.erase(std_it);

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(MultisetIteratorTest, EraseWithChild_4) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_multiset = {20, 10, 30, 5, 15, 25, 35, 3};
  std::multiset<int> std_multiset = {20, 10, 30, 5, 15, 25, 35, 3};

  // Удалим узел 10, при этом у него должен быть брат (узел 30), который красный
  auto s21_it = s21_multiset.find(10);
  auto std_it = std_multiset.find(10);

  ASSERT_NE(s21_it, s21_multiset.end());
  ASSERT_NE(std_it, std_multiset.end());

  // Удаление элемента
  s21_multiset.erase(s21_it);
  std_multiset.erase(std_it);

  // Проверка: размер после удаления должен быть одинаков
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(MultisetIteratorTest, EraseWithChild_5) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;

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
  s21::multiset<int> ms;
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
  s21::multiset<int> ms{1, 2, 3};
  auto results = ms.insert_many(3, 4, 5);

  EXPECT_EQ(
      ms.size(),
      6);  // Проверка, что размер увеличился на 2, так как 3 уже существует

  // Проверка значений и успешности вставки
  EXPECT_TRUE(results[0].second);  // 3 уже существует, не должно быть вновь
                                   // вставлено (это для set здесь false)
  EXPECT_TRUE(results[1].second);  // 4 — новое значение
  EXPECT_TRUE(results[2].second);  // 5 — новое значение
}

// Тест вставки одного значения для проверки корректности работы с одним
// аргументом
TEST(MultisetTest, InsertMany_SingleValue) {
  s21::multiset<int> ms;
  auto results = ms.insert_many(42);

  EXPECT_EQ(ms.size(), 1);  // Размер множества должен быть 1
  EXPECT_EQ(*results[0].first, 42);  // Вставленное значение — 42
  EXPECT_TRUE(results[0].second);  // Вставка нового элемента
}

TEST(InsertManyTest, BasicFunctionality) {
  s21::multiset<int> s;
  auto results = s.insert_many(3, 1, 4, 1, 5);

  EXPECT_EQ(s.size(), 5);  // Проверяем размер multiset
  EXPECT_EQ(*results[0].first, 3);
  EXPECT_EQ(*results[1].first, 1);
  EXPECT_TRUE(results[1].second);  // Второй элемент вставлен с дубликатом
}

TEST(InsertManyTest, DifferentTypes) {
  s21::multiset<std::string> s;
  s.insert_many("hello", "world", "hello");
  EXPECT_EQ(s.size(), 3);
}

TEST(InsertManyTest, EmptyMultiset) {
  s21::multiset<int> s;
  auto results = s.insert_many(42);
  EXPECT_TRUE(results[0].second);
}

// Тест пустой вставки
TEST(MultisetTest, InsertMany_Empty) {
  s21::multiset<int> ms;
  auto results = ms.insert_many();  // Вставка пустого списка аргументов

  EXPECT_TRUE(results.empty());  // Результаты должны быть пустыми
  EXPECT_EQ(ms.size(), 0);  // Размер множества должен быть 0
}

TEST(Multiset_Capacity, Max_Size) {
  s21::multiset<int> s21_set = {1, 2, 3};
  std::multiset<int> std_set = {1, 2, 3};
  ASSERT_EQ(s21_set.max_size(), std_set.max_size());
}

// array_tests

TEST(Array_Constructor, Default_Empty) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
}

TEST(Array_Constructor, Initializer_List_OK1) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Constructor, Initializer_List_OK2) {
  s21::array<int, 3> s21_array = {1, 2};
  std::array<int, 3> std_array = {1, 2};
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Constructor, Initializer_List_ERROR) {
  s21::array<int, 3> s21_array;
  EXPECT_THROW((s21_array = {1, 2, 3, 4}), std::length_error);
}

TEST(Array_Constructor, Copy_Check_Old) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array_copy(s21_array);
  std::array<int, 3> std_array_copy(std_array);
  ASSERT_EQ(s21_array_copy.empty(), std_array_copy.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Constructor, Copy_Check_New) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array_copy(s21_array);
  std::array<int, 3> std_array_copy(std_array);
  ASSERT_EQ(s21_array_copy.empty(), std_array_copy.empty());
  ASSERT_EQ(s21_array_copy.size(), std_array_copy.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array_copy[i], std_array_copy[i]);
  }
}

TEST(Array_Constructor, Move_Check_Old) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array_move(std::move(s21_array));
  std::array<int, 3> std_array_move(std::move(std_array));
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array_move.empty(), std_array_move.empty());
}

TEST(Array_Constructor, Move_Check_New) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array_move(std::move(s21_array));
  std::array<int, 3> std_array_move(std::move(std_array));
  ASSERT_EQ(s21_array_move.empty(), std_array_move.empty());
  ASSERT_EQ(s21_array_move.size(), std_array_move.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array_move[i], std_array_move[i]);
  }
}

TEST(Array_Operator, Assignment_Check_Old) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array2 = s21_array;
  std::array<int, 3> std_array2 = std_array;
  ASSERT_EQ(s21_array2.empty(), std_array2.empty());
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Operator, Assignment_Check_New) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array2 = s21_array;
  std::array<int, 3> std_array2 = std_array;
  ASSERT_EQ(s21_array2.empty(), std_array2.empty());
  ASSERT_EQ(s21_array2.size(), std_array2.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array2[i], std_array2[i]);
  }
}

TEST(Array_Element_access, At_OK) {
  s21::array<char, 5> s21_array = {'a', 'b', 'c', 'd', 'e'};
  std::array<char, 5> std_array = {'a', 'b', 'c', 'd', 'e'};
  for (size_t i = 0; i < 5; i++) {
    ASSERT_EQ(s21_array.at(i), std_array.at(i));
  }
}

TEST(Array_Element_access, At_ERROR) {
  s21::array<char, 5> s21_array = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_THROW(s21_array.at(6), std::out_of_range);
}

TEST(Array_Element_access, Brackets_OK) {
  s21::array<char, 5> s21_array = {'a', 'b', 'c', 'd', 'e'};
  std::array<char, 5> std_array = {'a', 'b', 'c', 'd', 'e'};
  for (size_t i = 0; i < 5; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Element_access, Brackets_ERROR) {
  s21::array<char, 5> s21_array = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_THROW(s21_array[6], std::out_of_range);
}

TEST(Array_Element_access, Front_Full) {
  s21::array<std::string, 2> s21_array = {"hello", "world"};
  std::array<std::string, 2> std_array = {"hello", "world"};
  ASSERT_EQ(s21_array.front(), std_array.front());
}

TEST(Array_Element_access, Front_Empty) {
  s21::array<std::string, 2> s21_array;
  std::array<std::string, 2> std_array;
  ASSERT_EQ(s21_array.front(), std_array.front());
}

TEST(Array_Element_access, Back_Full) {
  s21::array<std::string, 2> s21_array = {"hello", "world"};
  std::array<std::string, 2> std_array = {"hello", "world"};
  ASSERT_EQ(s21_array.back(), std_array.back());
}

TEST(Array_Element_access, Back_Empty) {
  s21::array<std::string, 2> s21_array;
  std::array<std::string, 2> std_array;
  ASSERT_EQ(s21_array.back(), std_array.back());
}

TEST(Array_Iterators, Begin_Full) {
  s21::array<std::string, 2> s21_array = {"hello", "world"};
  std::array<std::string, 2> std_array = {"hello", "world"};
  ASSERT_EQ(*s21_array.begin(), *std_array.begin());
}

TEST(Array_Iterators, Begin_Empty) {
  s21::array<std::string, 2> s21_array;
  std::array<std::string, 2> std_array;
  ASSERT_EQ(*s21_array.begin(), *std_array.begin());
}

TEST(Array_Iterators, End_Full) {
  s21::array<int, 2> s21_array = {1, 2};
  std::array<int, 2> std_array = {1, 2};
  s21::array<int, 2>::iterator s21_iter = s21_array.end();
  std::array<int, 2>::iterator std_iter = std_array.end();
  s21_iter--;
  std_iter--;
  ASSERT_EQ(*s21_iter, *std_iter);
}

TEST(Array_Iterators, End_Empty) {
  s21::array<std::string, 2> s21_array;
  EXPECT_NO_THROW(*s21_array.end());
}

TEST(Array_Capacity, Empty_True) {
  s21::array<double, 1> s21_array;
  std::array<double, 1> std_array;
  ASSERT_EQ(s21_array.empty(), std_array.empty());
}

TEST(Array_Capacity, Empty_False) {
  s21::array<double, 1> s21_array = {1.1};
  std::array<double, 1> std_array = {1.1};
  ASSERT_EQ(s21_array.empty(), std_array.empty());
}

TEST(Array_Capacity, Size_0) {
  s21::array<double, 1> s21_array;
  std::array<double, 1> std_array;
  ASSERT_EQ(s21_array.size(), std_array.size());
}

TEST(Array_Capacity, Size_1) {
  s21::array<double, 1> s21_array = {1.1};
  std::array<double, 1> std_array = {1.1};
  ASSERT_EQ(s21_array.size(), std_array.size());
}

TEST(Array_Modifiers, Swap_Full) {
  s21::array<double, 2> s21_array = {1.1, 4.4};
  std::array<double, 2> std_array = {1.1, 4.4};
  s21::array<double, 2> s21_array2 = {2.2, 3.3};
  std::array<double, 2> std_array2 = {2.2, 3.3};
  s21_array.swap(s21_array2);
  std_array.swap(std_array2);
  for (size_t i = 0; i < 2; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
    ASSERT_EQ(s21_array2[i], std_array2[i]);
  }
}

TEST(Array_Modifiers, Swap_Empty) {
  s21::array<double, 2> s21_array = {1.1, 2.2};
  std::array<double, 2> std_array = {1.1, 2.2};
  s21::array<double, 2> s21_array2;
  std::array<double, 2> std_array2;
  s21_array.swap(s21_array2);
  std_array.swap(std_array2);
  for (size_t i = 0; i < 2; i++) {
    ASSERT_EQ(s21_array2[i], std_array2[i]);
  }
}

TEST(Array_Modifiers, Fill_Full) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21_array.fill(5);
  std_array.fill(5);
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Modifiers, Fill_Empty) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  s21_array.fill(5);
  std_array.fill(5);
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Operator, Assignment_NewTest) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array2;
  std::array<int, 3> std_array2;
  s21_array2 = s21_array;
  std_array2 = std_array;
  ASSERT_EQ(s21_array2.empty(), std_array2.empty());
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Element_access, Data) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3>::iterator s21_iter;
  std::array<int, 3>::iterator std_iter;
  s21_iter = s21_array.data();
  std_iter = std_array.data();
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(*s21_iter, *std_iter);
    s21_iter++;
    std_iter++;
  }
}

TEST(Array_Operator, Assignment_Move) {
  s21::array<int, 3> s21_array;  // Пустое множество
  s21::array<int, 3> s21_array2 = {1, 2, 3};  // Множество с тремя элементами

  // Перемещение в пустое множество
  s21_array = std::move(s21_array2);
  ASSERT_EQ(s21_array[0], 1);
  ASSERT_EQ(s21_array[1], 2);
  ASSERT_EQ(s21_array[2], 3);
}

TEST(Array_Operator, Assignment_NewTest2) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  s21::array<int, 3> s21_array2;
  std::array<int, 3> std_array2;
  s21_array2 = s21_array;
  std_array2 = std_array;
  ASSERT_EQ(s21_array2.empty(), std_array2.empty());
  ASSERT_EQ(s21_array.empty(), std_array.empty());
}

TEST(Array_Operator, Assignment_NewTest3) {
  s21::array<int, 3> s21_array;
  std::array<int, 3> std_array;
  s21::array<int, 3> s21_array2 = {1, 2, 3};
  std::array<int, 3> std_array2 = {1, 2, 3};
  s21_array2 = s21_array;
  std_array2 = std_array;
  ASSERT_EQ(s21_array2.empty(), std_array2.empty());
  ASSERT_EQ(s21_array.empty(), std_array.empty());
}

TEST(Array_Operator, Assignment_NewTest4) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  std::array<int, 3> std_array = {1, 2, 3};
  s21::array<int, 3> s21_array2 = {4, 5, 6};
  std::array<int, 3> std_array2 = {4, 5, 6};
  s21_array2 = s21_array;
  std_array2 = std_array;
  ASSERT_EQ(s21_array2.empty(), std_array2.empty());
  ASSERT_EQ(s21_array.empty(), std_array.empty());
  ASSERT_EQ(s21_array.size(), std_array.size());
  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(s21_array[i], std_array[i]);
  }
}

TEST(Array_Iterator, Equal_True) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3>::iterator s21_iter;
  s21::array<int, 3>::iterator s21_iter2;
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3>::iterator std_iter;
  std::array<int, 3>::iterator std_iter2;
  s21_iter = s21_array.data();
  s21_iter2 = s21_array.data();
  std_iter = std_array.data();
  std_iter2 = std_array.data();
  EXPECT_TRUE(s21_iter == s21_iter2);
  EXPECT_TRUE(std_iter == std_iter2);
}

TEST(Array_Iterator, Equal_False) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3>::iterator s21_iter;
  s21::array<int, 3>::iterator s21_iter2;
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3>::iterator std_iter;
  std::array<int, 3>::iterator std_iter2;
  s21_iter = s21_array.data();
  s21_iter2 = s21_array.data();
  std_iter = std_array.data();
  std_iter2 = std_array.data();
  s21_iter2++;
  std_iter2++;
  EXPECT_FALSE(s21_iter == s21_iter2);
  EXPECT_FALSE(std_iter == std_iter2);
}

TEST(Array_Iterator, NonEqual_True) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3>::iterator s21_iter;
  s21::array<int, 3>::iterator s21_iter2;
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3>::iterator std_iter;
  std::array<int, 3>::iterator std_iter2;
  s21_iter = s21_array.data();
  s21_iter2 = s21_array.data();
  std_iter = std_array.data();
  std_iter2 = std_array.data();
  s21_iter2++;
  std_iter2++;
  EXPECT_TRUE(s21_iter != s21_iter2);
  EXPECT_TRUE(std_iter != std_iter2);
}

TEST(Array_Iterator, NonEqual_False) {
  s21::array<int, 3> s21_array = {1, 2, 3};
  s21::array<int, 3>::iterator s21_iter;
  s21::array<int, 3>::iterator s21_iter2;
  std::array<int, 3> std_array = {1, 2, 3};
  std::array<int, 3>::iterator std_iter;
  std::array<int, 3>::iterator std_iter2;
  s21_iter = s21_array.data();
  s21_iter2 = s21_array.data();
  std_iter = std_array.data();
  std_iter2 = std_array.data();
  EXPECT_FALSE(s21_iter != s21_iter2);
  EXPECT_FALSE(std_iter != std_iter2);
}