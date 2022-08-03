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

#include <catch2/catch_test_macros.hpp>

#include <initializer_list>
#include <iomanip>
#include <sstream>

#include "basic.h"
#include "parseutil.h"
#include "unicode_sets.h"

TEST_CASE("parseHexCharTest") {
  // good
  REQUIRE(0x0 == parseHexChar('0'));
  REQUIRE(0x1 == parseHexChar('1'));
  REQUIRE(0x2 == parseHexChar('2'));
  REQUIRE(0x3 == parseHexChar('3'));
  REQUIRE(0x4 == parseHexChar('4'));
  REQUIRE(0x5 == parseHexChar('5'));
  REQUIRE(0x6 == parseHexChar('6'));
  REQUIRE(0x7 == parseHexChar('7'));
  REQUIRE(0x8 == parseHexChar('8'));
  REQUIRE(0x9 == parseHexChar('9'));
  REQUIRE(0xA == parseHexChar('A'));
  REQUIRE(0xB == parseHexChar('B'));
  REQUIRE(0xC == parseHexChar('C'));
  REQUIRE(0xD == parseHexChar('D'));
  REQUIRE(0xE == parseHexChar('E'));
  REQUIRE(0xF == parseHexChar('F'));
  REQUIRE(0xA == parseHexChar('a'));
  REQUIRE(0xB == parseHexChar('b'));
  REQUIRE(0xC == parseHexChar('c'));
  REQUIRE(0xD == parseHexChar('d'));
  REQUIRE(0xE == parseHexChar('e'));
  REQUIRE(0xF == parseHexChar('f'));

  // bad
  for (int i = -10; i < '0'; ++i) {
    REQUIRE(-1 == parseHexChar(i));
  }

  for (int i = ':'; i < 'A'; ++i) {
    REQUIRE(-1 == parseHexChar(i));
  }

  for (int i = '['; i < 'a'; ++i) {
    REQUIRE(-1 == parseHexChar(i));
  }

  for (int i = '{'; i < 300; ++i) {
    REQUIRE(-1 == parseHexChar(i));
  }
}

TEST_CASE("parseHexShortTest") {
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
      REQUIRE(exp == parseHexByte(h, h+2));

      if (exp != -1) {
        REQUIRE(b+2 == h);
      }
    }
  }
}

typedef std::string::const_iterator SItr;

template <class F>
void fixture(F func, const std::string& s, int exp, int len) {
  std::string::const_iterator i(s.begin());
  REQUIRE(exp == func(i, s.end()));
  if (exp != -1) {
    REQUIRE(len == i - s.begin());
  }
}

TEST_CASE("parseHexCodePointTest") {
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

TEST_CASE("parseOctCharTest") {
  // good
  REQUIRE(00 == parseOctChar('0'));
  REQUIRE(01 == parseOctChar('1'));
  REQUIRE(02 == parseOctChar('2'));
  REQUIRE(03 == parseOctChar('3'));
  REQUIRE(04 == parseOctChar('4'));
  REQUIRE(05 == parseOctChar('5'));
  REQUIRE(06 == parseOctChar('6'));
  REQUIRE(07 == parseOctChar('7'));

  // bad
  for (int i = -10; i < '0'; ++i) {
    REQUIRE(-1 == parseOctChar(i));
  }

  for (int i = '8'; i < 300; ++i) {
    REQUIRE(-1 == parseOctChar(i));
  }
}

TEST_CASE("parseOctByteTest") {
  fixture(parseOctByte<SItr>, "0",      00,  1);
  fixture(parseOctByte<SItr>, "01",     01,  2);
  fixture(parseOctByte<SItr>, "01a",    01,  2);
  fixture(parseOctByte<SItr>, "0a1",    00,  1);
  fixture(parseOctByte<SItr>, "000",    00,  3);
  fixture(parseOctByte<SItr>, "0001",   00,  3);
  fixture(parseOctByte<SItr>, "377",  0377,  3);
  fixture(parseOctByte<SItr>, "400",    -1, -1); // > 377 is multi-byte
}

TEST_CASE("parseNamedCodePointNumberTest") {
  fixture(parseNamedCodePoint<SItr>, "{U+BEEF}", 0xBEEF, 8);
  fixture(parseNamedCodePoint<SItr>, "{U+10FFFF}", 0x10FFFF, 10);
  fixture(parseNamedCodePoint<SItr>, "{U+0}", 0x0, 5);
  fixture(parseNamedCodePoint<SItr>, "{U+123}stuff", 0x123, 7);
  fixture(parseNamedCodePoint<SItr>, "{U+FFFFFFF}", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "{U+bogus}", -1, -1);
}

TEST_CASE("parseNamedCodePointNameTest") {
  fixture(parseNamedCodePoint<SItr>, "{LATIN CAPITAL LETTER A}", 'A', 24);
  fixture(parseNamedCodePoint<SItr>, "{CYRILLIC SMALL LETTER DOUBLE MONOCULAR O}", 0xA66D, 42);
  fixture(parseNamedCodePoint<SItr>, "{PILE OF POO}", 0x1F4A9, 13);
  fixture(parseNamedCodePoint<SItr>, "{LATIN SMALL LETTER L WITH KICKSTAND}", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "{bogus", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "bogus", -1, -1);
  fixture(parseNamedCodePoint<SItr>, "{}", -1, -1);
}

template <typename T, bool Func(UnicodeSet&)>
void desensitizer(std::initializer_list<T> in,
                  std::initializer_list<T> out)
{
  // I am un chien andalusia
  // wanna grow up to be a desensitizer
  UnicodeSet aset(in);

  // true is returned iff in != out
  REQUIRE((in.size() != out.size()) == Func(aset));

  // actual out should equal expected out
  UnicodeSet eset(out);
  REQUIRE(eset == aset);
}

TEST_CASE("caseDesensitize_a_Test") {
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'a' }, { 'A', 'a' });
}

