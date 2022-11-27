#include <gtest/gtest.h>

#include <iomanip>
#include <queue>

#include "my_queue.h"

using namespace std;

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

  my::Queue<double> my_queue_double{0.7, -4.4, 7.1, 2.3};
  my::Queue<double> my_queue_double2{10.1, 10.2};
  my_queue_double2 = my_queue_double;
  ASSERT_EQ(my_queue_double.Size(), 4);
  ASSERT_DOUBLE_EQ(my_queue_double.Back(), 2.3);
  ASSERT_DOUBLE_EQ(my_queue_double.Front(), 0.7);
  ASSERT_EQ(my_queue_double2.Size(), 4);
  ASSERT_DOUBLE_EQ(my_queue_double2.Back(), 2.3);
  ASSERT_DOUBLE_EQ(my_queue_double2.Front(), 0.7);

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}