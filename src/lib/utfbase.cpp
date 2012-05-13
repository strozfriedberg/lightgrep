#include "utfbase.h"

void UTFBase::writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32& l, uint32& h, byte* cur, uint32 len, uint32 blimit) const {
  while (l < blimit) {
    // write the encoding for the next code point
    write(l, cur);
    va.emplace_back(len);
    std::vector<ByteSet>& v = va.back();

    for (uint32 j = 0; j < len; ++j) {
      v[j].set(cur[j]);
    }

    // write the encoding for all code points with the same initial len bytes
    writeRangeBlock(v, ++l, h, len, blimit);

    // figure out where to look for the next code point
    if (l < h) {
      if (l >= blimit) {
        return;
      }
    }
    else if (i == iend) {
      return;
    }
    else {
      ++i;
      if (i == iend) {
        return;
      }
      l = i->first;
      h = i->second;
    }
  }
}

void UTFBase::skipRange(UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32& l, uint32& h, uint32 ubound) const {
  if (l < ubound) {
    if (i == iend) {
      return;
    }

    for (++i; i != iend; ++i) {
      l = i->first;
      h = i->second;
      if (h > ubound) {
        if (l < ubound) {
          l = ubound;
        }
        return;
      }
    }
  }
}