TEST_CASE("caseDesensitize_A_Test") {
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'A' }, { 'A', 'a' });
}

TEST_CASE("caseDesensitize_DollarSign_Test") {
  desensitizer<uint32_t, caseDesensitizeUnicode>({ '$' }, { '$' });
}

TEST_CASE("caseDesensitize_s_Test") {
  // 0x17F ſ = LATIN SMALL LETTER LONG S
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 's' }, { 'S', 's', U'ſ' });
}

TEST_CASE("caseDesensitize_S_Test") {
  // 0x17F ſ = LATIN SMALL LETTER LONG S
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'S' }, { 'S', 's', U'ſ' });
}

TEST_CASE("caseDesensitize_k_Test") {
  // 0x212A KELVIN SIGN looks exactly like LATIN CAPITAL LETTER K
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'k' }, { 'K', 'k', 0x212A });
}

TEST_CASE("caseDesensitize_K_Test") {
  // 0x212A KELVIN SIGN looks exactly like LATIN CAPITAL LETTER K
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'K' }, { 'K', 'k', 0x212A });
}

TEST_CASE("caseDesensitize_a_to_z_Test") {
  desensitizer<UnicodeSet::range, caseDesensitizeUnicode>(
    { {'a', 'z' + 1} },
    {
      {'A', 'Z' + 1},
      {'a', 'z' + 1},
      {0x17F, 0x180},  // LATIN SMALL LETTER LONG S
      {0x212A, 0x212B} // KELVIN SIGN
    }
  );
}

TEST_CASE("caseDesensitize_A_to_Z_Test") {
  desensitizer<UnicodeSet::range, caseDesensitizeUnicode>(
    { {'A', 'Z' + 1} },
    {
      {'A', 'Z' + 1},
      {'a', 'z' + 1},
      {0x17F, 0x180},  // LATIN SMALL LETTER LONG S
      {0x212A, 0x212B} // KELVIN SIGN
    }
  );
}

TEST_CASE("caseDesensitizeAscii_a_Test") {
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'a' }, { 'A', 'a' });
}

TEST_CASE("caseDesensitizeAscii_A_Test") {
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'A' }, { 'A', 'a' });
}

TEST_CASE("caseDesensitizeAscii_DollarSign_Test") {
  desensitizer<uint32_t, caseDesensitizeAscii>({ '$' }, { '$' });
}

TEST_CASE("caseDesensitizeAscii_s_Test") {
  // No medial s
  desensitizer<uint32_t, caseDesensitizeAscii>({ 's' }, { 'S', 's' });
}

TEST_CASE("caseDesensitizeAscii_S_Test") {
  // No medial s
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'S' }, { 'S', 's' });
}

TEST_CASE("caseDesensitizeAscii_k_Test") {
  // No Kelvin sign
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'k' }, { 'K', 'k' });
}

TEST_CASE("caseDesensitizeAscii_K_Test") {
  // No Kelvin sign
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'K' }, { 'K', 'k' });
}

