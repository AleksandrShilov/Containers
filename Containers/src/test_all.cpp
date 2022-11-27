#include <gtest/gtest.h>

#include <cmath>
#include <iomanip>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "my_containers.h"

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

// ************* MAP *****************

TEST(Test_1, init_and_size_map) {
  my::Map<int, int> mp;
  std::map<int, int> mp_eq;
  ASSERT_EQ(mp.size(), mp_eq.size());
}

TEST(Test_2, empty_map) {
  my::Map<std::string, double> mp;
  std::map<std::string, double> mp_eq;
  ASSERT_TRUE(mp.empty());
  ASSERT_TRUE(mp.empty());
}

TEST(Test_3, init_and_size_map) {
  my::Map<int, int> mp;
  mp.insert({4, 6});
  mp.insert({1, 9});
  ASSERT_EQ(mp.at(4), 6);
  ASSERT_EQ(mp.at(1), 9);
}

TEST(Test_4, init_and_size_map2) {
  my::Map<int, int> mp;
  mp.insert(4, 6);
  mp.insert(1, 9);
  ASSERT_EQ(mp.at(4), 6);
  ASSERT_EQ(mp.at(1), 9);
}

TEST(Test_5, insert_map) {
  my::Map<int, int> mp;
  mp.insert(4, 6);
  mp.insert_or_assign(4, 9);
  mp.insert_or_assign(5, 8);
  mp.insert(5, 9);
  ASSERT_EQ(mp.at(4), 9);
  ASSERT_EQ(mp.at(5), 8);
}

TEST(Test_6, erase_map) {
  my::Map<int, int> mp;
  mp.insert(4, 6);
  mp.insert_or_assign(4, 9);
  mp.insert_or_assign(5, 8);
  mp.insert(5, 9);
  my::Map<int, int>::iterator iter = mp.begin();
  ++iter;
  mp.erase(iter);
  ASSERT_EQ(mp.size(), 1);
}

TEST(Test_7, erase_map2) {
  my::Map<int, int> mp;
  mp.insert(7, 6);
  mp.insert(3, 9);
  mp.insert(9, 9);
  mp.insert(2, 9);
  mp.insert(5, 9);
  mp.insert(8, 9);
  mp.insert(1, 9);
  mp.insert(4, 9);
  mp.insert(6, 9);
  my::Map<int, int>::iterator iter = mp.begin();
  ++iter;
  mp.erase(iter);
  ASSERT_EQ(mp.size(), 8);
  ASSERT_EQ(mp.at(3), 9);
}

TEST(Test_8, clear_map) {
  my::Map<int, int> mp;
  mp.insert(4, 6);
  mp.insert(1, 9);
  mp.clear();
  ASSERT_EQ(mp.size(), 0);
}

TEST(Test_9, my_erase_tree) {
  Tree<int, int> mp;
  mp.Insert(7, 6);
  mp.Insert(3, 9);
  mp.Insert(9, 9);
  mp.Insert(2, 9);
  mp.Insert(5, 9);
  mp.Insert(8, 9);
  mp.Insert(1, 9);
  mp.Insert(4, 9);
  mp.Insert(6, 9);
  mp.Erase({1, 9});
  ASSERT_EQ(mp.Size(), 8);
}

TEST(Test_10, init_and_size_set) {
  my::Set<int> st;
  std::set<int> st_eq;
  ASSERT_EQ(st.size(), st_eq.size());
}

TEST(Test_11, empty_set) {
  my::Set<std::string> st;
  std::set<std::string> st_eq;
  ASSERT_TRUE(st.empty());
  ASSERT_TRUE(st.empty());
}

TEST(Test_12, init_and_size_set) {
  my::Set<int> st;
  st.insert(4);
  st.insert(1);
  ASSERT_EQ(st.size(), 2);
}

TEST(Test_13, init_and_size_set) {
  my::Set<int> st;
  st.insert(4);
  st.insert(1);
  my::Set<int>::iterator iter = st.begin();
  ++iter;
  --iter;
  st.erase(iter);
  ASSERT_EQ(st.size(), 1);
}

