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

#include <initializer_list>
#include <iomanip>
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

template <typename T, bool Func(UnicodeSet&)>
void desensitizer(std::initializer_list<T> in,
                  std::initializer_list<T> out)
{
  // I am un chien andalusia
  // wanna grow up to be a desensitizer
  UnicodeSet aset(in);

  // true is returned iff in != out
  SCOPE_ASSERT_EQUAL(in.size() != out.size(), Func(aset));

  // actual out should equal expected out
  UnicodeSet eset(out);
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(caseDesensitize_a_Test) {
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'a' }, { 'A', 'a' });
}

SCOPE_TEST(caseDesensitize_A_Test) {
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'A' }, { 'A', 'a' });
}

SCOPE_TEST(caseDesensitize_DollarSign_Test) {
  desensitizer<uint32_t, caseDesensitizeUnicode>({ '$' }, { '$' });
}

SCOPE_TEST(caseDesensitize_s_Test) {
  // 0x17F ſ = LATIN SMALL LETTER LONG S
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 's' }, { 'S', 's', U'ſ' });
}

SCOPE_TEST(caseDesensitize_S_Test) {
  // 0x17F ſ = LATIN SMALL LETTER LONG S
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'S' }, { 'S', 's', U'ſ' });
}

SCOPE_TEST(caseDesensitize_k_Test) {
  // 0x212A KELVIN SIGN looks exactly like LATIN CAPITAL LETTER K
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'k' }, { 'K', 'k', 0x212A });
}

SCOPE_TEST(caseDesensitize_K_Test) {
  // 0x212A KELVIN SIGN looks exactly like LATIN CAPITAL LETTER K
  desensitizer<uint32_t, caseDesensitizeUnicode>({ 'K' }, { 'K', 'k', 0x212A });
}

SCOPE_TEST(caseDesensitize_a_to_z_Test) {
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

SCOPE_TEST(caseDesensitize_A_to_Z_Test) {
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

SCOPE_TEST(caseDesensitizeAscii_a_Test) {
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'a' }, { 'A', 'a' });
}

SCOPE_TEST(caseDesensitizeAscii_A_Test) {
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'A' }, { 'A', 'a' });
}

SCOPE_TEST(caseDesensitizeAscii_DollarSign_Test) {
  desensitizer<uint32_t, caseDesensitizeAscii>({ '$' }, { '$' });
}

SCOPE_TEST(caseDesensitizeAscii_s_Test) {
  // No medial s
  desensitizer<uint32_t, caseDesensitizeAscii>({ 's' }, { 'S', 's' });
}

SCOPE_TEST(caseDesensitizeAscii_S_Test) {
  // No medial s
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'S' }, { 'S', 's' });
}

SCOPE_TEST(caseDesensitizeAscii_k_Test) {
  // No Kelvin sign
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'k' }, { 'K', 'k' });
}

SCOPE_TEST(caseDesensitizeAscii_K_Test) {
  // No Kelvin sign
  desensitizer<uint32_t, caseDesensitizeAscii>({ 'K' }, { 'K', 'k' });
}

SCOPE_TEST(caseDesensitizeAscii_a_to_z_Test) {
  desensitizer<UnicodeSet::range, caseDesensitizeAscii>(
    { {'a', 'z' + 1} },
    {
      {'A', 'Z' + 1},
      {'a', 'z' + 1},
    }
  );
}

SCOPE_TEST(caseDesensitizeAscii_A_to_Z_Test) {
  desensitizer<UnicodeSet::range, caseDesensitizeAscii>(
    { {'A', 'Z' + 1} },
    {
      {'A', 'Z' + 1},
      {'a', 'z' + 1},
    }
  );
}

