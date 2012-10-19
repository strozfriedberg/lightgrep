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

#include "utfbase.h"

void UTFBase::writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32& l, uint32& h, byte* cur, uint32 len, uint32 blimit) const {
  while (l < std::min(h, blimit)) {
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
