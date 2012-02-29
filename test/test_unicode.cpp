#include <scope/test.h>

#include <algorithm>
#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <type_traits>

#include "basic.h"
#include "unicode.h"

inline int invalid(int& cp, const byte*) {
  cp = -1;
  return -1;
}

inline int onebyte(int& cp, const byte* begin) {
  cp = *begin;
  return 1;
}

inline int twobyte(int& cp, const byte* begin) {
  cp = ((*begin & 0x1F) << 6) | ((*(begin+1)) & 0x3F);
  return 2;
}

inline int threebyte(int& cp, const byte* begin) {
  cp = ((* begin    & 0x0F) << 12) |
       ((*(begin+1) & 0x3F) <<  6) | (*(begin+2) & 0x3F);
  return 3;
}

inline int fourbyte(int& cp, const byte* begin) {
  cp = ((* begin    & 0x07) << 18) | ((*(begin+1) & 0x3F) << 12) |
       ((*(begin+2) & 0x3F) <<  6) |  (*(begin+3) & 0x3F);
  return 4;
}

inline byte expected_length(byte b) {
  if (b < 0x80) {
    return 1;
  }
  else if (b < 0xE0) {
    return 2;
  }
  else if (b < 0xF0) {
    return 3;
  }
  else {
    return 4;
  } 
}

template <class Expected, class Actual>
void test_single(const byte* b, Expected exp, Actual act) {

  int e_cp, a_cp;
  const int e_consumed = exp(e_cp, b);
  const int a_consumed = act(a_cp, b, b+4);

/*
  if (e_cp != a_cp) {
    std::cout << std::hex << std::setfill('0')
              << std::setw(2) << (uint32) eb[0] << ' '
              << std::setw(2) << (uint32) eb[1] << ' '
              << std::setw(2) << (uint32) eb[2] << ' '
              << std::setw(2) << (uint32) eb[3] << ' '
              << std::setw(8) << (uint32) e     << ' '
              << std::setw(8) << (uint32) a     << ' '
              << std::endl;
  }
*/

  SCOPE_ASSERT_EQUAL(e_consumed, a_consumed);
  SCOPE_ASSERT_EQUAL(e_cp, a_cp);
}

inline uint32 other_endian(uint32 w) {
  return ((w & 0x000000FF) << 24) |
         ((w & 0x0000FF00) <<  8) |
         ((w & 0x00FF0000) >>  8) |
         ((w & 0xFF000000) >> 24);
}

template <class Expected, class Actual>
void test_range(uint32 i, const uint32 end, Expected exp, Actual act) {
  uint32 seq;
  while (i < end) {
    // become big-endian
    seq = other_endian(i);

    const byte* b = reinterpret_cast<byte*>(&seq);
    test_single(b, exp, act);

    // increment the last byte in the sequence
    i += 1 << (8*(4 - expected_length(b[0])));
  }
}

template <uint32 Length, class Expected, class Actual>
typename std::enable_if<
  !std::is_same<typename std::integral_constant<uint32,4>,
                typename std::integral_constant<uint32,Length>>::value>::type
test_range(const byte* first, const byte* last, Expected exp, Actual act)
{
  // mask out right 4-Length bytes
  const uint32 mask = ((1 << (Length*8)) - 1) << ((4-Length)*8);

  uint32 i = other_endian(*reinterpret_cast<const uint32*>(first)) & mask;
  const uint32 end = (other_endian(*reinterpret_cast<const uint32*>(last)) & mask) + (1 << (4-Length)*8);

  test_range(i, end, exp, act);
}

template <uint32 Length, class Expected, class Actual>
typename std::enable_if<
  std::is_same<typename std::integral_constant<uint32,4>,
               typename std::integral_constant<uint32,Length>>::value>::type
test_range(const byte* first, const byte* last, Expected exp, Actual act)
{
  uint32 i = other_endian(*reinterpret_cast<const uint32*>(first));
  const uint32 end = other_endian(*reinterpret_cast<const uint32*>(last));

  if (end == 0xFFFFFFFF) {
    test_range(i, end, exp, act);
    test_single((const byte*) "\xFF\xFF\xFF\xFF", exp, act);
  }
  else {
    test_range(i, end+1, exp, act);
  }
}

template <uint32 Length, class Converter>
void invalid_range(const byte* first, const byte* last, Converter conv) {
  test_range<Length>(first, last, invalid, conv);
}

template <uint32 Length, class Converter>
void invalid_range(const char* first, const char* last, Converter conv) {
  invalid_range<Length>(reinterpret_cast<const byte*>(first),
                        reinterpret_cast<const byte*>(last), conv);
}

