#include <gtest/gtest.h>

#include <iomanip>
#include <vector>

#include "my_vector.h"

using namespace std;

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
TEST(ConstructorCopy, Copy) {
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
TEST(ConstructorMove, Move) {
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