TEST(Test_14, my_erase_tree) {
  TreeSet<int> mp;
  mp.Insert(7);
  mp.Insert(3);
  mp.Insert(9);
  mp.Insert(2);
  mp.Insert(5);
  mp.Insert(8);
  mp.Insert(1);
  mp.Insert(4);
  mp.Insert(6);
  mp.Erase(1);
  ASSERT_EQ(mp.Size(), 8);
}

TEST(Test_15, clear_set) {
  my::Set<int> st;
  st.insert(4);
  st.insert(1);
  st.clear();
  ASSERT_EQ(st.size(), 0);
}

// *************** queue ******************

// ************************ Базовый конструктор ************************
TEST(QueueConstructors, DefaultConstructor) {
  my::Queue<int> my_queue_int;
  ASSERT_TRUE(my_queue_int.Empty());
  ASSERT_EQ(my_queue_int.Size(), 0);

  my::Queue<size_t> my_queue_size_t;
  ASSERT_TRUE(my_queue_size_t.Empty());
  ASSERT_EQ(my_queue_size_t.Size(), 0);

  my::Queue<double> my_queue_double;
  ASSERT_TRUE(my_queue_double.Empty());
  ASSERT_EQ(my_queue_double.Size(), 0);

  my::Queue<char> my_queue_char;
  ASSERT_TRUE(my_queue_char.Empty());
  ASSERT_EQ(my_queue_char.Size(), 0);

  my::Queue<std::string> my_queue_string;
  ASSERT_TRUE(my_queue_string.Empty());
  ASSERT_EQ(my_queue_string.Size(), 0);
}

// ************************ Конструктор инициализации ************************
TEST(Queue_Constructors, initializer_queue_constructor) {
  my::Queue<int> my_queue_int{8, 1, 20, 7, 4};
  ASSERT_EQ(my_queue_int.Size(), 5);
  ASSERT_EQ(my_queue_int.Back(), 4);
  ASSERT_EQ(my_queue_int.Front(), 8);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Ivan"};
  ASSERT_EQ(my_queue_string.Size(), 3);
  ASSERT_EQ(my_queue_string.Back(), "Ivan");
  ASSERT_EQ(my_queue_string.Front(), "Hello");
}

// ************************ Конструткор копирвоания ************************
TEST(QueueConstructors, CopyConstructor) {
  my::Queue<int> my_queue_int{8, 1, 20, 7, 4};
  my::Queue<int> my_queue_int2(my_queue_int);
  ASSERT_EQ(my_queue_int.Size(), 5);
  ASSERT_EQ(my_queue_int.Back(), 4);
  ASSERT_EQ(my_queue_int.Front(), 8);
  ASSERT_EQ(my_queue_int2.Size(), 5);
  ASSERT_EQ(my_queue_int2.Back(), 4);
  ASSERT_EQ(my_queue_int2.Front(), 8);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Ivan"};
  my::Queue<std::string> my_queue_string2(my_queue_string);
  ASSERT_EQ(my_queue_string.Size(), 3);
  ASSERT_EQ(my_queue_string.Back(), "Ivan");
  ASSERT_EQ(my_queue_string.Front(), "Hello");
  ASSERT_EQ(my_queue_string2.Size(), 3);
  ASSERT_EQ(my_queue_string2.Back(), "Ivan");
  ASSERT_EQ(my_queue_string2.Front(), "Hello");
}

