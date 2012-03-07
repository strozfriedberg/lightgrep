#include <scope/test.h>

#include <iostream>
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

void parseHexLongTestFixture(const std::string& s, int exp, int len) {
  std::string::const_iterator i(s.begin());
  SCOPE_ASSERT_EQUAL(exp, parseHexLong(i, s.end()));
  if (exp != -1) {
    SCOPE_ASSERT_EQUAL(len, i - s.begin());
  }
}

SCOPE_TEST(parseHexLongTest) {
  parseHexLongTestFixture("",         -1,       -1);
  parseHexLongTestFixture("}",        0x0,       1);
  parseHexLongTestFixture("1",        -1,       -1);
  parseHexLongTestFixture("1}",       0x1,       2);
  parseHexLongTestFixture("11",       -1,       -1);
  parseHexLongTestFixture("11}",      0x11,      3);
  parseHexLongTestFixture("111",      -1,       -1);
  parseHexLongTestFixture("111}",     0x111,     4);
  parseHexLongTestFixture("1111",     -1,       -1);
  parseHexLongTestFixture("1111}",    0x1111,    5);
  parseHexLongTestFixture("11111",    -1,       -1);
  parseHexLongTestFixture("11111}",   0x11111,   6);
  parseHexLongTestFixture("111111",   -1,       -1);
  parseHexLongTestFixture("111111}",  0x111111,  7);
  parseHexLongTestFixture("1111111",  -1,       -1);
  parseHexLongTestFixture("1111111}", -1,       -1);  // > 6 hex digits
}

void parseHexTestFixture(const std::string& s, int exp, int len) {
  std::string::const_iterator i(s.begin());
  SCOPE_ASSERT_EQUAL(exp, parseHex(i, s.end()));
  if (exp != -1) {
    SCOPE_ASSERT_EQUAL(len, i - s.begin());
  }
}

SCOPE_TEST(parseHexTest) {
  parseHexTestFixture("", -1, -1);
  parseHexTestFixture("0", -1, -1);
  parseHexTestFixture("00", 0, 2);
  parseHexTestFixture("{0}", 0, 3);
  parseHexTestFixture("{0", -1, -1);
  parseHexTestFixture("0}", -1, -1);
  parseHexTestFixture("00}", 0, 2);
  parseHexTestFixture("{000000}", 0, 8);
  parseHexTestFixture("0000000", 0, 2);
}

