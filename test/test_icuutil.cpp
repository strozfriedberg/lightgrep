#include <scope/test.h>

#include "icuutil.h"

SCOPE_TEST(testUnicodeSetICUToLGDstEmpty) {
  icu::UnicodeSet src(0x27, 0x3F);
  ::UnicodeSet exp{{0x27,0x40}}, act;

  convUnicodeSet(act, src);
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(testUnicodeSetICUToLGDstNonEmpty) {
  // test that convUnicodeSet clears dst
  icu::UnicodeSet src(0x27, 0x3F);
  ::UnicodeSet exp{{0x27,0x40}}, act{0xBEEF};

  convUnicodeSet(act, src);
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(testUnicodeSetLGToICUDstEmpty) {
  ::UnicodeSet src{{0x27,0x40}};
  icu::UnicodeSet exp(0x27, 0x3F), act;

  convUnicodeSet(act, src);
  SCOPE_ASSERT(exp == act);
}

SCOPE_TEST(testUnicodeSetLGToICUDstNonEmpty) {
  // test that convUnicodeSet clears dst
  ::UnicodeSet src{{0x27,0x40}};
  icu::UnicodeSet exp(0x27, 0x3F), act(0xBEEF, 0xBEEF);

  convUnicodeSet(act, src);
  SCOPE_ASSERT(exp == act);
}