TEST_CASE("caseDesensitizeAscii_a_to_z_Test") {
  desensitizer<UnicodeSet::range, caseDesensitizeAscii>(
    { {'a', 'z' + 1} },
    {
      {'A', 'Z' + 1},
      {'a', 'z' + 1},
    }
  );
}

TEST_CASE("caseDesensitizeAscii_A_to_Z_Test") {
  desensitizer<UnicodeSet::range, caseDesensitizeAscii>(
    { {'A', 'Z' + 1} },
    {
      {'A', 'Z' + 1},
      {'a', 'z' + 1},
    }
  );
}

TEST_CASE("caseDesensitize_Sigma_Test") {
  // NB: ς is the version of σ which ends words in Greek
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'Σ' },
    {
      U'Σ', // GREEK CAPITAL LETTER SIGMA
      U'σ', // GREEK SMALL LETTER SIGMA
      U'ς'  // GREEK SMALL LETTER FINAL SIGMA
    }
  );
}

TEST_CASE("caseDesensitize_sigma_Test") {
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'σ' },
    {
      U'Σ', // GREEK CAPITAL LETTER SIGMA
      U'σ', // GREEK SMALL LETTER SIGMA
      U'ς'  // GREEK SMALL LETTER FINAL SIGMA
    }
  );
}

TEST_CASE("caseDesensitize_final_sigma_Test") {
  // NB: ς is the version of σ which ends words in Greek.
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'ς' },
    {
      U'Σ', // GREEK CAPITAL LETTER SIGMA
      U'σ', // GREEK SMALL LETTER SIGMA
      U'ς'  // GREEK SMALL LETTER FINAL SIGMA
    }
  );
}

TEST_CASE("caseDesensitize_eszett_Test") {
  // NB: For UTS #18 Level 2 conformance, ß must also match SS.
  // See also Section 5.18 of the Unicode Standard for a discussion
  // of the Eszett.
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'ß' },
    {
      U'ß', // LATIN SMALL LETTER SHARP S
      U'ẞ', // LATIN CAPITAL LETTER SHARP S
    }
  );
}

TEST_CASE("caseDesensitize_Eszett_Test") {
  // NB: For UTS #18 Level 2 conformance, ß must also match SS.
  // See also Section 5.18 of the Unicode Standard for a discussion
  // of the Eszett.
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'ẞ' },
    {
      U'ß', // LATIN SMALL LETTER SHARP S
      U'ẞ', // LATIN CAPITAL LETTER SHARP S
    }
  );
}

TEST_CASE("caseDesensitize_dz_digraph_Test") {
  // NB: Dz is a titlecase version of the dz and DZ digraphs used in
  // various Slavic languages written in the Latin alphabet.
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'ǳ' },
    {
      U'ǳ', // LATIN SMALL LETTER DZ
      U'Ǳ', // LATIN CAPITAL LETTER DZ
      U'ǲ', // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
    }
  );
}

TEST_CASE("caseDesensitize_DZ_digraph_Test") {
  // NB: Dz is a titlecase version of the dz and DZ digraphs used in
  // various Slavic languages written in the Latin alphabet.
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'Ǳ' },
    {
      U'ǳ', // LATIN SMALL LETTER DZ
      U'Ǳ', // LATIN CAPITAL LETTER DZ
      U'ǲ', // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
    }
  );
}

TEST_CASE("caseDesensitize_Dz_digraph_Test") {
  // NB: Dz is a titlecase version of the dz and DZ digraphs used in
  // various Slavic languages written in the Latin alphabet.
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'ǲ' },
    {
      U'ǳ', // LATIN SMALL LETTER DZ
      U'Ǳ', // LATIN CAPITAL LETTER DZ
      U'ǲ', // LATIN CAPITAL LETTER D WITH SMALL LETTER Z
    }
  );
}

TEST_CASE("caseDesensitize_mixed_Test") {
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { 's', U'Ω', U'φ' },
    {
      'S',
      's',
      U'ſ',  // LATIN SMALL LETTER LONG S
      U'Φ',  // GREEK CAPITAL LETTER PHI
      U'φ',  // GREEK SMALL LETTER PHI
      U'Ω',  // GREEK CAPITAL LETTER OMEGA
      U'ω',  // GREEK SMALL LETTER OMEGA
      0x3D5, // GREEK PHI SYMBOL
      0x2126 // OHM SIGN
    }
  );
}