// ************************ Конструткор переноса ************************
TEST(QueueConstructors, MoveConstructor) {
  my::Queue<int> my_queue_int;
  my_queue_int.Push(4);
  my_queue_int.Push(7);
  my_queue_int.Push(20);
  my_queue_int.Push(1);
  my_queue_int.Push(8);
  std::queue<int> std_queue;
  std_queue.push(4);
  std_queue.push(7);
  std_queue.push(20);
  std_queue.push(1);
  std_queue.push(8);
  my::Queue<int> my_queue_int2(std::move(my_queue_int));
  ASSERT_EQ(my_queue_int.Size(), 0);
  ASSERT_EQ(my_queue_int2.Size(), 5);
  ASSERT_EQ(my_queue_int2.Back(), std_queue.back());
  ASSERT_EQ(my_queue_int2.Front(), std_queue.front());

  my::Queue<std::string> my_queue_string;
  my_queue_string.Push("Ivan");
  my_queue_string.Push("I'm");
  my_queue_string.Push("Hello");
  std::queue<std::string> std_queue2;
  std_queue2.push("Ivan");
  std_queue2.push("I'm");
  std_queue2.push("Hello");
  my::Queue<std::string> my_queue_string2(std::move(my_queue_string));
  ASSERT_EQ(my_queue_string.Size(), 0);
  ASSERT_EQ(my_queue_string2.Size(), 3);
  ASSERT_EQ(my_queue_string2.Back(), std_queue2.back());
  ASSERT_EQ(my_queue_string2.Front(), std_queue2.front());
}

// ************** Перегрузка оператора **************
TEST(QueueOverload, AssignmentOperator) {
  my::Queue<int> my_queue_int{8, 1, 20, 7, 4};
  my::Queue<int> my_queue_int2;
  my_queue_int2 = my_queue_int;
  ASSERT_EQ(my_queue_int.Size(), 5);
  ASSERT_EQ(my_queue_int.Back(), 4);
  ASSERT_EQ(my_queue_int.Front(), 8);
  ASSERT_EQ(my_queue_int2.Size(), 5);
  ASSERT_EQ(my_queue_int2.Back(), 4);
  ASSERT_EQ(my_queue_int2.Front(), 8);

  // my::Queue<double> my_queue_double{0.7, -4.4, 7.1, 2.3};
  // my::Queue<double> my_queue_double2{10.1, 10.2};
  // my_queue_double2 = my_queue_double;
  // ASSERT_EQ(my_queue_double.Size(), 4);
  // ASSERT_DOUBLE_EQ(my_queue_double.Back(), 2.3);
  // ASSERT_DOUBLE_EQ(my_queue_double.Front(), 0.7);
  // ASSERT_EQ(my_queue_double2.Size(), 4);
  // ASSERT_DOUBLE_EQ(my_queue_double2.Back(), 2.3);
  // ASSERT_DOUBLE_EQ(my_queue_double2.Front(), 0.7);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Ivan"};
  my::Queue<std::string> my_queue_string2{"Aboba", "to", "and", "Ababo"};
  my_queue_string2 = std::move(my_queue_string);
  ASSERT_EQ(my_queue_string.Size(), 0);
  ASSERT_EQ(my_queue_string2.Size(), 3);
  ASSERT_EQ(my_queue_string2.Back(), "Ivan");
  ASSERT_EQ(my_queue_string2.Front(), "Hello");
}

// ************** Pop **************
TEST(QueueModifiers, TestPushPop) {
  my::Queue<int> my_queue_int({777, -3, 1, 0, 5});
  std::queue<int> queue_int({777, -3, 1, 0, 5});
  my_queue_int.Push(9);
  queue_int.push(9);
  ASSERT_EQ(my_queue_int.Back(), queue_int.back());

  my_queue_int.Pop();
  queue_int.pop();
  ASSERT_EQ(my_queue_int.Front(), queue_int.front());

  my::Queue<std::string> my_queue_string({"Hello"});
  std::queue<std::string> queue_string({"Hello"});
  my_queue_string.Pop();
  queue_string.pop();
  ASSERT_TRUE(my_queue_string.Empty());
  ASSERT_TRUE(queue_string.empty());

  my_queue_string.Push("Ivan");
  queue_string.push("Ivan");
  ASSERT_EQ(my_queue_string.Back(), queue_string.back());
  ASSERT_EQ(my_queue_string.Front(), queue_string.front());
}

