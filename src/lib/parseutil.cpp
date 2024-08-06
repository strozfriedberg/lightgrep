/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "parseutil.h"
#include "icuutil.h"

#include <memory>

#include <unicode/uset.h>
#include <unicode/ustring.h>

int parseHexChar(int c) {
  switch (c) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return c - '0';
  case 'A':
  case 'B':
  case 'C':
  case 'D':
  case 'E':
  case 'F':
    return c - 'A' + 10;
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
    return c - 'a' + 10;
  default:
    return -1;
  }
}

int parseOctChar(int c) {
  return ('0' <= c && c <= '7') ? c - '0' : -1;
}

int propertyGetter(const std::string& prop, UnicodeSet& us, bool case_insensitive) {
  // ask ICU for the set corresponding to this property
  UErrorCode err = U_ZERO_ERROR;

  const size_t ustrlen = prop.length();
  std::unique_ptr<UChar[]> ustr(new UChar[ustrlen+1]);
  u_strFromUTF8(
    ustr.get(), ustrlen+1, nullptr, prop.c_str(), -1, &err
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Failed to convert string: " << u_errorName(err);
    );
  }

  const uint32_t opts = case_insensitive ? USET_CASE_INSENSITIVE : 0;

  std::unique_ptr<USet, void(*)(USet*)> icu_us(
    uset_openPatternOptions(ustr.get(), -1, opts, &err), uset_close
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Unrecognized property \"" << prop << "\": " << u_errorName(err)
    );
  }

  addUnicodeSet(us, icu_us.get());
  return 1;
}

bool caseDesensitizeUnicode(UnicodeSet& us) {
  std::unique_ptr<USet, void(*)(USet*)> icu_us(uset_openEmpty(), uset_close);
  convUnicodeSet(icu_us.get(), us);
  uset_closeOver(icu_us.get(), USET_CASE_INSENSITIVE);

  if (uset_size(icu_us.get()) == (int32_t) us.count()) {
    // the given set was already closed under case-insensitivity
    return false;
  }

  convUnicodeSet(us, icu_us.get());
  return true;
}

bool caseDesensitizeAscii(UnicodeSet& us) {
  const UnicodeSet::size_type orig_count = us.count();

  const UnicodeSet ascii_upper('A', 'Z' + 1);
  const UnicodeSet ascii_lower('a', 'z' + 1);
  const uint8_t case_delta = 'a' - 'A'; // 0x20

  // map uppercase ASCII to lowercase
  for (auto r: us & ascii_upper) {
    r.first += case_delta;
    r.second += case_delta;
    us.insert(r);
  }

  // map lowercase ASCII to uppercase
  for (auto r: us & ascii_lower) {
    r.first -= case_delta;
    r.second -= case_delta;
    us.insert(r);
  }

  // desensitize nonascii as normal
  const UnicodeSet nonascii(0x80, 0x110000);
  UnicodeSet high = us & nonascii;
  if (high.any() && caseDesensitizeUnicode(high)) {
    us |= high;
  }

  // return true if closure added something
  return orig_count < us.count();
}

bool caseDesensitize(UnicodeSet& us, bool ascii_mode) {
  return ascii_mode ? caseDesensitizeAscii(us) : caseDesensitizeUnicode(us);
}

void setDigitClass(UnicodeSet& us, bool ascii_mode) {
  if (ascii_mode) {
    // \d = [0-9]
    us.insert('0', '9' + 1);
  }
  else {
    // pcrepattern(3): \d = \p{Nd}
    propertyGetter("\\p{Nd}", us, false);
  }
}

void setHorizontalSpaceClass(UnicodeSet& us) {
  us.set('\t');
  us.set(' ');
  us.set(0xA0);   // NO-BREAK SPACE
  us.set(0x1680); // OGHAM SPACE MARK
  us.set(0x180E); // MONGOLIAN VOWEL SEPARATOR
  // EN QUAD
  // EM QUAD
  // EN SPACE
  // EM SPACE
  // THREE-PER-EM SPACE
  // FOUR-PER-EM SPACE
  // SIX-PER-EM SPACE
  // FIGURE SPACE
  // PUNCTUATION SPACE
  // THIN SPACE
  // HAIR SPACE
  us.insert(0x2000, 0x200B);
  us.set(0x202F); // NARROW NO-BREAK SPACE
  us.set(0x205F); // MEDIUM MATHEMATICAL SPACE
  us.set(0x3000); // IDEOGRAPHIC SPACE
}

void setVerticalSpaceClass(UnicodeSet& us) {
  us.insert(0x0A, 0x0E); // \n, \v, \f, \r
  us.set(0x85); // NEXT LINE
  // LINE SEPARATOR
  // PARAGRAPH SEPARATOR
  us.insert(0x2028, 0x202A);
}

void setSpaceClass(UnicodeSet& us, bool ascii_mode) {
  if (ascii_mode) {
    us.insert(0x09, 0x0E); // \t, \n, \v, \f, \r
    us.set(' ');
  }
  else {
    // pcrepattern(3): \s = [\p{Z}\h\v]
    // presently \p{Z} is a subset of [\h\v] and we have a test to prove it,
    // so adding \p{Z} is a noop and we skip it
    setHorizontalSpaceClass(us);
    setVerticalSpaceClass(us);
  }
}

void setWordClass(UnicodeSet& us, bool ascii_mode) {
  if (ascii_mode) {
    // \w = [A-Za-z0-9_]
    us.insert('0', '9' + 1);
    us.insert('A', 'Z' + 1);
    us.set('_');
    us.insert('a', 'z' + 1);
  }
  else {
    // pcrepattern(3): \w = [\p{L}\p{N}_]
    propertyGetter("\\p{L}", us, false);
    propertyGetter("\\p{N}", us, false);
    us.set('_');
  }
}
