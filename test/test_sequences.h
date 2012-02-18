#include <scope/test.h>

#include <vector>

#include "basic.h"
#include "listops.h"

SCOPE_TEST(removeRightDuplicatesTest) {
  std::vector<uint32> v{7,9,7,9};
  removeRightDuplicates(v);
  std::vector<uint32> exp{7,9};
  SCOPE_ASSERT_EQUAL(exp, v);
}
