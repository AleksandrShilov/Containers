#include <gtest/gtest.h>

#include <iomanip>
#include <list>

#include "my_list.h"

using namespace std;

// ************************ Базовый конструктор ************************
TEST(Constructors, Default) {
  my::List<int> list_int;
  ASSERT_TRUE(list_int.Empty());
  ASSERT_EQ(list_int.Size(), 0);

  my::List<size_t> list_size_t;
  ASSERT_TRUE(list_size_t.Empty());
  ASSERT_EQ(list_size_t.Size(), 0);

  my::List<double> list_double;
  ASSERT_TRUE(list_double.Empty());
  ASSERT_EQ(list_double.Size(), 0);

  my::List<char> list_char;
  ASSERT_TRUE(list_char.Empty());
  ASSERT_EQ(list_char.Size(), 0);

  my::List<std::string> my_list_string;
  ASSERT_TRUE(my_list_string.Empty());
  ASSERT_EQ(my_list_string.Size(), 0);
}

// ************************ Конструктор size ************************
TEST(ConstructorsParam, Parameterized) {
  my::List<int> list_int(3);
  ASSERT_FALSE(list_int.Empty());
  ASSERT_EQ(list_int.Size(), 3);

  my::List<size_t> list_size_t(100);
  ASSERT_FALSE(list_size_t.Empty());
  ASSERT_EQ(list_size_t.Size(), 100);

  my::List<double> list_double(78);
  ASSERT_FALSE(list_double.Empty());
  ASSERT_EQ(list_double.Size(), 78);

  my::List<char> list_char(0);
  ASSERT_TRUE(list_char.Empty());
  ASSERT_EQ(list_char.Size(), 0);

  my::List<std::string> list_string(205);
  ASSERT_FALSE(list_string.Empty());
  ASSERT_EQ(list_string.Size(), 205);
}

// ************************ Конструткор инициализации ********************
TEST(Constructors, Initializer) {
  my::List<int> list_int{777, -3, 1, 2, 2};
  ASSERT_EQ(list_int.Size(), 5);
  ASSERT_EQ(list_int.Front(), 777);
  ASSERT_EQ(list_int.Back(), 2);

  my::List<std::string> list_string{"Hello", "I'm", "Vikus"};
  ASSERT_EQ(list_string.Size(), 3);
  ASSERT_EQ(list_string.Front(), "Hello");
  ASSERT_EQ(list_string.Back(), "Vikus");
}

// ******************* Конструткор копирвоания *****************
TEST(Constructors, Copy) {
  my::List<int> list_int{777, -3, 1, 2, 5};
  my::List<int> list_int2(list_int);
  ASSERT_EQ(list_int.Size(), 5);
  ASSERT_EQ(list_int.Front(), 777);
  ASSERT_EQ(list_int.Back(), 5);
  ASSERT_EQ(list_int2.Size(), 5);
  ASSERT_EQ(list_int2.Front(), 777);
  ASSERT_EQ(list_int2.Back(), 5);

  my::List<std::string> list_string{"am", "I", "Ivan"};
  my::List<std::string> list_string2(list_string);
  ASSERT_EQ(list_string.Size(), 3);
  ASSERT_EQ(list_string.Front(), "am");
  ASSERT_EQ(list_string.Back(), "Ivan");
  auto it = list_string2.Begin();
  auto it_End = list_string2.End();
  --it_End;
  ASSERT_EQ(*it, "am");
  ASSERT_EQ(*it_End, "Ivan");
}

// ********************** Конструткор переноса ********************

TEST(Constructors, Move) {
  my::List<int> list_int{777, -3, 1, 2, 5};
  my::List<int> list_int2(std::move(list_int));
  ASSERT_EQ(list_int.Size(), 0);
  ASSERT_EQ(list_int2.Size(), 5);
  ASSERT_EQ(list_int2.Front(), 777);
  ASSERT_EQ(list_int2.Back(), 5);

  my::List<std::string> list_string{"am", "I", "Ivan"};
  my::List<std::string> list_string2(std::move(list_string));
  ASSERT_EQ(list_string.Size(), 0);
  ASSERT_EQ(list_string2.Size(), 3);
  auto it = list_string2.Begin();
  auto it_End = list_string2.End();
  --it_End;
  ASSERT_EQ(*it, "am");
  ASSERT_EQ(*it_End, "Ivan");
}

// ************** Clear **************
TEST(ListModifiers, Clear) {
  my::List<int> my_list_int{5, 1, 2, 3, 7};
  std::list<int> list_int{5, 1, 2, 3, 7};
  my_list_int.Clear();
  list_int.clear();
  ASSERT_EQ(my_list_int.Size(), list_int.size());
  ASSERT_TRUE(my_list_int.Empty());
}

