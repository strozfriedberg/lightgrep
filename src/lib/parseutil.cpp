#include "parseutil.h"

#include <iostream>

#include <unicode/uniset.h>
#include <unicode/unistr.h>

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

int propertyGetter(const std::string& prop, ::UnicodeSet& us) {
  // ask ICU for the set corresponding to this property
  const UnicodeString ustr(prop.c_str(), -1, US_INV);
  std::cerr << prop << std::endl;
  UErrorCode err = U_ZERO_ERROR;
  icu_46::UnicodeSet icu_us(ustr, err);
  if (U_FAILURE(err)) {
    std::cerr << u_errorName(err) << std::endl;
    return -1;
  }

  const int rc = icu_us.getRangeCount();
  for (int i = 0; i < rc; ++i) {
    us.insert(icu_us.getRangeStart(i), icu_us.getRangeEnd(i)+1);
  }

  return 1;
}
