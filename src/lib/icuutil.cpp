#include "icuutil.h"

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
