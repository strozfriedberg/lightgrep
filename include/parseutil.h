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

#pragma once

#include <algorithm>
#include <iterator>

#include "basic.h"
#include "unicode.h"
#include "rangeset.h"

#include <unicode/uchar.h>

int parseHexChar(int c);

// Should accept \\x[0-9A-Fa-f]{2}
template <typename Iterator>
int parseHexByte(Iterator& i, const Iterator& iend) {
  if (i == iend) {
    return -1;
  }

  int val = parseHexChar(*i++);
  if (val < 0 || i == iend) {
    return -1;
  }
  val <<= 4;
  val |= parseHexChar(*i++);
  return val < 0 ? -1 : val;
}

// Should accept \\x\{[0-9A-Fa-f]{0,6}\}
template <typename Iterator>
int parseHexCodePoint(Iterator& i, const Iterator& iend) {
  if (i == iend || *i == '}') {
    return -1;
  }

  const Iterator end = std::min(i + 7, iend);
  for (int c, val = 0; i != end; ) {
    c = *i++;
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
      val <<= 4;
      val |= c - '0';
      break;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
      val <<= 4;
      val |= c - 'A' + 10;
      break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
      val <<= 4;
      val |= c - 'a' + 10;
      break;
    case '}':
      return val > 0x10FFFF ? -1 : val;
    default:
      return -1;
    }
  }
  return -1;
}

int parseOctChar(int c);

// Should accept \\[0-7]{1,3}
template <typename Iterator>
int parseOctByte(Iterator& i, const Iterator& iend) {
  int oct = 0;

  const Iterator end = std::min(i + 3, iend);
  for (int digit; i != end; ) {
    digit = parseOctChar(*i);

    if (digit == -1) {
      break;
    }

    ++i;
    oct <<= 3;
    oct |= digit;
  }

  return oct > 0377 ? -1 : oct;
}

template <typename Iterator>
int unicode_to_ascii(Iterator& i, const Iterator& end, std::string& out) {
  byte b;
  while (unicode_to_ascii(b, i, end) != -1) {
    out += b;
  }

  // check that there were no non-ASCII chars
  return i != end ? -1 : 1;
}

template <typename Iterator>
int prepareStringForICU(Iterator& i, const Iterator& end, std::string& out) {
  // find the closing '}'
  const Iterator nend(std::find(i, end, '}'));
  if (nend == end) {
    i = end;
    return -1;
  }

  // sadly, we need to convert the string back to bytes
  if (unicode_to_ascii(i, nend, out) == -1) {
    return -1;
  }

  ++i;

  return 1;
}

// Should accept \{U\+[0-9A-Fa-f]{1,6}\} and \{[\w ]+\}
template <typename Iterator>
int parseNamedCodePoint(Iterator& i, const Iterator& end) {
  if (i == end) {
    return -1;
  }

  if (*i++ != '{') {
    return -1;
  }

  if (i + 1 < end && *i == 'U' && *(i+1) == '+') {
    // this is U+hhhh, parseHexCodePoint handles the closing '}'
    return parseHexCodePoint(i += 2, end);
  }

  std::string name;
  if (prepareStringForICU(i, end, name) == -1) {
    return -1;
  }

  // ask ICU for the code point with this name
  UErrorCode err = U_ZERO_ERROR;
  const int val = u_charFromName(U_UNICODE_CHAR_NAME, name.c_str(), &err);
  return U_FAILURE(err) ? -1 : val;
}

int propertyGetter(const std::string& prop, UnicodeSet& us, bool case_insensitive);

template <typename Iterator>
int parseProperty(Iterator& i, const Iterator& end, UnicodeSet& us, bool case_insensitive) {
  if (i == end) {
    return -1;
  }

  if (i+1 == end || i+2 == end) {
    i = end;
    return -1;
  }

  if (*(i+2) != '{') {
    i += 2;
    return -1;
  }

  std::string prop;
  if (prepareStringForICU(i, end, prop) == -1) {
    return -1;
  }
  prop += '}';

  us.reset();
  return propertyGetter(prop, us, case_insensitive);
}

bool caseDesensitize(UnicodeSet& us, bool ascii_mode);

bool caseDesensitizeAscii(UnicodeSet& us);

bool caseDesensitizeUnicode(UnicodeSet& us);

void setDigitClass(UnicodeSet& us, bool ascii_mode);

void setWordClass(UnicodeSet& us, bool ascii_mode);

void setHorizontalSpaceClass(UnicodeSet& us);

void setVerticalSpaceClass(UnicodeSet& us);

void setSpaceClass(UnicodeSet& us, bool ascii_mode);
