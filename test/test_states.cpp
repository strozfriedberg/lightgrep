#include <scope/test.h>

#include "states.h"

SCOPE_TEST(litAccept) {
  LitState lit('a');
  char ch = 'a';
  SCOPE_ASSERT_EQUAL(&ch+1, lit.allowed(&ch, &ch+1));
  ch = 'b';
  SCOPE_ASSERT_EQUAL(&ch, lit.allowed(&ch, &ch+1));
}

SCOPE_TEST(eitherAccept) {
  const EitherState e('A', 'a');
  char ch = 'a';
  SCOPE_ASSERT_EQUAL(&ch+1, e.allowed(&ch, &ch+1));
  ch = 'b';
  SCOPE_ASSERT_EQUAL(&ch, e.allowed(&ch, &ch+1));
  ch = 'A';
  SCOPE_ASSERT_EQUAL(&ch+1, e.allowed(&ch, &ch+1));
}

SCOPE_TEST(rangeAccept) {
  const RangeState r('0', '9');
  char ch;
  for (unsigned int i = 0; i < 256; ++i) {
    ch = i;
    if ('0' <= ch && ch <= '9') {
      SCOPE_ASSERT_EQUAL(&ch+1, r.allowed(&ch, &ch+1));
    }
    else {
      SCOPE_ASSERT_EQUAL(&ch, r.allowed(&ch, &ch+1));
    }
  }
}
