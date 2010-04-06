#include <scope/test.h>

#include "states.h"

#include <iostream>

SCOPE_TEST(litAccept) {
  LitState lit('a');
  char ch[2] = "a";
  SCOPE_ASSERT_EQUAL(ch+1, lit.allowed(ch, ch+1));
  ch[0] = 'b';
  SCOPE_ASSERT_EQUAL(ch, lit.allowed(ch, ch+1));
  std::bitset<256> bits(0);
  lit.getBits(bits);
  // std::cerr << bits.count() << ": " << bits << std::endl;
  // SCOPE_ASSERT(0 == bits.count());
  SCOPE_ASSERT(bits.test('a'));
  SCOPE_ASSERT(bits.any());
  SCOPE_ASSERT_EQUAL(256u, bits.size());
  SCOPE_ASSERT(!bits.test('c'));
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

SCOPE_TEST(bitset) {
  std::bitset<256> bits(0);
  SCOPE_ASSERT_EQUAL(0u, bits.count());
  bits.set('a');
  SCOPE_ASSERT_EQUAL(1u, bits.count());
}
