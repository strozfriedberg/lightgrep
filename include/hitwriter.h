#pragma once

#include "lightgrep_c_api.h"
#include "patterninfo.h"

#include <iosfwd>
#include <string>
#include <vector>

struct HitCounterInfo {
  HitCounterInfo(): NumHits(0) {}

  uint64 NumHits;

  virtual void setPath(const std::string&) {}
};

void nullWriter(void* userData, const LG_SearchHit* const);

struct HitWriterInfo: public HitCounterInfo, PatternInfo {
  HitWriterInfo(std::ostream& outStream, const PatternInfo& pinfo):
                PatternInfo(pinfo), Out(outStream) {}

  std::ostream& Out;
};

void hitWriter(void* userData, const LG_SearchHit* const hit);

struct PathWriterInfo: public HitWriterInfo {
  PathWriterInfo(std::ostream& outStream,
                 const PatternInfo& pinfo):
                 HitWriterInfo(outStream, pinfo) {}

  std::string Path;

  virtual void setPath(const std::string& path) { Path = path; }
};

void pathWriter(void* userData, const LG_SearchHit* const hit);