// ************** Insert **************
TEST(ListModifiers, Insert) {
  my::List<int> my_list_int{5, 1, 2, 3, 7};
  std::list<int> list_int{5, 1, 2, 3, 7};
  auto it_my = my_list_int.Begin();
  auto it_orig = list_int.begin();
  auto it_my_insert = my_list_int.Insert(it_my, 77);
  auto it_orig_insert = list_int.insert(it_orig, 77);
  ASSERT_EQ(*it_my_insert, *it_orig_insert);
  ++it_my;
  ++it_orig;
  auto it_my_insert2 = my_list_int.Insert(it_my, 171);
  auto it_orig_insert2 = list_int.insert(it_orig, 171);
  ASSERT_EQ(*it_my_insert2, *it_orig_insert2);
}

// ************** Erase **************
TEST(ListModifiers, Erase) {
  my::List<std::string> my_list_string{"am", "I", "Ivan"};
  std::list<std::string> list_string{"am", "I", "Ivan"};
  auto it_my = my_list_string.Begin();
  auto it_orig = list_string.begin();
  ++it_my;
  ++it_orig;
  my_list_string.Erase(it_my);
  list_string.erase(it_orig);
  auto it_my_after_erase = my_list_string.Begin();
  auto it_orig_after_erase = list_string.begin();
  ++it_my_after_erase;
  ++it_orig_after_erase;
  ASSERT_EQ(*it_my_after_erase, *it_orig_after_erase);

  my_list_string.Erase(it_my_after_erase);
  list_string.erase(it_orig_after_erase);
  auto it_my_after_erase2 = my_list_string.Begin();
  auto it_orig_after_erase2 = list_string.begin();
  ASSERT_EQ(*it_my_after_erase2, *it_orig_after_erase2);

  my_list_string.Erase(it_my_after_erase2);
  list_string.erase(it_orig_after_erase2);
  ASSERT_TRUE(my_list_string.Empty());
  ASSERT_TRUE(list_string.empty());
}

TEST(ListModifiers, Erase2) {
  my::List<std::string> my_list_string;
  auto it_my = my_list_string.Begin();
  EXPECT_THROW(my_list_string.Erase(it_my), invalid_argument);
}

TEST(ListModifiers, Erase3) {
  my::List<std::string> my_list_string{"am", "I", "Ivan"};
  auto it_my = my_list_string.Begin();
  ++it_my;
  ++it_my;
  ++it_my;
  my_list_string.Erase(it_my);
  auto it_my_after_erase = my_list_string.Begin();
  ++it_my_after_erase;
  ASSERT_EQ(*it_my_after_erase, "I");
}

// ************** SortAndMerge **************
TEST(List_Modifiers, SortAndMerge) {
  my::List<double> my_list_double{0.5, -3.9, 11.5, 2.3};
  my::List<double> my_list_double2{-0.5, 777, 25.9, 33.1};
  std::list<double> list_double{0.5, -3.9, 11.5, 2.3};
  std::list<double> list_double2{-0.5, 777, 25.9, 33.1};
  my_list_double.Sort();
  my_list_double2.Sort();
  list_double.sort();
  list_double2.sort();
  ASSERT_DOUBLE_EQ(my_list_double.Front(), list_double.front());
  ASSERT_DOUBLE_EQ(my_list_double.Back(), list_double.back());
  ASSERT_DOUBLE_EQ(my_list_double2.Front(), list_double2.front());
  ASSERT_DOUBLE_EQ(my_list_double2.Back(), list_double2.back());

  my_list_double.Merge(my_list_double2);
  list_double.merge(list_double2);
  ASSERT_DOUBLE_EQ(my_list_double.Front(), list_double.front());
  ASSERT_DOUBLE_EQ(my_list_double.Back(), list_double.back());
  ASSERT_TRUE(my_list_double2.Empty());
  ASSERT_TRUE(list_double2.empty());
}

// ************** Splice **************
TEST(ListModifiers, Splice) {
  my::List<char> my_list_char{'a', 'c', 'b'};
  my::List<char> my_list_char2{'1', '!', '4', '5'};
  std::list<char> list_char{'a', 'c', 'b'};
  std::list<char> list_char2{'1', '!', '4', '5'};
  auto it_my = my_list_char.End();
  --it_my;
  auto it_orig = list_char.end();
  --it_orig;
  my_list_char.Splice(it_my, my_list_char2);
  list_char.splice(it_orig, list_char2);
  ASSERT_EQ(my_list_char.Front(), list_char.front());
  ASSERT_EQ(my_list_char.Back(), list_char.back());
  ASSERT_TRUE(my_list_char2.Empty());
  ASSERT_TRUE(list_char2.empty());
}

