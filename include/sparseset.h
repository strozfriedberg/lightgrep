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

#include "basic.h"

#include <algorithm>

// for the time-being, we're only going to support uint32_t, but could obviously template
// also, this doesn't work so well (er, at all) with values > 2^31-1
// low-part of array is non-sparse, high-part is dense
class SparseSet {
public:
  SparseSet(uint32_t maxSize = 0) { resize(maxSize); }

  uint32_t size() const { return End - Max; }

  // e had damn well better be less than Max, because we don't check
  bool find(uint32_t e) const {
    const uint32_t i = Data[e] + Max;
    return i < End && Data[i] == e;
  }

  // e had damn well better be less than Max, because we don't check
  void insert(uint32_t e) {
    Data[End] = e;
    Data[e] = End - Max;
    ++End;
  }

  void clear() {
    End = Max;
  }

  void resize(uint32_t maxSize) {
    Data.reset(new uint32_t[2 * maxSize]);
    End = Max = maxSize;
    // we don't have to do this, but it'll make things like valgrind happy
    std::fill(Data.get(), Data.get() + maxSize, 0);
  }

  size_t max_size() const { return std::numeric_limits<uint32_t>::max()/2+1; }

private:
  std::unique_ptr<uint32_t[]> Data;
  uint32_t End,
           Max;
};
