#include <scope/test.h>

#include <sstream>

#include "basic.h"
#include "parseutil.h"

SCOPE_TEST(parseHexCharTest) {
  // good
  SCOPE_ASSERT_EQUAL(0x0, parseHexChar('0'));
  SCOPE_ASSERT_EQUAL(0x1, parseHexChar('1'));
  SCOPE_ASSERT_EQUAL(0x2, parseHexChar('2'));
  SCOPE_ASSERT_EQUAL(0x3, parseHexChar('3'));
  SCOPE_ASSERT_EQUAL(0x4, parseHexChar('4'));
  SCOPE_ASSERT_EQUAL(0x5, parseHexChar('5'));
  SCOPE_ASSERT_EQUAL(0x6, parseHexChar('6'));
  SCOPE_ASSERT_EQUAL(0x7, parseHexChar('7'));
  SCOPE_ASSERT_EQUAL(0x8, parseHexChar('8'));
  SCOPE_ASSERT_EQUAL(0x9, parseHexChar('9'));
  SCOPE_ASSERT_EQUAL(0xA, parseHexChar('A'));
  SCOPE_ASSERT_EQUAL(0xB, parseHexChar('B'));
  SCOPE_ASSERT_EQUAL(0xC, parseHexChar('C'));
  SCOPE_ASSERT_EQUAL(0xD, parseHexChar('D'));
  SCOPE_ASSERT_EQUAL(0xE, parseHexChar('E'));
  SCOPE_ASSERT_EQUAL(0xF, parseHexChar('F'));
  SCOPE_ASSERT_EQUAL(0xA, parseHexChar('a'));
  SCOPE_ASSERT_EQUAL(0xB, parseHexChar('b'));
  SCOPE_ASSERT_EQUAL(0xC, parseHexChar('c'));
  SCOPE_ASSERT_EQUAL(0xD, parseHexChar('d'));
  SCOPE_ASSERT_EQUAL(0xE, parseHexChar('e'));
  SCOPE_ASSERT_EQUAL(0xF, parseHexChar('f'));

  // bad
  for (int i = -10; i < '0'; ++i) {
    SCOPE_ASSERT_EQUAL(-1, parseHexChar(i));
  }

  for (int i = ':'; i < 'A'; ++i) {
    SCOPE_ASSERT_EQUAL(-1, parseHexChar(i));
  }

  for (int i = '['; i < 'a'; ++i) {
    SCOPE_ASSERT_EQUAL(-1, parseHexChar(i));
  }

  for (int i = '{'; i < 300; ++i) {
    SCOPE_ASSERT_EQUAL(-1, parseHexChar(i));
  } 
}

SCOPE_TEST(parseHexShortTest) {
  char b[3] = { 'h', 'h', '\0' };

  b[0] = 0x00;
  for (uint32 l = 0; l < 256; b[0] = ++l) {
    b[1] = 0x00;
    for (uint32 r = 0; r < 256; b[1] = ++r) {
      int exp;
      if (
          (('0' <= l && l <= '9') ||
           ('A' <= l && l <= 'F') ||
           ('a' <= l && l <= 'f')) &&
          (('0' <= r && r <= '9') ||
           ('A' <= r && r <= 'F') ||
           ('a' <= r && r <= 'f'))
         )
      {
        std::istringstream in(b);
        in >> std::hex >> exp;
      }
      else {
        exp = -1;
      } 

      const char* h = b;
      SCOPE_ASSERT_EQUAL(exp, parseHexShort(h, h+2));

      if (exp != -1) {
        SCOPE_ASSERT_EQUAL(b+2, h);
      }
    }
  }
}

typedef std::string::const_iterator SItr;

template <class F>
void fixture(F func, const std::string& s, int exp, int len) {
  std::string::const_iterator i(s.begin());
  SCOPE_ASSERT_EQUAL(exp, func(i, s.end()));
  if (exp != -1) {
    SCOPE_ASSERT_EQUAL(len, i - s.begin());
  }
}

