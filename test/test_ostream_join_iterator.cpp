#include <scope/test.h>

#include "ostream_join_iterator.h"

#include <algorithm>
#include <sstream>

SCOPE_TEST(joinEmpty) {
  const int a[] = { };
  std::stringstream ss;
  std::copy(a, a, ostream_join_iterator<int>(ss, ", "));
  SCOPE_ASSERT_EQUAL("", ss.str());
}

SCOPE_TEST(joinSingleton) {
  const int a[] = { 1 };
  std::stringstream ss;
  std::copy(a, a + 1, ostream_join_iterator<int>(ss, ", "));
  SCOPE_ASSERT_EQUAL("1", ss.str());
}

SCOPE_TEST(joinMultiple) {
  const int a[] = { 1, 2, 3 };
  std::stringstream ss;
  std::copy(a, a + 3, ostream_join_iterator<int>(ss, ", "));
  SCOPE_ASSERT_EQUAL("1, 2, 3", ss.str());
}
