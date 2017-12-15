#pragma once

#include <lightgrep/api.h>
#include <lightgrep/search_hit.h>
#include <lightgrep/util.h>

#include <iosfwd>
#include <string>


struct HitCounterInfo {
  HitCounterInfo(): NumHits(0) {}

  virtual ~HitCounterInfo() {}

  uint64_t NumHits;

  virtual void setPath(const std::string&) {}

  virtual void setBuffer(const char*, size_t, uint64_t) {}
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

  virtual void setPath(const std::string& path) override { Path = path; }
};

void pathWriter(void* userData, const LG_SearchHit* const hit);

struct LineContextHitWriterInfo: public HitWriterInfo {
  LineContextHitWriterInfo(std::ostream& outStream,
                           const LG_HPATTERNMAP hMap,
                           int32_t beforeContext,
                           int32_t afterContext,
                           const std::string& groupSeparator):
    HitWriterInfo(outStream, hMap),
    BeforeContext(beforeContext),
    AfterContext(afterContext),
    GroupSeparator(groupSeparator),
    Decoder(lg_create_decoder()) {}

  virtual ~LineContextHitWriterInfo() {
    lg_destroy_decoder(Decoder);
  }

  int32_t BeforeContext, AfterContext;
  std::string GroupSeparator;

  const char* Buf;
  size_t BufLen;
  uint64_t BufOff;

  LG_HDECODER Decoder;

  bool FirstHit = true;

  virtual void setBuffer(const char* buf, size_t blen, uint64_t boff) override {
    Buf = buf;
    BufLen = blen;
    BufOff = boff;
  }
};

void lineContextHitWriter(void* userData, const LG_SearchHit* const hit);

struct LineContextPathWriterInfo: public LineContextHitWriterInfo {
  LineContextPathWriterInfo(std::ostream& outStream,
                            const LG_HPATTERNMAP hMap,
                            int32_t beforeContext,
                            int32_t afterContext,
                            const std::string& groupSeparator):
    LineContextHitWriterInfo(
      outStream, hMap, beforeContext, afterContext, groupSeparator) {}

  std::string Path;

  virtual void setPath(const std::string& path) override { Path = path; }
};

void lineContextPathWriter(void* userData, const LG_SearchHit* const hit);

const char* find_leading_context(const char* const bbeg, const char* const hbeg, size_t lines);

const char* find_trailing_context(const char* const hend, const char* const bend, size_t lines);