TEST_CASE("caseDesensitizeAscii_mixed_Test") {
  // NB: We do not get the medial S here due to case folding, but we DO
  // get the math phi and Ohm sign, as we're clipping ASCII case folding
  // to the ASCII range but leaving non-ASCII case folding unchanged
  desensitizer<uint32_t, caseDesensitizeAscii>(
    { 's', U'Ω', U'φ' },
    {
      'S',
      's',
      U'Φ',  // GREEK CAPITAL LETTER PHI
      U'φ',  // GREEK SMALL LETTER PHI
      U'Ω',  // GREEK CAPITAL LETTER OMEGA
      U'ω',  // GREEK SMALL LETTER OMEGA
      0x3D5, // GREEK PHI SYMBOL
      0x2126 // OHM SIGN
    }
  );
}

TEST_CASE("setDigitClass_Ascii_Test") {
  UnicodeSet aset;
  setDigitClass(aset, true);
  const UnicodeSet eset('0', '9' + 1);
  REQUIRE(eset == aset);
}

TEST_CASE("setDigitClass_Unicode_Test") {
  UnicodeSet aset;
  setDigitClass(aset, false);
  REQUIRE(DIGIT == aset);
}

TEST_CASE("setSpaceClass_Ascii_Test") {
  UnicodeSet aset;
  setSpaceClass(aset, true);
  const UnicodeSet eset({'\t', '\n', '\v', '\f', '\r', ' '});
  REQUIRE(eset == aset);
}

TEST_CASE("setHorizontalSpaceClass_Test") {
  UnicodeSet aset;
  setHorizontalSpaceClass(aset);
  REQUIRE(HSPACE == aset);
}

TEST_CASE("setVerticalSpaceClass_Test") {
  UnicodeSet aset;
  setVerticalSpaceClass(aset);
  REQUIRE(VSPACE == aset);
}

TEST_CASE("Z_subset_hv_Test") {
  // Sanity check
  // \p{Z} subset of [\h\v]
  UnicodeSet z;
  propertyGetter("\\p{Z}", z, false);
  REQUIRE((HSPACE | VSPACE) == (HSPACE | VSPACE | z));
}

TEST_CASE("setSpaceClass_Unicode_Test") {
  UnicodeSet aset;
  setSpaceClass(aset, false);

  // pcrepattern(3): \s = [\p{Z}\h\v]
  // presently [\v\h] is a superset of \p{Z}, so including \p{Z} is superfluous
  // SPACE = HSPACE | VSPACE
  REQUIRE(SPACE == aset);
}

TEST_CASE("setWordClass_Ascii_Test") {
  UnicodeSet aset;
  setWordClass(aset, true);
  const UnicodeSet eset({
    {'A', 'Z' + 1},
    {'a', 'z' + 1},
    {'0', '9' + 1},
    {'_', '_' + 1}
  });
  REQUIRE(eset == aset);
}

TEST_CASE("NdNlNo_Equals_N_Test") {
  // Sanity check
  // \p{N} = [\p{Nd}\p{Nl}\p{No}]
  UnicodeSet nd;
  propertyGetter("\\p{Nd}", nd, false);
  UnicodeSet nl;
  propertyGetter("\\p{Nl}", nl, false);
  UnicodeSet no;
  propertyGetter("\\p{No}", no, false);
  UnicodeSet n;
  propertyGetter("\\p{N}", n, false);
  REQUIRE((nd | nl | no) == n);
}

TEST_CASE("LuLlLtLmLo_Equals_L_Test") {
  // Sanity check
  // \p{L} = [\p{Lu}\p{Ll}\p{Lt}\p{Lm}\p{Lo}]
  UnicodeSet lu;
  propertyGetter("\\p{Lu}", lu, false);
  UnicodeSet ll;
  propertyGetter("\\p{Ll}", ll, false);
  UnicodeSet lt;
  propertyGetter("\\p{Lt}", lt, false);
  UnicodeSet lm;
  propertyGetter("\\p{Lm}", lm, false);
  UnicodeSet lo;
  propertyGetter("\\p{Lo}", lo, false);
  UnicodeSet l;
  propertyGetter("\\p{L}", l, false);
  REQUIRE((lu | ll | lt | lm | lo) == l);
}

TEST_CASE("setWordClass_Unicode_Test") {
  UnicodeSet aset;
  setWordClass(aset, false);
  REQUIRE(WORD == aset);
}