SCOPE_TEST(parseHexLongTest) {
  fixture(parseHexLong<SItr>, "",         -1,       -1);
  fixture(parseHexLong<SItr>, "}",        0x0,       1);
  fixture(parseHexLong<SItr>, "1",        -1,       -1);
  fixture(parseHexLong<SItr>, "1}",       0x1,       2);
  fixture(parseHexLong<SItr>, "11",       -1,       -1);
  fixture(parseHexLong<SItr>, "11}",      0x11,      3);
  fixture(parseHexLong<SItr>, "111",      -1,       -1);
  fixture(parseHexLong<SItr>, "111}",     0x111,     4);
  fixture(parseHexLong<SItr>, "1111",     -1,       -1);
  fixture(parseHexLong<SItr>, "1111}",    0x1111,    5);
  fixture(parseHexLong<SItr>, "11111",    -1,       -1);
  fixture(parseHexLong<SItr>, "11111}",   0x11111,   6);
  fixture(parseHexLong<SItr>, "111111",   -1,       -1);
  fixture(parseHexLong<SItr>, "111111}",  0x111111,  7);
  fixture(parseHexLong<SItr>, "1111111",  -1,       -1);
  fixture(parseHexLong<SItr>, "1111111}", -1,       -1);  // > 6 hex digits
}

SCOPE_TEST(parseHexTest) {
  fixture(parseHex<SItr>, "", -1, -1);
  fixture(parseHex<SItr>, "0", -1, -1);
  fixture(parseHex<SItr>, "00", 0, 2);
  fixture(parseHex<SItr>, "{0}", 0, 3);
  fixture(parseHex<SItr>, "{0", -1, -1);
  fixture(parseHex<SItr>, "0}", -1, -1);
  fixture(parseHex<SItr>, "00}", 0, 2);
  fixture(parseHex<SItr>, "{000000}", 0, 8);
  fixture(parseHex<SItr>, "0000000", 0, 2);
}

SCOPE_TEST(parseOctCharTest) {
  // good
  SCOPE_ASSERT_EQUAL(00, parseOctChar('0'));
  SCOPE_ASSERT_EQUAL(01, parseOctChar('1'));
  SCOPE_ASSERT_EQUAL(02, parseOctChar('2'));
  SCOPE_ASSERT_EQUAL(03, parseOctChar('3'));
  SCOPE_ASSERT_EQUAL(04, parseOctChar('4'));
  SCOPE_ASSERT_EQUAL(05, parseOctChar('5'));
  SCOPE_ASSERT_EQUAL(06, parseOctChar('6'));
  SCOPE_ASSERT_EQUAL(07, parseOctChar('7'));

  // bad
  for (int i = -10; i < '0'; ++i) {
    SCOPE_ASSERT_EQUAL(-1, parseOctChar(i));
  }

  for (int i = '8'; i < 300; ++i) {
    SCOPE_ASSERT_EQUAL(-1, parseOctChar(i));
  }
}

SCOPE_TEST(parseOctTest) {
  fixture(parseOct<SItr>, "0",  00, 1);
  fixture(parseOct<SItr>, "01", 01, 2);
  fixture(parseOct<SItr>, "01a", 01, 2);
  fixture(parseOct<SItr>, "0a1", 00, 1);
  fixture(parseOct<SItr>, "000", 00, 3);
  fixture(parseOct<SItr>, "0001", 00, 3);
  fixture(parseOct<SItr>, "377", 0377, 3);
  fixture(parseOct<SItr>, "400", -1, -1); // > 377 is multi-byte
}

SCOPE_TEST(parseNamedCodePointNumberTest) {
  fixture(parseNamedCodePoint<SItr>, "{U+BEEF}", 0xBEEF, 8);
  fixture(parseNamedCodePoint<SItr>, "{U+10FFFF}", 0x10FFFF, 10);
  fixture(parseNamedCodePoint<SItr>, "{U+0}", 0x0, 5);
  fixture(parseNamedCodePoint<SItr>, "{U+123}stuff", 0x123, 7);
  fixture(parseNamedCodePoint<SItr>, "{U+FFFFFFF}", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "{U+bogus}", -1, -1);
}

SCOPE_TEST(parseNamedCodePointNameTest) {
  fixture(parseNamedCodePoint<SItr>, "{LATIN CAPITAL LETTER A}", 'A', 24);
  fixture(parseNamedCodePoint<SItr>, "{CYRILLIC SMALL LETTER DOUBLE MONOCULAR O}", 0xA66D, 42);
  fixture(parseNamedCodePoint<SItr>, "{PILE OF POO}", 0x1F4A9, 13);
  fixture(parseNamedCodePoint<SItr>, "{LATIN SMALL LETTER L WITH KICKSTAND}", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "{bogus", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "bogus", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "{}", -1, -1);
}
