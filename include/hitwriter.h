#pragma once

#include "SearchHit.h"

#include <iosfwd>

class HitCounter: public HitCallback {
public:
  HitCounter(): NumHits(0) {}

  uint64  NumHits;
};

class HitWriter: public HitCounter {
public:
  HitWriter(std::ostream& outStream,
            const std::vector< std::pair<uint32, uint32> >& tbl,
            const std::vector<std::string>& keys,
            const std::vector<std::string>& encodings):
            HitCounter(), Out(outStream), Table(tbl), Keys(keys), Encodings(encodings) {}

  virtual void collect(const SearchHit& hit);

private:
  std::ostream& Out;
  const std::vector< std::pair<uint32, uint32> >& Table;
  const std::vector< std::string >& Keys;
  const std::vector< std::string >& Encodings;
};

class NullWriter: public HitCounter {
public:
  virtual void collect(const SearchHit&) { ++NumHits; }
};
