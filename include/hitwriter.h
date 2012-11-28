#pragma once

#include "lightgrep/api.h"
#include "lightgrep/search_hit.h"

#include <iosfwd>
#include <string>
#include <vector>

struct HitCounterInfo {
  virtual ~HitCounterInfo() {}

  uint64_t NumHits;

  virtual void setPath(const std::string&) {}
};

void nullWriter(void* userData, const LG_SearchHit* const);

struct HitWriterInfo: public HitCounterInfo {
  HitWriterInfo(std::ostream& outStream, const LG_HPATTERNMAP hMap):
    Out(outStream), Map(hMap) {}

  std::ostream& Out;

  const LG_HPATTERNMAP Map;
};

void hitWriter(void* userData, const LG_SearchHit* const hit);

struct PathWriterInfo: public HitWriterInfo {
  PathWriterInfo(std::ostream& outStream, const LG_HPATTERNMAP hMap):
    HitWriterInfo(outStream, hMap) {}

  std::string Path;

  virtual void setPath(const std::string& path) { Path = path; }
};

void pathWriter(void* userData, const LG_SearchHit* const hit);