// ************** Reverse **************
TEST(ListModifiers, Reverse) {
  my::List<double> my_list_double{0.5, -3.9, 11.5, 2.3};
  std::list<double> list_double{0.5, -3.9, 11.5, 2.3};
  my_list_double.Reverse();
  list_double.reverse();
  ASSERT_DOUBLE_EQ(my_list_double.Front(), list_double.front());
  ASSERT_DOUBLE_EQ(my_list_double.Back(), list_double.back());

  my::List<std::string> my_list_string{"am", "I", "Ivan"};
  std::list<std::string> list_string{"am", "I am", "Ivan"};
  my_list_string.Reverse();
  list_string.reverse();
  ASSERT_EQ(my_list_string.Front(), list_string.front());
  ASSERT_EQ(my_list_string.Back(), list_string.back());
}

// ************** Unique **************
TEST(ListModifiers, Unique) {
  my::List<int> my_list_int{1, 2, 2, 3, 3, 3, 8, 9, 9, 0, 0, 0};
  std::list<int> list_int{1, 2, 2, 3, 3, 3, 8, 9, 9, 0, 0, 0};
  my_list_int.Unique();
  list_int.unique();
  ASSERT_EQ(my_list_int.Size(), list_int.size());
  auto it_my = my_list_int.Begin();
  auto it_orig = list_int.begin();
  ++it_my;
  ++it_my;
  ++it_orig;
  ++it_orig;
  ASSERT_EQ(*it_my, *it_orig);
}

// ************** Pop **************
TEST(ListModifiers, Pop) {
  my::List<int> my_list_int;
  my_list_int.PushBack(1);
  my_list_int.PushBack(2);
  my_list_int.PushBack(3);
  my_list_int.PopBack();
  ASSERT_EQ(my_list_int.Size(), 2);
  ASSERT_EQ(my_list_int.Back(), 2);
}

// ************** Operator1 **************
TEST(ListOverload, Operator1) {
  my::List<int> my_list_int{777, -3, 1, 2, 5};
  my::List<int> my_list_int2;
  my_list_int2 = my_list_int;
  ASSERT_EQ(my_list_int.Size(), 5);
  ASSERT_EQ(my_list_int.Front(), 777);
  ASSERT_EQ(my_list_int.Back(), 5);
  ASSERT_EQ(my_list_int2.Size(), 5);
  ASSERT_EQ(my_list_int2.Front(), 777);
  ASSERT_EQ(my_list_int2.Back(), 5);

  my::List<double> my_list_double{0.5, -3.9, 1.5, 2.3};
  my::List<double> my_list_double2{100.1, 100.2};
  my_list_double2 = my_list_double;
  ASSERT_EQ(my_list_double.Size(), 4);
  ASSERT_DOUBLE_EQ(my_list_double.Front(), 0.5);
  ASSERT_DOUBLE_EQ(my_list_double.Back(), 2.3);
  ASSERT_EQ(my_list_double2.Size(), 4);
  ASSERT_DOUBLE_EQ(my_list_double2.Front(), 0.5);
  ASSERT_DOUBLE_EQ(my_list_double2.Back(), 2.3);

  my::List<std::string> my_list_string{"am", "I", "Ivan"};
  my::List<std::string> my_list_string2{"Aboba", "to", "and", "Ababo"};
  my_list_string2 = std::move(my_list_string);
  ASSERT_EQ(my_list_string.Size(), 0);
  ASSERT_EQ(my_list_string2.Size(), 3);
  auto it = my_list_string2.Begin();
  auto it_End = my_list_string2.End();
  --it_End;
  ASSERT_EQ(*it, "am");
  ASSERT_EQ(*it_End, "Ivan");
}

// ************** MaxSize **************
TEST(ListModifiers, MaxSize) {
  my::List<int> my_list_int;
  ASSERT_EQ(my_list_int.MaxSize(), 384307168202282325);
}

// ************** Iterator **************
TEST(ListModifiers, Iterator) {
  my::List<int> my_list_int{1, 2, 3};
  my::List<int> list_int{1, 2, 1, 3, 4};
  my::List<int>::iterator it;
  my::List<int>::iterator it2;
  it = my_list_int.Begin();
  it2 = list_int.Begin();
  ASSERT_EQ(false, it == it2);
  ASSERT_EQ(*it, *it2);
}

// ************** Swap **************
TEST(ListModifiers, Swap1) {
  my::List<int> my_list_int{0, 0, 0};
  my::List<int> list_int{1, 2, 1, 3, 4};
  my_list_int.Swap(list_int);
  ASSERT_EQ(my_list_int.Size(), 5);
  ASSERT_EQ(list_int.Size(), 3);
  ASSERT_EQ(*(my_list_int.Begin()), 1);
  ASSERT_EQ(*(list_int.Begin()), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}