// ************** Swap **************
TEST(QueueModifiers, TestSwap) {
  my::Queue<double> my_queue_double{0.5, -3.9, 1.5, 2.3};
  my::Queue<double> my_queue_double2{100.1, 100.2};

  my_queue_double2.Swap(my_queue_double);
  ASSERT_EQ(my_queue_double.Size(), 2);
  ASSERT_DOUBLE_EQ(my_queue_double.Back(), 100.2);
  ASSERT_DOUBLE_EQ(my_queue_double.Front(), 100.1);
  ASSERT_EQ(my_queue_double2.Size(), 4);
  ASSERT_DOUBLE_EQ(my_queue_double2.Back(), 2.3);
  ASSERT_DOUBLE_EQ(my_queue_double2.Front(), 0.5);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Ivan"};
  my::Queue<std::string> my_queue_string2{"Aboba", "to", "and", "Ababo"};
  my_queue_string2.Swap(my_queue_string);
  ASSERT_EQ(my_queue_string.Size(), 4);
  ASSERT_EQ(my_queue_string.Back(), "Ababo");
  ASSERT_EQ(my_queue_string.Front(), "Aboba");
  ASSERT_EQ(my_queue_string2.Size(), 3);
  ASSERT_EQ(my_queue_string2.Back(), "Ivan");
  ASSERT_EQ(my_queue_string2.Front(), "Hello");
}

// *********************** Stack ************************

// ************************ Базовый конструктор ************************
TEST(Constructor, Defolt) {
  my::Stack<int> test1;
  my::Stack<int> test2{};
}

// ************************ Конструктор инициализации ************************
TEST(ConstructorInit, InitList) {
  my::Stack<int> test_s{1, 2, 3};
  for (int i = test_s.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(test_s.Top(), i);
    test_s.Pop();
  }
}
// ************************ Конструткор копирвоания ************************
TEST(ConstructorCopy, Copy) {
  my::Stack<int> test_1{1, 2, 3, 4, 5};
  my::Stack<int> test_2(test_1);
  GTEST_ASSERT_EQ(test_1.Size(), test_2.Size());
  for (int i = test_1.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(test_1.Top(), test_2.Top());
    test_1.Pop();
    test_2.Pop();
  }
}

// ************************ Конструткор переноса ************************
TEST(ConstructorMove, Move) {
  my::Stack<int> test_1{1, 2, 3, 4, 5};
  my::Stack<int> test_2(std::move(test_1));
  GTEST_ASSERT_EQ(test_2.Size(), 5);
  for (int i = test_2.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(i, test_2.Top());
    test_2.Pop();
  }
}

// ************** Перегрузка оператора **************
TEST(Equal, OverloadLvalue_1) {
  my::Stack<int> test1{1, 2, 3};
  my::Stack<int> b2;
  b2 = test1;
  GTEST_ASSERT_EQ(b2.Size(), test1.Size());
  for (int i = b2.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(b2.Top(), test1.Top());
    b2.Pop();
    test1.Pop();
  }
}

TEST(Equal, OverloadLvalue_2) {
  my::Stack<int> test1{1, 2, 3};
  test1 = test1;
  GTEST_ASSERT_EQ(3, test1.Size());
  for (int i = test1.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(i, test1.Top());
    test1.Pop();
  }
}

TEST(Equal, OverloadRvalue_1) {
  my::Stack<int> test1{1, 2, 3};
  my::Stack<int> b2;
  b2 = std::move(test1);
  GTEST_ASSERT_EQ(0, test1.Size());
  GTEST_ASSERT_EQ(3, b2.Size());
  for (int i = b2.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(b2.Top(), i);
    b2.Pop();
  }
}

TEST(Equal, OverloadRvalue_2) {
  my::Stack<int> test1{1, 2, 3};
  test1 = std::move(test1);
  GTEST_ASSERT_EQ(3, test1.Size());
  for (int i = test1.Size(); i > 0; i--) {
    GTEST_ASSERT_EQ(test1.Top(), i);
    test1.Pop();
  }
}

