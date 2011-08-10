#pragma once

#include "basic.h"

class SearchHit: public LG_SearchHit {
public:
  SearchHit() { set(0, 0, 0); }
  // note that this takes the length
  SearchHit(uint64 start, uint64 length, uint32 lbl) { set(start, start + length, lbl); }

  void set(uint64 start, uint64 end, uint32 lbl) {
    Start = start; End = end; KeywordIndex = lbl;
  }

  uint64 length() const {
    return End - Start;
  }

  bool operator==(const SearchHit& x) const {
    return x.Start == Start && x.End == End && x.KeywordIndex == KeywordIndex;
  }

  bool operator<(const SearchHit& x) const {
    return Start < x.Start ||
          (Start == x.Start &&
          (End < x.End ||
          (End == x.End && KeywordIndex < x.KeywordIndex)));
  }
};

template<class OutStream>
OutStream& operator<<(OutStream& out, const SearchHit& hit) {
  out << '(' << hit.Start << ", " << hit.End << ", " << hit.KeywordIndex << ')';
  return out;
}

class HitCallback {
public:
  virtual ~HitCallback() {}
  virtual void collect(const SearchHit& hit) = 0;
};
