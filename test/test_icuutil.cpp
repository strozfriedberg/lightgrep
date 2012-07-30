#include <scope/test.h>

#include <memory>

#include "icuutil.h"

SCOPE_TEST(testUnicodeSetICUToLGDstEmpty) {
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40}}, act;

  convUnicodeSet(act, src.get());
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(testUnicodeSetICUToLGDstNonEmpty) {
  // test that convUnicodeSet clears dst
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40}}, act{0xBEEF};

  convUnicodeSet(act, src.get());
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(testUnicodeSetLGToICUDstEmpty) {
  UnicodeSet src{{0x27,0x40}};
  std::unique_ptr<USet, void(*)(USet*)> exp(uset_open(0x27, 0x3F), uset_close);
  std::unique_ptr<USet, void(*)(USet*)> act(uset_openEmpty(), uset_close);

  convUnicodeSet(act.get(), src);
  SCOPE_ASSERT(uset_equals(exp.get(), act.get()));
}

SCOPE_TEST(testUnicodeSetLGToICUDstNonEmpty) {
  // test that convUnicodeSet clears dst
  UnicodeSet src{{0x27,0x40}};
  std::unique_ptr<USet, void(*)(USet*)> exp(uset_open(0x27, 0x3F), uset_close);
  std::unique_ptr<USet, void(*)(USet*)> act(uset_open(0xBEEF, 0xBEEF), uset_close);

  convUnicodeSet(act.get(), src);
  SCOPE_ASSERT(uset_equals(exp.get(), act.get()));
}