// ************** Size *************
TEST(func, size_1) {
  my::Stack<int> test1;
  GTEST_ASSERT_EQ(test1.Size(), 0);
}

TEST(TestModif, size_2) {
  my::Stack<int> test1{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test1.Size(), 5);
}

// ************** Top *************
TEST(TestModif, top_1) {
  my::Stack<int> test1{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test1.Top(), 5);
}

// ************** Empty *************
TEST(TestModif, empty_1) {
  my::Stack<int> test1{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test1.Empty(), 0);
}

TEST(TestModif, empty_2) {
  my::Stack<int> testa{};
  GTEST_ASSERT_EQ(testa.Empty(), 1);
}

// ************** Pop **************
TEST(TestModif, PushPop) {
  my::Stack<int> test_s;
  test_s.Push(1);
  test_s.Push(2);
  test_s.Push(3);
  test_s.Pop();
  test_s.Pop();
  test_s.Push(1);
  test_s.Pop();
  test_s.Pop();
  GTEST_ASSERT_EQ(test_s.Empty(), 1);
}

// ************** Swap **************
TEST(TestModif, Swap) {
  my::Stack<int> test_1;
  my::Stack<int> test_2{1, 2, 3};
  test_1.Push(1);
  test_1.Push(1);
  test_1.Push(1);
  test_1.Push(1);
  test_1.Push(1);
  test_1.Swap(test_2);
  GTEST_ASSERT_EQ(test_1.Size(), 3);
  GTEST_ASSERT_EQ(test_2.Size(), 5);
}

// ********************** Vector **********************

// ************************ Базовый конструктор ************************
TEST(ConstructorDef, Defolt) {
  my::Vector<int> test1{};
  my::Vector<int> test2;
}

// ************************ Конструктор инициализации ************************
TEST(ConstructorInit1, Init1) {
  my::Vector<int> test1{4, 5, 2};
  GTEST_ASSERT_EQ(test1.Size(), 3);
  GTEST_ASSERT_EQ(test1.Capacity(), 6);
}

TEST(ConstructorInit2, Init2) {
  my::Vector<int> test1{1};
  GTEST_ASSERT_EQ(test1.Size(), 1);
  GTEST_ASSERT_EQ(test1.Capacity(), 2);
}

// ************************ Конструктор Size ************************
TEST(ConstructorSize, WithSize) { my::Vector<int> test1(50); }

// ************************ Конструткор копирвоания ************************
TEST(ConstructorCopyVector, Copy) {
  my::Vector<int> test1{1, 2, 3, 4, 5};
  my::Vector<int> v(test1);
  GTEST_ASSERT_EQ(test1.Size(), v.Size());
  for (int i = test1.Size(); i > 0; --i) {
    GTEST_ASSERT_EQ(test1.Back(), v.Back());
    test1.PopBack();
    v.PopBack();
  }
}

TEST(ConstructorCopyEqual, Copy2) {
  my::Vector<int> test1{1, 2, 3, 4, 5};
  my::Vector<int> a;
  a = test1;
  GTEST_ASSERT_EQ(test1.Size(), a.Size());
  for (int i = test1.Size(); i > 0; --i) {
    GTEST_ASSERT_EQ(test1.Back(), a.Back());
    test1.PopBack();
    a.PopBack();
  }
}

// ************************ Конструткор переноса ************************
TEST(ConstructorMoveVector, Move) {
  my::Vector<int> test1{1, 2, 3, 4, 5};
  my::Vector<int> v(std::move(test1));
}

TEST(ConstructorMoveEqual, Move2) {
  my::Vector<int> a{1, 2, 3, 4, 5};
  my::Vector<int> b;
  b = std::move(a);
  GTEST_ASSERT_EQ(b.Size(), 5);
  GTEST_ASSERT_EQ(b.Capacity(), 10);
  GTEST_ASSERT_EQ(b.Front(), 1);
  GTEST_ASSERT_EQ(b.Back(), 5);
}

