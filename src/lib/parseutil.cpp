/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

#include "parseutil.h"
#include "icuutil.h"

#include <iostream>
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

int propertyGetter(const std::string& prop, UnicodeSet& us) {
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

  std::unique_ptr<USet, void(*)(USet*)> icu_us(
    uset_openPattern(ustr.get(), -1, &err), uset_close
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Unrecognized property \"" << prop << "\": " << u_errorName(err)
    );
  }

  convUnicodeSet(us, icu_us.get());
  return 1;
}

bool caseDesensitize(UnicodeSet& us) {
  std::unique_ptr<USet, void(*)(USet*)> icu_us(uset_openEmpty(), uset_close);
  convUnicodeSet(icu_us.get(), us);
  uset_closeOver(icu_us.get(), USET_CASE_INSENSITIVE);

  if (uset_size(icu_us.get()) == (int32) us.count()) {
    // the given set was already closed under case-insensitivity
    return false;
  }

  convUnicodeSet(us, icu_us.get());
  return true;
}
