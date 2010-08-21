#pragma once

#include "SearchHit.h"

#include <iosfwd>

class HitWriter: public HitCallback {
public:
  uint64  NumHits;

  HitWriter(std::ostream& outStream): NumHits(0), Out(outStream) {}

  virtual void collect(const SearchHit& hit);

private:
  std::ostream& Out;
};