template <uint32 Length, class Converter>
typename std::enable_if<
  std::is_same<typename std::integral_constant<uint32,1>,
               typename std::integral_constant<uint32,Length>>::value>::type
valid_range(const byte* first, const byte* last, Converter conv) {
  test_range<Length>(first, last, onebyte, conv);
}

template <uint32 Length, class Converter>
typename std::enable_if<
  std::is_same<typename std::integral_constant<uint32,2>,
               typename std::integral_constant<uint32,Length>>::value>::type
valid_range(const byte* first, const byte* last, Converter conv) {
  test_range<Length>(first, last, twobyte, conv);
}

template <uint32 Length, class Converter>
typename std::enable_if<
  std::is_same<typename std::integral_constant<uint32,3>,
               typename std::integral_constant<uint32,Length>>::value>::type
valid_range(const byte* first, const byte* last, Converter conv) {
  test_range<Length>(first, last, threebyte, conv);
}

template <uint32 Length, class Converter>
typename std::enable_if<
  std::is_same<typename std::integral_constant<uint32,4>,
               typename std::integral_constant<uint32,Length>>::value>::type
valid_range(const byte* first, const byte* last, Converter conv) {
  test_range<Length>(first, last, fourbyte, conv);
}

template <uint32 Length, class Converter>
void valid_range(const char* first, const char* last, Converter conv) {
  valid_range<Length>(reinterpret_cast<const byte*>(first),
                      reinterpret_cast<const byte*>(last), conv);
}

template <uint32 N, uint32 L, class Converter>
struct ContinuationTester {
  void operator()(byte* l, Converter conv) const {
    byte h[4];
    std::copy(l, l+4, h);

    std::fill(l+(L-N), l+4, 0x00);
    h[L-N] = 0x7F;
    std::fill(h+(L-N)+1, h+4, 0xFF);
    invalid_range<L>(l, h, conv);

    ContinuationTester<N-1,L,Converter> t;
    for (l[L-N] = 0x80; l[L-N] < 0xC0; ++l[L-N]) {
      t(l, conv);
    }

    l[L-N] = 0xC0;
    std::fill(l+(L-N)+1, l+4, 0x00);
    std::fill(h+(L-N), h+4, 0xFF);
    invalid_range<L>(l, h, conv);
  }
};

template <uint32 L, class Converter>
struct ContinuationTester<1,L,Converter> {
  void operator()(byte* l, Converter conv) const {
    byte h[4];
    std::copy(l, l+4, h);

    l[L-1] = 0x00;
    h[L-1] = 0x7F;
    invalid_range<L>(l, h, conv);

    l[L-1] = 0x80;
    h[L-1] = 0xBF;
    valid_range<L>(l, h, conv);

    l[L-1] = 0xC0;
    h[L-1] = 0xFF;
    invalid_range<L>(l, h, conv);
  }
};

