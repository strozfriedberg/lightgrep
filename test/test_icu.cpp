#include <scope/test.h>

#include <set>

#include <unicode/ucnv.h>

#include "basic.h"
#include "container_out.h"

SCOPE_TEST(testICUStandards) {
  // check that ICU is defining exactly the standards we expect

  std::set<std::string> expected{
    "UTR22", "IANA", "MIME", "IBM", "WINDOWS", "JAVA", ""
  };

  std::set<std::string> actual;
  UErrorCode err = U_ZERO_ERROR;
  const uint32 slen = ucnv_countStandards();
  for (uint32 i = 0; i < slen; ++i) {
    actual.insert(ucnv_getStandard(i, &err));
    SCOPE_ASSERT(!U_FAILURE(err));
  }

  SCOPE_ASSERT_EQUAL(expected, actual);
}
