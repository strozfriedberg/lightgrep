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
