#pragma once

#include "basic.h"

#include <algorithm>

// for the time-being, we're only going to support uint32, but could obviously template
// also, this doesn't work so well (er, at all) with values > 2^31-1
// low-part of array is non-sparse, high-part is dense
class SparseSet {
public:
  SparseSet(uint32 maxSize = 0) { resize(maxSize); }

  uint32 size() const { return End - Max; }

  // e had damn well better be less than Max, because we don't check
  bool find(uint32 e) const {
    const uint32 i = Data[e] + Max;
    return i < End && Data[i] == e;
  }

  // e had damn well better be less than Max, because we don't check
  void insert(uint32 e) {
    Data[End] = e;
    Data[e] = End - Max;
    ++End;
  }

  void clear() {
    End = Max;
  }

  void resize(uint32 maxSize) {
    Data.reset(new uint32[2 * maxSize]);
    End = Max = maxSize;
    // we don't have to do this, but it'll make things like valgrind happy
    std::fill(Data.get(), Data.get() + maxSize, 0);
  }

private:
  std::unique_ptr<uint32[]> Data;
  uint32 End,
         Max;
};
