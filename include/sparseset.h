#pragma once

#include "basic.h"

// for the time-being, we're only going to support uint32, but could obviously template
// also, this doesn't work so well (er, at all) with values > 2^31-1
// low-part of array is non-sparse, high-part is dense
class SparseSet {
public:
  SparseSet(uint32 maxSize): Data(new uint32[2 * maxSize]), End(maxSize), Max(maxSize) {
    // we don't have to do this, but it'll make things like valgrind happy
    for (uint32 i = 0; i < maxSize; ++i) {
      Data[i] = 0;
    }
  }

  uint32 size() const { return End - Max; }

  // e had damn well better be less than Max, because we don't check
  void add(uint32 e) {
    Data[End] = e;
    Data[e] = End;
    ++End;
  }

  // e had damn well better be less than Max, because we don't check
  bool find(uint32 e) const {
    uint32 i = Data[e];
    return i < End && Data[i] == e;
  }

private:
  boost::scoped_array<uint32> Data;
  uint32 End,
         Max;
};
