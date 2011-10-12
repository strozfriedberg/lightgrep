#pragma once

#include "lightgrep_c_api.h"

#include <iosfwd>
#include <string>
#include <vector>

struct HitCounterInfo {
  uint64 NumHits;
};

void nullWriter(void* userData, const LG_SearchHit* const);

struct HitWriterInfo: public HitCounterInfo {
  HitWriterInfo(std::ostream& outStream,
                const std::vector< std::pair<uint32,uint32> >& tbl,
                const std::vector<std::string>& patterns,
                const std::vector<std::string>& encodings):
                Out(outStream), Table(tbl), Patterns(patterns),
                Encodings(encodings) {}

  std::ostream& Out;
  const std::vector< std::pair<uint32, uint32> >& Table;
  const std::vector<std::string>& Patterns;
  const std::vector<std::string>& Encodings;
};

void hitWriter(void* userData, const LG_SearchHit* const hit);

struct PathWriterInfo: public HitWriterInfo {
  PathWriterInfo(const std::string& path,
                 std::ostream& outStream,
                 const std::vector< std::pair<uint32,uint32> >& tbl,
                 const std::vector<std::string>& patterns,
                 const std::vector<std::string>& encodings):
                 HitWriterInfo(outStream, tbl, patterns, encodings),
                 Path(path) {}

  const std::string Path;
};

void pathWriter(void* userData, const LG_SearchHit* const hit);

