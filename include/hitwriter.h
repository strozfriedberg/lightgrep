#pragma once

#include "SearchHit.h"

#include <iosfwd>

class HitWriter: public HitCallback {
public:
  uint64  NumHits;

  HitWriter(std::ostream& outStream,
            const std::vector< std::pair<uint32, uint32> >& tbl,
            const std::vector<std::string>& keys,
            const std::vector<std::string>& encodings):
            NumHits(0), Out(outStream), Table(tbl), Keys(keys), Encodings(encodings) {}

  virtual void collect(const SearchHit& hit);

private:
  std::ostream& Out;
  const std::vector< std::pair<uint32, uint32> >& Table;
  const std::vector< std::string >& Keys;
  const std::vector< std::string >& Encodings;
};
