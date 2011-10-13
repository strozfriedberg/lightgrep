#pragma once

#include "lightgrep_c_api.h"
#include "patterninfo.h"

#include <iosfwd>
#include <string>
#include <vector>

struct HitCounterInfo {
  HitCounterInfo(): NumHits(0) {}

  uint64 NumHits;
};

void nullWriter(void* userData, const LG_SearchHit* const);

struct HitWriterInfo: public HitCounterInfo, PatternInfo {
  HitWriterInfo(std::ostream& outStream, const PatternInfo& pinfo):
                PatternInfo(pinfo), Out(outStream) {}

  std::ostream& Out;
};

void hitWriter(void* userData, const LG_SearchHit* const hit);

struct PathWriterInfo: public HitWriterInfo {
  PathWriterInfo(const std::string& path,
                 std::ostream& outStream,
                 const PatternInfo& pinfo):
                 HitWriterInfo(outStream, pinfo),
                 Path(path) {}

  const std::string Path;
};

void pathWriter(void* userData, const LG_SearchHit* const hit);