// ************** Перегрузка оператора **************

// ************** Push **************
TEST(MethodsPush, PushBack) {
  my::Vector<int> test1;
  test1.PushBack(15);
  test1.PushBack(15);
  GTEST_ASSERT_EQ(test1.Size(), 2);
}
// ************** Pop **************
TEST(MethodsPop, PopBack) {
  my::Vector<int> test1;
  test1.PushBack(15);
  test1.PushBack(15);
  test1.PushBack(15);
  test1.PushBack(15);
  test1.PushBack(15);
  test1.PopBack();
  test1.PopBack();
  GTEST_ASSERT_EQ(test1.Size(), 3);
}

// ************** Empty **************
TEST(MethodsEmpty, Empty1) {
  my::Vector<int> test1;
  test1.PushBack(15);
  test1.PushBack(15);
  GTEST_ASSERT_EQ(test1.Empty(), 0);
}

TEST(MethodsEmpty, Empty2) {
  my::Vector<int> test1;
  GTEST_ASSERT_EQ(test1.Empty(), 1);
}

// ************** Front **************
TEST(MethodsFront, Front) {
  my::Vector<int> test1{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test1.Front(), 1);
}

// ************** Back **************
TEST(MethodsBack, Back) {
  my::Vector<int> test1{1, 2, 3, 4, 5};
  GTEST_ASSERT_EQ(test1.Back(), 5);
}

// ************** Data **************
TEST(MethodsData, Data) {
  my::Vector<int> test1{1, 2, 3, 4, 5};
  int* data = test1.Data();
  data[2] = 1;
  test1.PopBack();
  test1.PopBack();
  GTEST_ASSERT_EQ(test1.Back(), 1);
}

// ************** Capacity **************
TEST(MethodsCapacity, Capacity1) {
  my::Vector<int> test1;
  GTEST_ASSERT_EQ(test1.Capacity(), 0);
  test1.PushBack(1);
  test1.PushBack(2);
  test1.Clear();
  GTEST_ASSERT_EQ(test1.Capacity(), 2);
}

TEST(MethodsCapacity, Capacity2) {
  my::Vector<int> test1(50);
  test1.PushBack(1);
  test1.PushBack(2);
  GTEST_ASSERT_EQ(test1.Capacity(), 100);
}

TEST(MethodsMaxSize, MaxSize) {
  my::Vector<int> test1(50);
  GTEST_ASSERT_EQ(test1.MaxSize(), 2305843009213693951);
}

// ************** Bracket **************
TEST(OverloadBracket, Bracket) {
  my::Vector<int> test1(7);
  test1.PushBack(-2);
  test1.PushBack(2);
  test1.PushBack(3);
  test1.PushBack(4);
  test1.PushBack(5);
  test1.PushBack(6);
  test1.PushBack(7);
  test1[6] = -2;
  GTEST_ASSERT_EQ(test1[6], -2);
  GTEST_ASSERT_EQ(0, test1.Front());
}

// ************** At **************
TEST(MethodsAt, At) {
  my::Vector<int> test1(7);
  test1.PushBack(-2);
  test1.PushBack(2);
  test1.PushBack(3);
  test1.PushBack(4);
  test1.PushBack(5);
  test1.PushBack(6);
  test1.PushBack(7);
  test1[6] = -2;
  GTEST_ASSERT_EQ(test1.At(6), -2);
  GTEST_ASSERT_EQ(0, test1.Front());
}

TEST(MethodsAt, At2) {
  my::Vector<int> test1(7);
  test1.PushBack(-2);
  test1.PushBack(2);
  test1.PushBack(3);
  test1.PushBack(4);
  test1.PushBack(5);
  test1.PushBack(6);
  test1.PushBack(7);
  EXPECT_THROW(test1.At(-2), invalid_argument);
}

