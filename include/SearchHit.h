#pragma once

#include "basic.h"

class SearchHit {
public:
  uint64  Offset,
          Length;

  SearchHit(uint64 o, uint64 len): Offset(o), Length(len) {}

  bool operator==(const SearchHit& x) const { return x.Offset == Offset && x.Length == Length; }
};

template<class OutStream>
OutStream& operator<<(OutStream& out, const SearchHit& hit) {
  out << '(' << hit.Offset << ", " << hit.Length << ')';
  return out;
}

class HitCallback {
public:
  virtual void collect(const SearchHit& hit) = 0;
};