template <class Converter>
void utf8_to_unicode_tester(Converter conv) {
  byte b[4];

  //
  // [00,80) are valid 1-byte sequences
  //
  valid_range<1>("\x00", "\x7F", conv);

  invalid_range<1>("\x80", "\xBF", conv);           // bad starts

  invalid_range<2>("\xC0\x00", "\xC0\x7F", conv);   // bad continuations
  invalid_range<2>("\xC0\x80", "\xC0\xBF", conv);   // overlong forms
  invalid_range<2>("\xC0\xC0", "\xC0\xFF", conv);   // bad continuations
  invalid_range<2>("\xC1\x00", "\xC1\x7F", conv);   // bad continuations
  invalid_range<2>("\xC1\x80", "\xC1\xBF", conv);   // overlong forms
  invalid_range<2>("\xC1\xC0", "\xC1\xFF", conv);   // bad continuations

  //
  // [C2,E0) begin valid 2-byte sequences
  //
  for (b[0] = 0xC2; b[0] < 0xE0; ++b[0]) {
    ContinuationTester<1,2,Converter>()(b, conv);
  }

  //
  // [E0,F0) begin valid 3-byte sequences
  //

  // E0 [80,9F] [00,7F] are bad continuations
  // E0 [80,9F] [80,BF] are overlong forms
  // E0 [80,9F] [C0,FF] are bad continuations
  invalid_range<3>("\xE0\x00\x00", "\xE0\x9F\xFF", conv);

  // EO [A0,BF] [80,BF] contains valid code points
  b[0] = 0xE0;
  for (b[1] = 0xA0; b[1] < 0xC0; ++b[1]) {
    ContinuationTester<1,3,Converter>()(b, conv);
  }

  invalid_range<3>("\xE0\xC0\x00", "\xE0\xFF\xFF", conv); // bad continuations

  // [E1,ED) have the full range of continuation bytes
  for (b[0] = 0xE1; b[0] < 0xED; ++b[0]) {
    ContinuationTester<2,3,Converter>()(b, conv);
  }

  // ED has no continuations above 9F due to the UTF-16 surrogates
  invalid_range<3>("\xED\x00\x00", "\xED\x7F\xFF", conv);

  b[0] = 0xED;
  for (b[1] = 0x80; b[1] < 0xA0; ++b[1]) {
    ContinuationTester<1,3,Converter>()(b, conv);
  }

  // ED [A0,BF] [80,BF] are UTF-16 surrogates
  // everything else is a bad continuation
  invalid_range<3>("\xED\xA0\x00", "\xED\xFF\xFF", conv);
 
  // [EE,F0) have the full range of continuation bytes
  for (b[0] = 0xEE; b[0] < 0xF0; ++b[0]) {
    ContinuationTester<2,3,Converter>()(b, conv);
  }

  //
  // [0xF0,0xF5) begin valid 4-byte sequences
  // 

  // F0 lacks some continuation bytes due to overlong forms

  // F0 [80,8F] [80,BF] [80,BF] are overlong forms
  // everything else is a bad continuation
  invalid_range<4>("\xF0\x00\x00\x00", "\xF0\x8F\xFF\xFF", conv);

  b[0] = 0xF0;
  for (b[1] = 0x90; b[1] < 0xC0; ++b[1]) {
    ContinuationTester<2,4,Converter>()(b, conv);
  }

  invalid_range<4>("\xF0\xC0\x00\x00", "\xF0\xFF\xFF\xFF", conv);

  // [F1,F4) have the full range of continuation bytes
  for (b[0] = 0xF1; b[0] < 0xF4; ++b[0]) {
    ContinuationTester<3,4,Converter>()(b, conv);
  }

  // 4F lacks some continuation bytes due to 0x10FFFF Unicode limit
  invalid_range<4>("\xF4\x00\x00\x00", "\xF0\x7F\xFF\xFF", conv);

  b[0] = 0xF4;
  for (b[1] = 0x80; b[1] < 0x90; ++b[1]) {
    ContinuationTester<2,4,Converter>()(b, conv);
  }

  // > 0x10FFFF or bad continuations
  invalid_range<4>("\xF4\x90\x00\x00", "\xF4\xFF\xFF\xFF", conv);

  // 0xF5 and up are invalid
  invalid_range<1>("\xF5", "\xFF", conv);          // bad starts
}

SCOPE_TEST(utf8_to_unicode_test) {
  utf8_to_unicode_tester(utf8_to_unicode<const byte*>);
}

/*
SCOPE_TEST(UTF8toUnicodeIterator_ctor_test) {
  const char* text = u8"We are Motörhead. We play rock & roll.";
  UTF8toUnicodeIterator<const char*> i(text, text + strlen(text));
}
*/

template <class Iterator>
std::ostream& operator<<(std::ostream& o, const UTF8toUnicodeIterator<Iterator>& i) {
  o << *i;
  return o;
}

SCOPE_TEST(UTF8toUnicodeIterator_assignment_equals_test) {
  const char* text = u8"Heizölrückstoßabdämpfung";
  const char* tend = text + strlen(text);
  UTF8toUnicodeIterator<const char*> i(text, text, tend);
  UTF8toUnicodeIterator<const char*> j = i;
  UTF8toUnicodeIterator<const char*> k;
  SCOPE_ASSERT(j == j);
  SCOPE_ASSERT(j == i);
  SCOPE_ASSERT(j != k);
  SCOPE_ASSERT(j != j + 1);
}

SCOPE_TEST(UTF8toUnicodeIterator_less_test) {
  const char* text = u8"Heizölrückstoßabdämpfung";
  const char* tend = text + strlen(text);
  UTF8toUnicodeIterator<const char*> i(text, text, tend);
  UTF8toUnicodeIterator<const char*> j(text, text+1, tend);
  UTF8toUnicodeIterator<const char*> k(text, tend, tend);

  SCOPE_ASSERT(!(i < i));
  SCOPE_ASSERT(!(j < j));
  SCOPE_ASSERT(!(k < k));

  SCOPE_ASSERT(i < j);
  SCOPE_ASSERT(i < k);
  SCOPE_ASSERT(j < k);

  SCOPE_ASSERT(!(j < i));
  SCOPE_ASSERT(!(k < i));
  SCOPE_ASSERT(!(k < j));
}

