#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <list>

#include "ngstub.h"

namespace {

TEST_CASE("threadlist") {
  Threadlist list1;
  list1.reserve(100);
  BENCHMARK("threadlist performance") {
    list1.clear();
    for (unsigned int i = 0; i < 40; ++i) {
      list1.insert(list1.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list1.begin();
    for (unsigned int i = 0; i < 10; ++i) {
      itr = list1.erase(itr);
      ++itr;
      ++itr;
    }
    for (unsigned int i = 0; i < 10; ++i) {
      list1.insert(list1.begin(), ThreadNG{i, LG_SearchHit()});
    }
  };

  std::list<ThreadNG> list2;
  BENCHMARK("stdlist performance") {
    list2.clear();
    for (unsigned int i = 0; i < 40; ++i) {
      list2.insert(list2.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list2.begin();
    for (unsigned int i = 0; i < 10; ++i) {
      itr = list2.erase(itr);
      ++itr;
      ++itr;
    }
    for (unsigned int i = 0; i < 10; ++i) {
      list2.insert(list2.begin(), ThreadNG{i, LG_SearchHit()});
    }
  };

  std::vector<ThreadNG> list3;
  list3.reserve(100);
  BENCHMARK("vectorlist performance") {
    list3.clear();
    for (unsigned int i = 0; i < 40; ++i) {
      list3.insert(list3.begin(), ThreadNG{i, LG_SearchHit()});
    }
    auto itr = list3.begin();
    for (unsigned int i = 0; i < 10; ++i) {
      itr = list3.erase(itr);
      ++itr;
      ++itr;
    }
    for (unsigned int i = 0; i < 10; ++i) {
      list3.insert(list3.begin(), ThreadNG{i, LG_SearchHit()});
    }
  };
}
}
