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

void convUnicodeSet(::UnicodeSet& dst, const icu::UnicodeSet& src) {
  const int rc = src.getRangeCount();
  for (int i = 0; i < rc; ++i) {
    dst.insert(src.getRangeStart(i), src.getRangeEnd(i)+1);
  }
}

void convUnicodeSet(icu::UnicodeSet& dst, const ::UnicodeSet& src) {
  for (const ::UnicodeSet::range& r : src) {
    dst.add(r.first, r.second-1);
  }
}

int propertyGetter(const std::string& prop, ::UnicodeSet& us) {
  // ask ICU for the set corresponding to this property
  const UnicodeString ustr(prop.c_str(), -1, US_INV);
  UErrorCode err = U_ZERO_ERROR;
  icu::UnicodeSet icu_us(ustr, err);
  if (U_FAILURE(err)) {
    std::cerr << u_errorName(err) << std::endl;
    return -1;
  }

  convUnicodeSet(us, icu_us);
  return 1;
}

bool caseDesensitize(::UnicodeSet& us) {
  icu::UnicodeSet icu_us;
  convUnicodeSet(icu_us, us);
  icu_us.closeOver(USET_CASE_INSENSITIVE);

  if (icu_us.size() == (int32) us.count()) {
    // the given set was already closed under case-insensitivity
    return false;
  }

  convUnicodeSet(us, icu_us);
  return true;
}
