#pragma once

#include "lightgrep_c_api.h"

#include <iosfwd>
#include <string>
#include <vector>

class HitCounter {
public:
  HitCounter(): NumHits(0) {}

  virtual ~HitCounter() {}

  virtual void collect(const LG_SearchHit&) {
    ++NumHits;
  }

  uint64  NumHits;
};

class HitWriter: public HitCounter {
public:
  HitWriter(std::ostream& outStream,
            const std::vector< std::pair<uint32,uint32> >& tbl,
            const std::vector<std::string>& keys,
            const std::vector<std::string>& encodings):
            HitCounter(), Out(outStream), Table(tbl), Keys(keys), Encodings(encodings) {}

  virtual ~HitWriter() {}
  virtual void collect(const LG_SearchHit& hit);

protected:
  std::ostream& Out;
  const std::vector< std::pair<uint32, uint32> >& Table;
  const std::vector<std::string>& Keys;
  const std::vector<std::string>& Encodings;
};

class NullWriter: public HitCounter {
};

class PathWriter: public HitWriter {
public:
  PathWriter(const std::string& path,
             std::ostream& outStream,
             const std::vector< std::pair<uint32,uint32> >& tbl,
             const std::vector<std::string>& keys,
             const std::vector<std::string>& encodings):
             HitWriter(outStream, tbl, keys, encodings), Path(path) {}

  virtual ~PathWriter() {}
  virtual void collect(const LG_SearchHit& hit);

private:
  std::string Path;
};
