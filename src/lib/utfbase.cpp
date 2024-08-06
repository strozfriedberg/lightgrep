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

#include "encoders/utfbase.h"

void UTFBase::writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32_t& l, uint32_t& h, byte* cur, uint32_t len, uint32_t blimit) const {
  while (l < std::min(h, blimit)) {
    // write the encoding for the next code point
    write(l, cur);
    va.emplace_back(len);
    std::vector<ByteSet>& v = va.back();

    for (uint32_t j = 0; j < len; ++j) {
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

void UTFBase::skipRange(UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32_t& l, uint32_t& h, uint32_t ubound) const {
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