// ************** Reserve **************
TEST(MethodsReserve, Reserve1) {
  my::Vector<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test1.Capacity(), 20);
  test1.Reserve(50);
  GTEST_ASSERT_EQ(test1.Size(), 10);
  GTEST_ASSERT_EQ(test1.Capacity(), 50);
  for (int i = 0; i < 10; ++i) {
    GTEST_ASSERT_EQ(test1.At(i), i + 1);
  }
}

// ************** ShrinkToFit **************
TEST(MethodsShrinkToFit1, ShrinkToFit1) {
  my::Vector<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(test1.Capacity(), 20);
  test1.Reserve(50);
  test1.PushBack(11);
  test1.PushBack(12);
  GTEST_ASSERT_EQ(test1.Capacity(), 50);
  GTEST_ASSERT_EQ(test1.Size(), 12);
  test1.ShrinkToFit();
  GTEST_ASSERT_EQ(test1.Size(), 12);
  GTEST_ASSERT_EQ(test1.Capacity(), 12);
  for (int i = 0; i < 12; ++i) {
    GTEST_ASSERT_EQ(test1.At(i), i + 1);
  }
}

// ************** Begin **************
TEST(MethodsBegin, Begin) {
  my::Vector<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  GTEST_ASSERT_EQ(*(test1.Begin()), 1);
}

// ************** End **************
TEST(MethodsEnd, End) {
  my::Vector<int> test1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int* num = test1.End();
  num--;
  GTEST_ASSERT_EQ(*num, 10);
}

// ************** Erase **************
TEST(MethodsIter, EraseBegin) {
  my::Vector<int> test1;
  test1.PushBack(11);
  test1.PushBack(22);
  test1.PushBack(33);
  test1.PushBack(44);
  test1.PushBack(55);
  auto iter = test1.Begin();
  test1.Erase(iter);
  GTEST_ASSERT_EQ(test1.Size(), 4);
  GTEST_ASSERT_EQ(test1.At(0), 22);
  GTEST_ASSERT_EQ(test1.At(1), 33);
  GTEST_ASSERT_EQ(test1.At(2), 44);
  GTEST_ASSERT_EQ(test1.At(3), 55);
}

TEST(MethodsIter, EraseMidl) {
  my::Vector<int> test_1;
  test_1.PushBack(11);
  test_1.PushBack(22);
  test_1.PushBack(33);
  auto iter = test_1.Begin();
  ++iter;
  test_1.Erase(iter);
  GTEST_ASSERT_EQ(test_1.Size(), 2);
  GTEST_ASSERT_EQ(test_1.At(0), 11);
  GTEST_ASSERT_EQ(test_1.At(1), 33);
}

TEST(MethodsIter, EraseEnd) {
  my::Vector<int> test_1;
  test_1.PushBack(11);
  test_1.PushBack(22);
  test_1.PushBack(33);
  test_1.PushBack(44);
  test_1.PushBack(55);
  auto iter = test_1.End();
  --iter;
  test_1.Erase(iter);
  GTEST_ASSERT_EQ(test_1.Size(), 4);
  GTEST_ASSERT_EQ(test_1.At(0), 11);
  GTEST_ASSERT_EQ(test_1.At(1), 22);
  GTEST_ASSERT_EQ(test_1.At(2), 33);
  GTEST_ASSERT_EQ(test_1.At(3), 44);
}

// ************** Insert **************
TEST(MethodsIter, InsertBegin) {
  my::Vector<int> test_1;
  test_1.PushBack(11);
  test_1.PushBack(22);
  test_1.PushBack(33);
  test_1.PushBack(44);
  test_1.PushBack(55);
  test_1.PushBack(66);
  test_1.PushBack(77);
  test_1.PushBack(88);
  test_1.PushBack(99);
  auto iter = test_1.Begin();
  test_1.Insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.Size(), 11);
  GTEST_ASSERT_EQ(test_1.At(0), 21);
  GTEST_ASSERT_EQ(test_1.At(1), 11);
  GTEST_ASSERT_EQ(test_1.At(2), 22);
  GTEST_ASSERT_EQ(test_1.At(3), 33);
  GTEST_ASSERT_EQ(test_1.At(4), 44);
  GTEST_ASSERT_EQ(test_1.At(5), 55);
  GTEST_ASSERT_EQ(test_1.At(6), 66);
  GTEST_ASSERT_EQ(test_1.At(7), 77);
  GTEST_ASSERT_EQ(test_1.At(8), 88);
  GTEST_ASSERT_EQ(test_1.At(9), 99);
}