SCOPE_TEST(UTF8toUnicodeIterator_post_increment_test) {
  const char* text = u8"I \U0001F4A9 Unicode";
  const char* tend = text + strlen(text);
  const int unicode[] = { 'I',' ',0x1F4A9,' ','U','n','i','c','o','d','e' };
  UTF8toUnicodeIterator<const char*> i(text, text, tend);
  for (int cp : unicode) {
    SCOPE_ASSERT_EQUAL(cp, *i++);
  }
}

SCOPE_TEST(UTF8toUnicodeIterator_pre_decrement_test) {
  const char* text = u8"I \U0001F4A9 Unicode";
  const char* tend = text + strlen(text);
  const int unicode[] = { 'e','d','o','c','i','n','U',' ',0x1F4A9,' ','I' };
  UTF8toUnicodeIterator<const char*> i(text, tend, tend);
  for (int cp : unicode) {
    SCOPE_ASSERT_EQUAL(cp, *--i);
  }
}

SCOPE_TEST(UTF8toUnicodeIterator_addition_test) {
  const char* text = u8"1ĳღ𝖀";
  const char* tend = text + strlen(text);
  const std::array<int,4> unicode{{ '1', 0x133, 0x10E6, 0x1D580 }};
  UTF8toUnicodeIterator<const char*> i(text, text, tend);
  for (uint32 x = 0; x < unicode.size(); ++x) {
    SCOPE_ASSERT_EQUAL(unicode[x], *(i + x));
  }
}

SCOPE_TEST(UTF8toUnicodeIterator_subtraction_test) {
  const char* text = u8"1ĳღ𝖀";
  const char* tend = text + strlen(text);
  const std::array<int,4> unicode{{ '1', 0x133, 0x10E6, 0x1D580 }};
  UTF8toUnicodeIterator<const char*> i(text, tend, tend);
  for (uint32 x = 0; x < unicode.size(); ++x) {
    SCOPE_ASSERT_EQUAL(unicode[unicode.size()-x-1], *(i-x-1));
  }
}

SCOPE_TEST(UTF8toUnicodeIterator_difference_test) {
  const char* text = u8"1ĳღ𝖀";
  const char* tend = text + strlen(text);

  const UTF8toUnicodeIterator<const char*> begin(text, text, tend);
  const UTF8toUnicodeIterator<const char*> end(text, tend, tend);
  SCOPE_ASSERT_EQUAL( 4, end - begin);
  SCOPE_ASSERT_EQUAL(-4, begin - end);

  UTF8toUnicodeIterator<const char*> i(text, text, tend);
  for (int x = 0;  i != end; ++x, ++i) {
    SCOPE_ASSERT_EQUAL( x, i - begin);
    SCOPE_ASSERT_EQUAL(-x, begin - i);
    SCOPE_ASSERT_EQUAL(x-4, i - end);
    SCOPE_ASSERT_EQUAL(4-x, end - i);
  }
}

SCOPE_TEST(UTF8toUnicodeIterator_addition_assignment_test) {
  const char* text = u8"Народный комиссариат внутренних дел";
  const char* tend = text + strlen(text);
  const std::array<int,35> unicode{{
    U'Н',U'а',U'р',U'о',U'д',U'н',U'ы',U'й',U' ',
    U'к',U'о',U'м',U'и',U'с',U'с',U'а',U'р',U'и',U'а',U'т',U' ',
    U'в',U'н',U'у',U'т',U'р',U'е',U'н',U'н',U'и',U'х',U' ',
    U'д',U'е',U'л'
  }};
  for (uint32 x = 0; x < unicode.size(); ++x) {
    UTF8toUnicodeIterator<const char*> i(text, text, tend);
    SCOPE_ASSERT_EQUAL(unicode[x], *(i += x));
  }
}

SCOPE_TEST(UTF8toUnicodeIterator_subtraction_assignment_test) {
  const char* text = u8"Народный комиссариат внутренних дел";
  const char* tend = text + strlen(text);
  const std::array<int,35> unicode{{
    U'Н',U'а',U'р',U'о',U'д',U'н',U'ы',U'й',U' ',
    U'к',U'о',U'м',U'и',U'с',U'с',U'а',U'р',U'и',U'а',U'т',U' ',
    U'в',U'н',U'у',U'т',U'р',U'е',U'н',U'н',U'и',U'х',U' ',
    U'д',U'е',U'л'
  }};
  for (uint32 x = 1; x <= unicode.size(); ++x) {
    UTF8toUnicodeIterator<const char*> i(text, tend, tend);
    SCOPE_ASSERT_EQUAL(unicode[unicode.size()-x], *(i -= x));
  }
}
