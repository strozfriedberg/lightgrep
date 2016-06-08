/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <scope/test.h>

#include <sstream>

#include "basic.h"
#include "parseutil.h"
#include "pair_out.h"

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
  for (uint32_t l = 0; l < 256; b[0] = ++l) {
    b[1] = 0x00;
    for (uint32_t r = 0; r < 256; b[1] = ++r) {
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
      SCOPE_ASSERT_EQUAL(exp, parseHexByte(h, h+2));

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

SCOPE_TEST(parseHexCodePointTest) {
  fixture(parseHexCodePoint<SItr>, "",         -1,       -1);
  fixture(parseHexCodePoint<SItr>, "}",        -1,       -1);
  fixture(parseHexCodePoint<SItr>, "1",        -1,       -1);
  fixture(parseHexCodePoint<SItr>, "1}",       0x1,       2);
  fixture(parseHexCodePoint<SItr>, "11",       -1,       -1);
  fixture(parseHexCodePoint<SItr>, "11}",      0x11,      3);
  fixture(parseHexCodePoint<SItr>, "111",      -1,       -1);
  fixture(parseHexCodePoint<SItr>, "111}",     0x111,     4);
  fixture(parseHexCodePoint<SItr>, "1111",     -1,       -1);
  fixture(parseHexCodePoint<SItr>, "1111}",    0x1111,    5);
  fixture(parseHexCodePoint<SItr>, "11111",    -1,       -1);
  fixture(parseHexCodePoint<SItr>, "11111}",   0x11111,   6);
  fixture(parseHexCodePoint<SItr>, "111111",   -1,       -1);
  fixture(parseHexCodePoint<SItr>, "10FFFF}",  0x10FFFF,  7);  // last point
  fixture(parseHexCodePoint<SItr>, "110000}",  -1,       -1);
  fixture(parseHexCodePoint<SItr>, "1111111",  -1,       -1);
  fixture(parseHexCodePoint<SItr>, "1111111}", -1,       -1);  // > 6 digits
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

SCOPE_TEST(parseOctByteTest) {
  fixture(parseOctByte<SItr>, "0",      00,  1);
  fixture(parseOctByte<SItr>, "01",     01,  2);
  fixture(parseOctByte<SItr>, "01a",    01,  2);
  fixture(parseOctByte<SItr>, "0a1",    00,  1);
  fixture(parseOctByte<SItr>, "000",    00,  3);
  fixture(parseOctByte<SItr>, "0001",   00,  3);
  fixture(parseOctByte<SItr>, "377",  0377,  3);
  fixture(parseOctByte<SItr>, "400",    -1, -1); // > 377 is multi-byte
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

SCOPE_TEST(caseDesensitize_a_Test) {
  UnicodeSet aset('a');
  SCOPE_ASSERT(caseDesensitize(aset));

  UnicodeSet eset;
  eset.set('A');
  eset.set('a');
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_A_Test) {
  UnicodeSet aset('A');
  SCOPE_ASSERT(caseDesensitize(aset));

  UnicodeSet eset;
  eset.set('A');
  eset.set('a');
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitizeASCII_DollarSign_Test) {
  UnicodeSet aset('$');
  SCOPE_ASSERT(!caseDesensitize(aset));

  UnicodeSet eset('$');
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitizeASCII_Aa_Test) {
  UnicodeSet aset;
  aset.set('A');
  aset.set('a');
  SCOPE_ASSERT(!caseDesensitize(aset));

  UnicodeSet eset;
  eset.set('A');
  eset.set('a');
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_a_to_z_Test) {
  UnicodeSet aset('a', 'z' + 1);
  SCOPE_ASSERT(caseDesensitize(aset));

  UnicodeSet eset{
    {'A', 'Z' + 1},
    {'a', 'z' + 1},
    {0x17F, 0x180},  // LATIN SMALL LETTER LONG S
    {0x212A, 0x212B} // KELVIN SIGN
  };
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_A_to_Z_Test) {
  UnicodeSet aset('A', 'Z' + 1);
  SCOPE_ASSERT(caseDesensitize(aset));

  UnicodeSet eset{
    {'A', 'Z' + 1},
    {'a', 'z' + 1},
    {0x17F, 0x180},  // LATIN SMALL LETTER LONG S
    {0x212A, 0x212B} // KELVIN SIGN
  };
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_Sigma_Test) {
  UnicodeSet aset(U'Σ');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: ς is the version of σ which ends words in Greek.

  UnicodeSet eset;
  eset.set(U'Σ'); // GREEK CAPITAL LETTER SIGMA
  eset.set(U'σ'); // GREEK SMALL LETTER SIGMA
  eset.set(U'ς'); // GREEK SMALL LETTER FINAL SIGMA
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_sigma_Test) {
  UnicodeSet aset(U'σ');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: ς is the version of σ which ends words in Greek.

  UnicodeSet eset;
  eset.set(U'Σ'); // GREEK CAPITAL LETTER SIGMA
  eset.set(U'σ'); // GREEK SMALL LETTER SIGMA
  eset.set(U'ς'); // GREEK SMALL LETTER FINAL SIGMA
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_final_sigma_Test) {
  UnicodeSet aset(U'ς');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: ς is the version of σ which ends words in Greek.

  UnicodeSet eset;
  eset.set(U'Σ'); // GREEK CAPITAL LETTER SIGMA
  eset.set(U'σ'); // GREEK SMALL LETTER SIGMA
  eset.set(U'ς'); // GREEK SMALL LETTER FINAL SIGMA
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_eszett_Test) {
  UnicodeSet aset(U'ß');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: For UTS #18 Level 2 conformance, ß must also match SS.
  // See also Section 5.18 of the Unicode Standard for a discussion
  // of the Eszett.

  UnicodeSet eset;
  eset.set(U'ß'); // LATIN SMALL LETTER SHARP S
  eset.set(U'ẞ'); // LATIN CAPITAL LETTER SHARP S
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_Eszett_Test) {
  UnicodeSet aset(U'ẞ');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: For UTS #18 Level 2 conformance, ß must also match SS.
  // See also Section 5.18 of the Unicode Standard for a discussion
  // of the Eszett.

  UnicodeSet eset;
  eset.set(U'ß'); // LATIN SMALL LETTER SHARP S
  eset.set(U'ẞ'); // LATIN CAPITAL LETTER SHARP S
  SCOPE_ASSERT_EQUAL(eset, aset);
}
SCOPE_TEST(caseDesensitize_dz_digraph_Test) {
  UnicodeSet aset(U'ǳ');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: Dz is a titlecase version of the dz and DZ digraphs used in
  // various Slavic languages written in the Latin alphabet.

  UnicodeSet eset;
  eset.set(U'ǳ'); // LATIN SMALL LETTER DZ
  eset.set(U'Ǳ'); // LATIN CAPITAL LETTER DZ
  eset.set(U'ǲ'); // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_DZ_digraph_Test) {
  UnicodeSet aset(U'Ǳ');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: Dz is a titlecase version of the dz and DZ digraphs used in
  // various Slavic languages written in the Latin alphabet.

  UnicodeSet eset;
  eset.set(U'ǳ'); // LATIN SMALL LETTER DZ
  eset.set(U'Ǳ'); // LATIN CAPITAL LETTER DZ
  eset.set(U'ǲ'); // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_Dz_digraph_Test) {
  UnicodeSet aset(U'ǲ');
  SCOPE_ASSERT(caseDesensitize(aset));

  // NB: Dz is a titlecase version of the dz and DZ digraphs used in
  // various Slavic languages written in the Latin alphabet.

  UnicodeSet eset;
  eset.set(U'ǳ'); // LATIN SMALL LETTER DZ
  eset.set(U'Ǳ'); // LATIN CAPITAL LETTER DZ
  eset.set(U'ǲ'); // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
  SCOPE_ASSERT_EQUAL(eset, aset);
}