TEST(MethodsIter, InsertMidl) {
  my::Vector<int> test_1;
  test_1.PushBack(11);
  test_1.PushBack(22);
  test_1.PushBack(33);
  test_1.PushBack(44);
  test_1.PushBack(55);
  test_1.PushBack(66);
  test_1.PushBack(77);
  test_1.PushBack(88);
  test_1.PushBack(99);
  auto iter = test_1.Begin();
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  test_1.Insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.Size(), 11);
  GTEST_ASSERT_EQ(test_1.At(0), 11);
  GTEST_ASSERT_EQ(test_1.At(1), 22);
  GTEST_ASSERT_EQ(test_1.At(2), 33);
  GTEST_ASSERT_EQ(test_1.At(3), 44);
  GTEST_ASSERT_EQ(test_1.At(4), 21);
  GTEST_ASSERT_EQ(test_1.At(5), 55);
  GTEST_ASSERT_EQ(test_1.At(6), 66);
  GTEST_ASSERT_EQ(test_1.At(7), 77);
  GTEST_ASSERT_EQ(test_1.At(8), 88);
  GTEST_ASSERT_EQ(test_1.At(9), 99);
}

TEST(iter, insert_3_end) {
  my::Vector<int> test_1;
  test_1.PushBack(11);
  test_1.PushBack(22);
  test_1.PushBack(33);
  test_1.PushBack(44);
  test_1.PushBack(55);
  test_1.PushBack(66);
  test_1.PushBack(77);
  test_1.PushBack(88);
  test_1.PushBack(99);
  auto iter = test_1.End();
  test_1.Insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.Size(), 11);
  GTEST_ASSERT_EQ(test_1.At(0), 11);
  GTEST_ASSERT_EQ(test_1.At(1), 22);
  GTEST_ASSERT_EQ(test_1.At(2), 33);
  GTEST_ASSERT_EQ(test_1.At(3), 44);
  GTEST_ASSERT_EQ(test_1.At(4), 55);
  GTEST_ASSERT_EQ(test_1.At(5), 66);
  GTEST_ASSERT_EQ(test_1.At(6), 77);
  GTEST_ASSERT_EQ(test_1.At(7), 88);
  GTEST_ASSERT_EQ(test_1.At(8), 99);
  GTEST_ASSERT_EQ(test_1.At(9), 21);
}

TEST(iter, insert_4) {
  my::Vector<int> test_1;
  test_1.PushBack(11);
  auto iter = test_1.Begin();
  test_1.Insert(iter, 21);
  GTEST_ASSERT_EQ(test_1.Size(), 3);
  GTEST_ASSERT_EQ(test_1.At(0), 21);
  GTEST_ASSERT_EQ(test_1.At(1), 11);
}

// ************** Swap **************
TEST(MethodsSwap, Swap1) {
  my::Vector<int> test1;
  my::Vector<int> test2(50);
  test1.PushBack(1);
  test1.PushBack(1);
  test1.PushBack(1);
  test1.PushBack(1);
  test1.PushBack(1);
  test2.PushBack(2);
  test2.PushBack(2);
  test2.PushBack(2);
  test1.Swap(test2);
  GTEST_ASSERT_EQ(test1.Size(), 53);
  GTEST_ASSERT_EQ(test2.Size(), 5);
  GTEST_ASSERT_EQ(test1.Capacity(), 100);
  GTEST_ASSERT_EQ(test2.Capacity(), 8);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}