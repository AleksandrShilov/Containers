#include <gtest/gtest.h>

#include <cmath>
#include <map>
#include <set>

#include "my_map.h"
#include "my_set.h"

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

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