SCOPE_TEST(caseDesensitize_Sigma_Test) {
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

SCOPE_TEST(caseDesensitize_sigma_Test) {
  desensitizer<uint32_t, caseDesensitizeUnicode>(
    { U'σ' },
    {
      U'Σ', // GREEK CAPITAL LETTER SIGMA
      U'σ', // GREEK SMALL LETTER SIGMA
      U'ς'  // GREEK SMALL LETTER FINAL SIGMA
    }
  );
}

SCOPE_TEST(caseDesensitize_final_sigma_Test) {
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

SCOPE_TEST(caseDesensitize_eszett_Test) {
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

SCOPE_TEST(caseDesensitize_Eszett_Test) {
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

SCOPE_TEST(caseDesensitize_dz_digraph_Test) {
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

SCOPE_TEST(caseDesensitize_DZ_digraph_Test) {
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

SCOPE_TEST(caseDesensitize_Dz_digraph_Test) {
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

SCOPE_TEST(caseDesensitize_mixed_Test) {
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

SCOPE_TEST(caseDesensitizeAscii_mixed_Test) {
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

SCOPE_TEST(setDigitClass_Ascii_Test) {
  UnicodeSet aset;
  setDigitClass(aset, true);
  const UnicodeSet eset('0', '9' + 1);
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(setDigitClass_Unicode_Test) {
  UnicodeSet aset;
  setDigitClass(aset, false);

  // NB: This list may expand as more blocks are added to Unicode
  const UnicodeSet eset({
    {'0', '9' + 1},
    {0x0660, 0x066a}, // ARABIC-INDIC DIGITS
    {0x06F0, 0x06FA}, // EXTENDED ARABIC-INDIC DIGITS
    {0x07C0, 0x07CA}, // NKO DIGITS
    {0x0966, 0x0970}, // DEVANAGARI DIGITS
    {0x09E6, 0x09F0}, // BENGALI DIGITS
    {0x0A66, 0x0A70}, // GURMUKHI DIGITS
    {0x0AE6, 0x0AF0}, // GUJARATI DIGITS
    {0x0B66, 0x0B70}, // ORIYA DIGITS
    {0x0BE6, 0x0BF0}, // TAMIL DIGITS
    {0x0C66, 0x0C70}, // TELUGU DIGITS
    {0x0CE6, 0x0CF0}, // KANNADA DIGITS
    {0x0D66, 0x0D70}, // MALAYALAM DIGITS
    {0x0DE6, 0x0DF0}, // SINHALA LITH DIGITS
    {0x0E50, 0x0E5A}, // THAI DIGITS
    {0x0ED0, 0X0EDA}, // LAO DIGITS
    {0x0F20, 0x0F2A}, // TIBETAN DIGITS
    {0x1040, 0x104A}, // MYANMAR DIGITS
    {0x1090, 0x109A}, // MYANMAR SHAN DIGITS
    {0x17E0, 0x17EA}, // KHMER DIGITS
    {0x1810, 0x181A}, // MONGOLIAN DIGITS
    {0x1946, 0x1950}, // LIMBU DIGITS
    {0x19D0, 0x19DA}, // NEW TAI LUE DIGITS
    {0x1A80, 0x1A8A}, // TAI THAM HORA DIGITS
    {0x1A90, 0x1A9A}, // TAI THAM THAM DIGITS
    {0x1B50, 0x1B5A}, // BALINESE DIGITS
    {0x1BB0, 0x1BBA}, // SUNDANESE DIGITS
    {0x1C40, 0x1C4A}, // LEPCHA DIGITS
    {0x1C50, 0x1C5A}, // OL CHIKI DIGITS
    {0xA620, 0xA62A}, // VAI DIGITS
    {0xA8D0, 0xA8DA}, // SAURASHTRA DIGITS
    {0xA900, 0xA90A}, // KAYAH LI DIGITS
    {0xA9D0, 0xA9DA}, // JAVANESE DIGITS
    {0xA9F0, 0xA9FA}, // MYANMAR TAI LAING DIGITS
    {0xAA50, 0xAA5A}, // CHAM DIGITS
    {0xABF0, 0xABFA}, // MEETEI MAYEK DIGITS
    {0xFF10, 0xFF1A}, // FULLWIDTH DIGITS
    {0x104A0, 0x104AA}, // OSMANYA DIGITS
    {0x11066, 0x11070}, // BRAHMI DIGITS
    {0x110F0, 0x110FA}, // SORA SOMPENG DIGITS
    {0x11136, 0x11140}, // CHAKMA DIGITS
    {0x111D0, 0x111DA}, // SHARADA DIGITS
    {0x112F0, 0x112FA}, // KHUDAWADI DIGITS
    {0x114D0, 0x114DA}, // TIRHUTA DIGITS
    {0x11650, 0x1165A}, // MODI DIGITS
    {0x116C0, 0x116CA}, // TAKRI DIGITS
    {0x11730, 0x1173A}, // AHOM DIGITS
    {0x118E0, 0x118EA}, // WARANG CITI DIGITS
    {0x16A60, 0x16A6A}, // MRO DIGITS
    {0x16B50, 0x16B5A}, // PAHAWH HMONG DIGITS
    {0x1D7CE, 0x1D800}  // MATHEMATICAL DIGITS
  });
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(setSpaceClass_Ascii_Test) {
  UnicodeSet aset;
  setSpaceClass(aset, true);
  const UnicodeSet eset({'\t', '\n', '\v', '\f', '\r', ' '});
  SCOPE_ASSERT_EQUAL(eset, aset);
}

// horizontal space characters (matched by \h)
const UnicodeSet HSPACE({
  '\t',
  ' ',
  0xA0,   // NO-BREAK SPACE
  0x1680, // OGHAM SPACE MARK
  0x180E, // MONGOLIAN VOWEL SEPARATOR
  0x2000, // EN QUAD
  0x2001, // EM QUAD
  0x2002, // EN SPACE
  0x2003, // EM SPACE
  0x2004, // THREE-PER-EM SPACE
  0x2005, // FOUR-PER-EM SPACE
  0x2006, // SIX-PER-EM SPACE
  0x2007, // FIGURE SPACE
  0x2008, // PUNCTUATION SPACE
  0x2009, // THIN SPACE
  0x200A, // HAIR SPACE
  0x202F, // NARROW NO-BREAK SPACE
  0x205F, // MEDIUM MATHEMATICAL SPACE
  0x3000  // IDEOGRAPHIC SPACE
});

// vertical space characters (matched by \v)
const UnicodeSet VSPACE({
  '\n',
  '\v',    // NB: \v the ASCII escape != \v the character class
  '\f',
  '\r',
  0x85,   // NEXT LINE
  0x2028, // LINE SEPARATOR
  0x2029, // PARAGRAPH SEPARATOR
});

SCOPE_TEST(setHorizontalSpaceClass_Test) {
  UnicodeSet aset;
  setHorizontalSpaceClass(aset);
  SCOPE_ASSERT_EQUAL(HSPACE, aset);
}

SCOPE_TEST(setVerticalSpaceClass_Test) {
  UnicodeSet aset;
  setVerticalSpaceClass(aset);
  SCOPE_ASSERT_EQUAL(VSPACE, aset);
}

SCOPE_TEST(Z_subset_hv_Test) {
  // Sanity check
  // \p{Z} subset of [\h\v]
  UnicodeSet z;
  propertyGetter("\\p{Z}", z);
  SCOPE_ASSERT_EQUAL(HSPACE | VSPACE, HSPACE | VSPACE | z);
}

SCOPE_TEST(setSpaceClass_Unicode_Test) {
  UnicodeSet aset;
  setSpaceClass(aset, false);

  // pcrepattern(3): \s = [\p{Z}\h\v]
  // presently [\v\h] is a superset of \p{Z}, so including \p{Z} is superfluous
  const UnicodeSet eset = HSPACE | VSPACE;
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(setWordClass_Ascii_Test) {
  UnicodeSet aset;
  setWordClass(aset, true);
  const UnicodeSet eset({
    {'A', 'Z' + 1},
    {'a', 'z' + 1},
    {'0', '9' + 1},
    {'_', '_' + 1}
  });
  SCOPE_ASSERT_EQUAL(eset, aset);
}

SCOPE_TEST(NdNlNo_Equals_N_Test) {
  // Sanity check
  // \p{N} = [\p{Nd}\p{Nl}\p{No}]
  UnicodeSet nd;
  propertyGetter("\\p{Nd}", nd);
  UnicodeSet nl;
  propertyGetter("\\p{Nl}", nl);
  UnicodeSet no;
  propertyGetter("\\p{No}", no);
  UnicodeSet n;
  propertyGetter("\\p{N}", n);
  SCOPE_ASSERT_EQUAL(nd | nl | no, n);
}

SCOPE_TEST(LuLlLtLmLo_Equals_L_Test) {
  // Sanity check
  // \p{L} = [\p{Lu}\p{Ll}\p{Lt}\p{Lm}\p{Lo}]
  UnicodeSet lu;
  propertyGetter("\\p{Lu}", lu);
  UnicodeSet ll;
  propertyGetter("\\p{Ll}", ll);
  UnicodeSet lt;
  propertyGetter("\\p{Lt}", lt);
  UnicodeSet lm;
  propertyGetter("\\p{Lm}", lm);
  UnicodeSet lo;
  propertyGetter("\\p{Lo}", lo);
  UnicodeSet l;
  propertyGetter("\\p{L}", l);
  SCOPE_ASSERT_EQUAL(lu | ll | lt | lm | lo, l);
}

SCOPE_TEST(setWordClass_Unicode_Test) {
  UnicodeSet aset;
  setWordClass(aset, false);

  // NB: This list may expand as more blocks are added to Unicode
  const UnicodeSet eset({
    {0x30, 0x3A},
    {0x41, 0x5B},
    {0x5F, 0x60},
    {0x61, 0x7B},
    {0xAA, 0xAB},
    {0xB2, 0xB4},
    {0xB5, 0xB6},
    {0xB9, 0xBB},
    {0xBC, 0xBF},
    {0xC0, 0xD7},
    {0xD8, 0xF7},
    {0xF8, 0x2C2},
    {0x2C6, 0x2D2},
    {0x2E0, 0x2E5},
    {0x2EC, 0x2ED},
    {0x2EE, 0x2EF},
    {0x370, 0x375},
    {0x376, 0x378},
    {0x37A, 0x37E},
    {0x37F, 0x380},
    {0x386, 0x387},
    {0x388, 0x38B},
    {0x38C, 0x38D},
    {0x38E, 0x3A2},
    {0x3A3, 0x3F6},
    {0x3F7, 0x482},
    {0x48A, 0x530},
    {0x531, 0x557},
    {0x559, 0x55A},
    {0x561, 0x588},
    {0x5D0, 0x5EB},
    {0x5F0, 0x5F3},
    {0x620, 0x64B},
    {0x660, 0x66A},
    {0x66E, 0x670},
    {0x671, 0x6D4},
    {0x6D5, 0x6D6},
    {0x6E5, 0x6E7},
    {0x6EE, 0x6FD},
    {0x6FF, 0x700},
    {0x710, 0x711},
    {0x712, 0x730},
    {0x74D, 0x7A6},
    {0x7B1, 0x7B2},
    {0x7C0, 0x7EB},
    {0x7F4, 0x7F6},
    {0x7FA, 0x7FB},
    {0x800, 0x816},
    {0x81A, 0x81B},
    {0x824, 0x825},
    {0x828, 0x829},
    {0x840, 0x859},
    {0x8A0, 0x8B5},
    {0x904, 0x93A},
    {0x93D, 0x93E},
    {0x950, 0x951},
    {0x958, 0x962},
    {0x966, 0x970},
    {0x971, 0x981},
    {0x985, 0x98D},
    {0x98F, 0x991},
    {0x993, 0x9A9},
    {0x9AA, 0x9B1},
    {0x9B2, 0x9B3},
    {0x9B6, 0x9BA},
    {0x9BD, 0x9BE},
    {0x9CE, 0x9CF},
    {0x9DC, 0x9DE},
    {0x9DF, 0x9E2},
    {0x9E6, 0x9F2},
    {0x9F4, 0x9FA},
    {0xA05, 0xA0B},
    {0xA0F, 0xA11},
    {0xA13, 0xA29},
    {0xA2A, 0xA31},
    {0xA32, 0xA34},
    {0xA35, 0xA37},
    {0xA38, 0xA3A},
    {0xA59, 0xA5D},
    {0xA5E, 0xA5F},
    {0xA66, 0xA70},
    {0xA72, 0xA75},
    {0xA85, 0xA8E},
    {0xA8F, 0xA92},
    {0xA93, 0xAA9},
    {0xAAA, 0xAB1},
    {0xAB2, 0xAB4},
    {0xAB5, 0xABA},
    {0xABD, 0xABE},
    {0xAD0, 0xAD1},
    {0xAE0, 0xAE2},
    {0xAE6, 0xAF0},
    {0xAF9, 0xAFA},
    {0xB05, 0xB0D},
    {0xB0F, 0xB11},
    {0xB13, 0xB29},
    {0xB2A, 0xB31},
    {0xB32, 0xB34},
    {0xB35, 0xB3A},
    {0xB3D, 0xB3E},
    {0xB5C, 0xB5E},
    {0xB5F, 0xB62},
    {0xB66, 0xB70},
    {0xB71, 0xB78},
    {0xB83, 0xB84},
    {0xB85, 0xB8B},
    {0xB8E, 0xB91},
    {0xB92, 0xB96},
    {0xB99, 0xB9B},
    {0xB9C, 0xB9D},
    {0xB9E, 0xBA0},
    {0xBA3, 0xBA5},
    {0xBA8, 0xBAB},
    {0xBAE, 0xBBA},
    {0xBD0, 0xBD1},
    {0xBE6, 0xBF3},
    {0xC05, 0xC0D},
    {0xC0E, 0xC11},
    {0xC12, 0xC29},
    {0xC2A, 0xC3A},
    {0xC3D, 0xC3E},
    {0xC58, 0xC5B},
    {0xC60, 0xC62},
    {0xC66, 0xC70},
    {0xC78, 0xC7F},
    {0xC85, 0xC8D},
    {0xC8E, 0xC91},
    {0xC92, 0xCA9},
    {0xCAA, 0xCB4},
    {0xCB5, 0xCBA},
    {0xCBD, 0xCBE},
    {0xCDE, 0xCDF},
    {0xCE0, 0xCE2},
    {0xCE6, 0xCF0},
    {0xCF1, 0xCF3},
    {0xD05, 0xD0D},
    {0xD0E, 0xD11},
    {0xD12, 0xD3B},
    {0xD3D, 0xD3E},
    {0xD4E, 0xD4F},
    {0xD5F, 0xD62},
    {0xD66, 0xD76},
    {0xD7A, 0xD80},
    {0xD85, 0xD97},
    {0xD9A, 0xDB2},
    {0xDB3, 0xDBC},
    {0xDBD, 0xDBE},
    {0xDC0, 0xDC7},
    {0xDE6, 0xDF0},
    {0xE01, 0xE31},
    {0xE32, 0xE34},
    {0xE40, 0xE47},
    {0xE50, 0xE5A},
    {0xE81, 0xE83},
    {0xE84, 0xE85},
    {0xE87, 0xE89},
    {0xE8A, 0xE8B},
    {0xE8D, 0xE8E},
    {0xE94, 0xE98},
    {0xE99, 0xEA0},
    {0xEA1, 0xEA4},
    {0xEA5, 0xEA6},
    {0xEA7, 0xEA8},
    {0xEAA, 0xEAC},
    {0xEAD, 0xEB1},
    {0xEB2, 0xEB4},
    {0xEBD, 0xEBE},
    {0xEC0, 0xEC5},
    {0xEC6, 0xEC7},
    {0xED0, 0xEDA},
    {0xEDC, 0xEE0},
    {0xF00, 0xF01},
    {0xF20, 0xF34},
    {0xF40, 0xF48},
    {0xF49, 0xF6D},
    {0xF88, 0xF8D},
    {0x1000, 0x102B},
    {0x103F, 0x104A},
    {0x1050, 0x1056},
    {0x105A, 0x105E},
    {0x1061, 0x1062},
    {0x1065, 0x1067},
    {0x106E, 0x1071},
    {0x1075, 0x1082},
    {0x108E, 0x108F},
    {0x1090, 0x109A},
    {0x10A0, 0x10C6},
    {0x10C7, 0x10C8},
    {0x10CD, 0x10CE},
    {0x10D0, 0x10FB},
    {0x10FC, 0x1249},
    {0x124A, 0x124E},
    {0x1250, 0x1257},
    {0x1258, 0x1259},
    {0x125A, 0x125E},
    {0x1260, 0x1289},
    {0x128A, 0x128E},
    {0x1290, 0x12B1},
    {0x12B2, 0x12B6},
    {0x12B8, 0x12BF},
    {0x12C0, 0x12C1},
    {0x12C2, 0x12C6},
    {0x12C8, 0x12D7},
    {0x12D8, 0x1311},
    {0x1312, 0x1316},
    {0x1318, 0x135B},
    {0x1369, 0x137D},
    {0x1380, 0x1390},
    {0x13A0, 0x13F6},
    {0x13F8, 0x13FE},
    {0x1401, 0x166D},
    {0x166F, 0x1680},
    {0x1681, 0x169B},
    {0x16A0, 0x16EB},
    {0x16EE, 0x16F9},
    {0x1700, 0x170D},
    {0x170E, 0x1712},
    {0x1720, 0x1732},
    {0x1740, 0x1752},
    {0x1760, 0x176D},
    {0x176E, 0x1771},
    {0x1780, 0x17B4},
    {0x17D7, 0x17D8},
    {0x17DC, 0x17DD},
    {0x17E0, 0x17EA},
    {0x17F0, 0x17FA},
    {0x1810, 0x181A},
    {0x1820, 0x1878},
    {0x1880, 0x18A9},
    {0x18AA, 0x18AB},
    {0x18B0, 0x18F6},
    {0x1900, 0x191F},
    {0x1946, 0x196E},
    {0x1970, 0x1975},
    {0x1980, 0x19AC},
    {0x19B0, 0x19CA},
    {0x19D0, 0x19DB},
    {0x1A00, 0x1A17},
    {0x1A20, 0x1A55},
    {0x1A80, 0x1A8A},
    {0x1A90, 0x1A9A},
    {0x1AA7, 0x1AA8},
    {0x1B05, 0x1B34},
    {0x1B45, 0x1B4C},
    {0x1B50, 0x1B5A},
    {0x1B83, 0x1BA1},
    {0x1BAE, 0x1BE6},
    {0x1C00, 0x1C24},
    {0x1C40, 0x1C4A},
    {0x1C4D, 0x1C7E},
    {0x1CE9, 0x1CED},
    {0x1CEE, 0x1CF2},
    {0x1CF5, 0x1CF7},
    {0x1D00, 0x1DC0},
    {0x1E00, 0x1F16},
    {0x1F18, 0x1F1E},
    {0x1F20, 0x1F46},
    {0x1F48, 0x1F4E},
    {0x1F50, 0x1F58},
    {0x1F59, 0x1F5A},
    {0x1F5B, 0x1F5C},
    {0x1F5D, 0x1F5E},
    {0x1F5F, 0x1F7E},
    {0x1F80, 0x1FB5},
    {0x1FB6, 0x1FBD},
    {0x1FBE, 0x1FBF},
    {0x1FC2, 0x1FC5},
    {0x1FC6, 0x1FCD},
    {0x1FD0, 0x1FD4},
    {0x1FD6, 0x1FDC},
    {0x1FE0, 0x1FED},
    {0x1FF2, 0x1FF5},
    {0x1FF6, 0x1FFD},
    {0x2070, 0x2072},
    {0x2074, 0x207A},
    {0x207F, 0x208A},
    {0x2090, 0x209D},
    {0x2102, 0x2103},
    {0x2107, 0x2108},
    {0x210A, 0x2114},
    {0x2115, 0x2116},
    {0x2119, 0x211E},
    {0x2124, 0x2125},
    {0x2126, 0x2127},
    {0x2128, 0x2129},
    {0x212A, 0x212E},
    {0x212F, 0x213A},
    {0x213C, 0x2140},
    {0x2145, 0x214A},
    {0x214E, 0x214F},
    {0x2150, 0x218A},
    {0x2460, 0x249C},
    {0x24EA, 0x2500},
    {0x2776, 0x2794},
    {0x2C00, 0x2C2F},
    {0x2C30, 0x2C5F},
    {0x2C60, 0x2CE5},
    {0x2CEB, 0x2CEF},
    {0x2CF2, 0x2CF4},
    {0x2CFD, 0x2CFE},
    {0x2D00, 0x2D26},
    {0x2D27, 0x2D28},
    {0x2D2D, 0x2D2E},
    {0x2D30, 0x2D68},
    {0x2D6F, 0x2D70},
    {0x2D80, 0x2D97},
    {0x2DA0, 0x2DA7},
    {0x2DA8, 0x2DAF},
    {0x2DB0, 0x2DB7},
    {0x2DB8, 0x2DBF},
    {0x2DC0, 0x2DC7},
    {0x2DC8, 0x2DCF},
    {0x2DD0, 0x2DD7},
    {0x2DD8, 0x2DDF},
    {0x2E2F, 0x2E30},
    {0x3005, 0x3008},
    {0x3021, 0x302A},
    {0x3031, 0x3036},
    {0x3038, 0x303D},
    {0x3041, 0x3097},
    {0x309D, 0x30A0},
    {0x30A1, 0x30FB},
    {0x30FC, 0x3100},
    {0x3105, 0x312E},
    {0x3131, 0x318F},
    {0x3192, 0x3196},
    {0x31A0, 0x31BB},
    {0x31F0, 0x3200},
    {0x3220, 0x322A},
    {0x3248, 0x3250},
    {0x3251, 0x3260},
    {0x3280, 0x328A},
    {0x32B1, 0x32C0},
    {0x3400, 0x4DB6},
    {0x4E00, 0x9FD6},
    {0xA000, 0xA48D},
    {0xA4D0, 0xA4FE},
    {0xA500, 0xA60D},
    {0xA610, 0xA62C},
    {0xA640, 0xA66F},
    {0xA67F, 0xA69E},
    {0xA6A0, 0xA6F0},
    {0xA717, 0xA720},
    {0xA722, 0xA789},
    {0xA78B, 0xA7AE},
    {0xA7B0, 0xA7B8},
    {0xA7F7, 0xA802},
    {0xA803, 0xA806},
    {0xA807, 0xA80B},
    {0xA80C, 0xA823},
    {0xA830, 0xA836},
    {0xA840, 0xA874},
    {0xA882, 0xA8B4},
    {0xA8D0, 0xA8DA},
    {0xA8F2, 0xA8F8},
    {0xA8FB, 0xA8FC},
    {0xA8FD, 0xA8FE},
    {0xA900, 0xA926},
    {0xA930, 0xA947},
    {0xA960, 0xA97D},
    {0xA984, 0xA9B3},
    {0xA9CF, 0xA9DA},
    {0xA9E0, 0xA9E5},
    {0xA9E6, 0xA9FF},
    {0xAA00, 0xAA29},
    {0xAA40, 0xAA43},
    {0xAA44, 0xAA4C},
    {0xAA50, 0xAA5A},
    {0xAA60, 0xAA77},
    {0xAA7A, 0xAA7B},
    {0xAA7E, 0xAAB0},
    {0xAAB1, 0xAAB2},
    {0xAAB5, 0xAAB7},
    {0xAAB9, 0xAABE},
    {0xAAC0, 0xAAC1},
    {0xAAC2, 0xAAC3},
    {0xAADB, 0xAADE},
    {0xAAE0, 0xAAEB},
    {0xAAF2, 0xAAF5},
    {0xAB01, 0xAB07},
    {0xAB09, 0xAB0F},
    {0xAB11, 0xAB17},
    {0xAB20, 0xAB27},
    {0xAB28, 0xAB2F},
    {0xAB30, 0xAB5B},
    {0xAB5C, 0xAB66},
    {0xAB70, 0xABE3},
    {0xABF0, 0xABFA},
    {0xAC00, 0xD7A4},
    {0xD7B0, 0xD7C7},
    {0xD7CB, 0xD7FC},
    {0xF900, 0xFA6E},
    {0xFA70, 0xFADA},
    {0xFB00, 0xFB07},
    {0xFB13, 0xFB18},
    {0xFB1D, 0xFB1E},
    {0xFB1F, 0xFB29},
    {0xFB2A, 0xFB37},
    {0xFB38, 0xFB3D},
    {0xFB3E, 0xFB3F},
    {0xFB40, 0xFB42},
    {0xFB43, 0xFB45},
    {0xFB46, 0xFBB2},
    {0xFBD3, 0xFD3E},
    {0xFD50, 0xFD90},
    {0xFD92, 0xFDC8},
    {0xFDF0, 0xFDFC},
    {0xFE70, 0xFE75},
    {0xFE76, 0xFEFD},
    {0xFF10, 0xFF1A},
    {0xFF21, 0xFF3B},
    {0xFF41, 0xFF5B},
    {0xFF66, 0xFFBF},
    {0xFFC2, 0xFFC8},
    {0xFFCA, 0xFFD0},
    {0xFFD2, 0xFFD8},
    {0xFFDA, 0xFFDD},
    {0x10000, 0x1000C},
    {0x1000D, 0x10027},
    {0x10028, 0x1003B},
    {0x1003C, 0x1003E},
    {0x1003F, 0x1004E},
    {0x10050, 0x1005E},
    {0x10080, 0x100FB},
    {0x10107, 0x10134},
    {0x10140, 0x10179},
    {0x1018A, 0x1018C},
    {0x10280, 0x1029D},
    {0x102A0, 0x102D1},
    {0x102E1, 0x102FC},
    {0x10300, 0x10324},
    {0x10330, 0x1034B},
    {0x10350, 0x10376},
    {0x10380, 0x1039E},
    {0x103A0, 0x103C4},
    {0x103C8, 0x103D0},
    {0x103D1, 0x103D6},
    {0x10400, 0x1049E},
    {0x104A0, 0x104AA},
    {0x10500, 0x10528},
    {0x10530, 0x10564},
    {0x10600, 0x10737},
    {0x10740, 0x10756},
    {0x10760, 0x10768},
    {0x10800, 0x10806},
    {0x10808, 0x10809},
    {0x1080A, 0x10836},
    {0x10837, 0x10839},
    {0x1083C, 0x1083D},
    {0x1083F, 0x10856},
    {0x10858, 0x10877},
    {0x10879, 0x1089F},
    {0x108A7, 0x108B0},
    {0x108E0, 0x108F3},
    {0x108F4, 0x108F6},
    {0x108FB, 0x1091C},
    {0x10920, 0x1093A},
    {0x10980, 0x109B8},
    {0x109BC, 0x109D0},
    {0x109D2, 0x10A01},
    {0x10A10, 0x10A14},
    {0x10A15, 0x10A18},
    {0x10A19, 0x10A34},
    {0x10A40, 0x10A48},
    {0x10A60, 0x10A7F},
    {0x10A80, 0x10AA0},
    {0x10AC0, 0x10AC8},
    {0x10AC9, 0x10AE5},
    {0x10AEB, 0x10AF0},
    {0x10B00, 0x10B36},
    {0x10B40, 0x10B56},
    {0x10B58, 0x10B73},
    {0x10B78, 0x10B92},
    {0x10BA9, 0x10BB0},
    {0x10C00, 0x10C49},
    {0x10C80, 0x10CB3},
    {0x10CC0, 0x10CF3},
    {0x10CFA, 0x10D00},
    {0x10E60, 0x10E7F},
    {0x11003, 0x11038},
    {0x11052, 0x11070},
    {0x11083, 0x110B0},
    {0x110D0, 0x110E9},
    {0x110F0, 0x110FA},
    {0x11103, 0x11127},
    {0x11136, 0x11140},
    {0x11150, 0x11173},
    {0x11176, 0x11177},
    {0x11183, 0x111B3},
    {0x111C1, 0x111C5},
    {0x111D0, 0x111DB},
    {0x111DC, 0x111DD},
    {0x111E1, 0x111F5},
    {0x11200, 0x11212},
    {0x11213, 0x1122C},
    {0x11280, 0x11287},
    {0x11288, 0x11289},
    {0x1128A, 0x1128E},
    {0x1128F, 0x1129E},
    {0x1129F, 0x112A9},
    {0x112B0, 0x112DF},
    {0x112F0, 0x112FA},
    {0x11305, 0x1130D},
    {0x1130F, 0x11311},
    {0x11313, 0x11329},
    {0x1132A, 0x11331},
    {0x11332, 0x11334},
    {0x11335, 0x1133A},
    {0x1133D, 0x1133E},
    {0x11350, 0x11351},
    {0x1135D, 0x11362},
    {0x11480, 0x114B0},
    {0x114C4, 0x114C6},
    {0x114C7, 0x114C8},
    {0x114D0, 0x114DA},
    {0x11580, 0x115AF},
    {0x115D8, 0x115DC},
    {0x11600, 0x11630},
    {0x11644, 0x11645},
    {0x11650, 0x1165A},
    {0x11680, 0x116AB},
    {0x116C0, 0x116CA},
    {0x11700, 0x1171A},
    {0x11730, 0x1173C},
    {0x118A0, 0x118F3},
    {0x118FF, 0x11900},
    {0x11AC0, 0x11AF9},
    {0x12000, 0x1239A},
    {0x12400, 0x1246F},
    {0x12480, 0x12544},
    {0x13000, 0x1342F},
    {0x14400, 0x14647},
    {0x16800, 0x16A39},
    {0x16A40, 0x16A5F},
    {0x16A60, 0x16A6A},
    {0x16AD0, 0x16AEE},
    {0x16B00, 0x16B30},
    {0x16B40, 0x16B44},
    {0x16B50, 0x16B5A},
    {0x16B5B, 0x16B62},
    {0x16B63, 0x16B78},
    {0x16B7D, 0x16B90},
    {0x16F00, 0x16F45},
    {0x16F50, 0x16F51},
    {0x16F93, 0x16FA0},
    {0x1B000, 0x1B002},
    {0x1BC00, 0x1BC6B},
    {0x1BC70, 0x1BC7D},
    {0x1BC80, 0x1BC89},
    {0x1BC90, 0x1BC9A},
    {0x1D360, 0x1D372},
    {0x1D400, 0x1D455},
    {0x1D456, 0x1D49D},
    {0x1D49E, 0x1D4A0},
    {0x1D4A2, 0x1D4A3},
    {0x1D4A5, 0x1D4A7},
    {0x1D4A9, 0x1D4AD},
    {0x1D4AE, 0x1D4BA},
    {0x1D4BB, 0x1D4BC},
    {0x1D4BD, 0x1D4C4},
    {0x1D4C5, 0x1D506},
    {0x1D507, 0x1D50B},
    {0x1D50D, 0x1D515},
    {0x1D516, 0x1D51D},
    {0x1D51E, 0x1D53A},
    {0x1D53B, 0x1D53F},
    {0x1D540, 0x1D545},
    {0x1D546, 0x1D547},
    {0x1D54A, 0x1D551},
    {0x1D552, 0x1D6A6},
    {0x1D6A8, 0x1D6C1},
    {0x1D6C2, 0x1D6DB},
    {0x1D6DC, 0x1D6FB},
    {0x1D6FC, 0x1D715},
    {0x1D716, 0x1D735},
    {0x1D736, 0x1D74F},
    {0x1D750, 0x1D76F},
    {0x1D770, 0x1D789},
    {0x1D78A, 0x1D7A9},
    {0x1D7AA, 0x1D7C3},
    {0x1D7C4, 0x1D7CC},
    {0x1D7CE, 0x1D800},
    {0x1E800, 0x1E8C5},
    {0x1E8C7, 0x1E8D0},
    {0x1EE00, 0x1EE04},
    {0x1EE05, 0x1EE20},
    {0x1EE21, 0x1EE23},
    {0x1EE24, 0x1EE25},
    {0x1EE27, 0x1EE28},
    {0x1EE29, 0x1EE33},
    {0x1EE34, 0x1EE38},
    {0x1EE39, 0x1EE3A},
    {0x1EE3B, 0x1EE3C},
    {0x1EE42, 0x1EE43},
    {0x1EE47, 0x1EE48},
    {0x1EE49, 0x1EE4A},
    {0x1EE4B, 0x1EE4C},
    {0x1EE4D, 0x1EE50},
    {0x1EE51, 0x1EE53},
    {0x1EE54, 0x1EE55},
    {0x1EE57, 0x1EE58},
    {0x1EE59, 0x1EE5A},
    {0x1EE5B, 0x1EE5C},
    {0x1EE5D, 0x1EE5E},
    {0x1EE5F, 0x1EE60},
    {0x1EE61, 0x1EE63},
    {0x1EE64, 0x1EE65},
    {0x1EE67, 0x1EE6B},
    {0x1EE6C, 0x1EE73},
    {0x1EE74, 0x1EE78},
    {0x1EE79, 0x1EE7D},
    {0x1EE7E, 0x1EE7F},
    {0x1EE80, 0x1EE8A},
    {0x1EE8B, 0x1EE9C},
    {0x1EEA1, 0x1EEA4},
    {0x1EEA5, 0x1EEAA},
    {0x1EEAB, 0x1EEBC},
    {0x1F100, 0x1F10D},
    {0x20000, 0x2A6D7},
    {0x2A700, 0x2B735},
    {0x2B740, 0x2B81E},
    {0x2B820, 0x2CEA2},
    {0x2F800, 0x2FA1E}
  });

  SCOPE_ASSERT_EQUAL(eset, aset);
}
