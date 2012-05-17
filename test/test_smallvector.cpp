#include <scope/test.h>

#include "basic.h"
#include "smallvector.h"

SCOPE_TEST(smallvector1Ctor) {
  std::vector<std::vector<int>> store;
  ExternalOverflow<int,1> eo(store);
  SmallVector<int,1,ExternalOverflow> v(eo);
  SCOPE_ASSERT_EQUAL(0, v.size());
}

SCOPE_TEST(smallvector1PushBack) {
  std::vector<std::vector<int>> store;
  ExternalOverflow<int,1> eo(store);
  SmallVector<int,1,ExternalOverflow> v(eo);

  for (int32 i = 0; i < 100; ++i) {
    v.push_back(i);
    SCOPE_ASSERT_EQUAL(i+1, v.size());
    SCOPE_ASSERT_EQUAL(i, v[i]);
  }
}

SCOPE_TEST(smallvector1Clear) {
  std::vector<std::vector<int>> store;
  ExternalOverflow<int,1> eo(store);
  SmallVector<int,1,ExternalOverflow> v(eo);

  for (uint32 i = 0; i < 10; ++i) {
    for (uint32 j = 0; j < i; ++j) {
      v.push_back(j);
    }

    SCOPE_ASSERT_EQUAL(i, v.size());
    v.clear();
    SCOPE_ASSERT_EQUAL(0, v.size());
  }
}

SCOPE_TEST(smallvector1Insert) {
  std::vector<std::vector<int>> store;
  ExternalOverflow<int,1> eo(store);
  SmallVector<int,1,ExternalOverflow> v(eo);

  for (int32 i = 0; i < 10; ++i) {
    v.insert(v.begin(), i);
  }

  SCOPE_ASSERT_EQUAL(10, v.size());

  for (int32 i = 0; i < 10; ++i) {
    SCOPE_ASSERT_EQUAL(10-i-1, v[i]);
  }
}

SCOPE_TEST(smallvector1Erase) {
  std::vector<std::vector<int>> store;
  ExternalOverflow<int,1> eo(store);
  SmallVector<int,1,ExternalOverflow> v(eo);

  for (int32 i = 0; i < 10; ++i) {
    v.push_back(i);
  }

  SCOPE_ASSERT_EQUAL(10, v.size());

  for (int32 i = 0; i < 5; ++i) {
    v.erase(v.begin());
  }

  SCOPE_ASSERT_EQUAL(5, v.size());

  for (int32 i = 0; i < 5; ++i) {
    SCOPE_ASSERT_EQUAL(i+5, v[i]);
  }
}

SCOPE_TEST(smallvector1Size) {
  SCOPE_ASSERT(sizeof(SmallVector<uint32,1,ExternalOverflow>) <
               sizeof(std::vector<uint32>) + sizeof(uint32));
}
