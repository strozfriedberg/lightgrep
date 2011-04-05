#pragma once

#include "basic.h"

class SearchHit {
public:
  uint64  Offset,
          Length;
  uint32  Label;

  SearchHit(): Offset(0), Length(0), Label(0) {}
  SearchHit(uint64 o, uint64 len, uint32 lbl): Offset(o), Length(len), Label(lbl) {}

  void set(uint64 o, uint64 len, uint32 lbl) { Offset = o; Length = len; Label = lbl; }

  bool operator==(const SearchHit& x) const { return x.Offset == Offset && x.Length == Length && x.Label == Label; }
};

template<class OutStream>
OutStream& operator<<(OutStream& out, const SearchHit& hit) {
  out << '(' << hit.Offset << ", " << hit.Length << ", " << hit.Label << ')';
  return out;
}

class HitCallback {
public:
  virtual void collect(const SearchHit& hit) = 0;
};
