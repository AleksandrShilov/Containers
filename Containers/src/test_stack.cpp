#include <gtest/gtest.h>

#include <iomanip>
#include <stack>

#include "my_stack.h"

using namespace std;

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}