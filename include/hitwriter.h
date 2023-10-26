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
  HitWriterInfo(std::ostream& outStream, const LG_HPROGRAM hProg):
    Out(outStream), Prog(hProg) {}

  std::ostream& Out;

  const ProgramHandle* Prog;
};

class HitCounterDecorator: public HitCounterInfo {
public:
  HitCounterDecorator(HitCounterInfo* hci) { _hitCounterInfo = hci; }

  virtual void setPath(const std::string& s) { _hitCounterInfo->setPath(s); }
  virtual void setBuffer(const char* buf, size_t blen, uint64_t boff) { _hitCounterInfo->setBuffer(buf, blen, boff); }

  HitCounterInfo* _hitCounterInfo;
};

void hitWriter(void* userData, const LG_SearchHit* const hit);

struct PathWriterInfo: public HitWriterInfo {
  PathWriterInfo(std::ostream& outStream, const LG_HPROGRAM hProg):
    HitWriterInfo(outStream, hProg) {}

  std::string Path;

  virtual void setPath(const std::string& path) override { Path = path; }
};

void pathWriter(void* userData, const LG_SearchHit* const hit);

struct LineContextHitWriterInfo: public HitWriterInfo {
  LineContextHitWriterInfo(std::ostream& outStream,
                           const LG_HPROGRAM hProg,
                           int32_t beforeContext,
                           int32_t afterContext,
                           const std::string& groupSeparator):
    HitWriterInfo(outStream, hProg),
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
                            const LG_HPROGRAM hProg,
                            int32_t beforeContext,
                            int32_t afterContext,
                            const std::string& groupSeparator):
    LineContextHitWriterInfo(
      outStream, hProg, beforeContext, afterContext, groupSeparator) {}

  std::string Path;

  virtual void setPath(const std::string& path) override { Path = path; }
};

void lineContextPathWriter(void* userData, const LG_SearchHit* const hit);

const char* find_leading_context(const char* const bbeg, const char* const hbeg, size_t lines);

const char* find_trailing_context(const char* const hend, const char* const bend, size_t lines);

void writeLineContext(LineContextHitWriterInfo* hi, const LG_SearchHit* const hit);

struct HitOutputData {
  std::ostream &Out;
  std::string path;
  uint64_t NumHits;
  ProgramHandle* Prog;
  char Separator;
  int32_t BeforeContext;
  int32_t AfterContext;

  const char* Buf;
  size_t BufLen;
  uint64_t BufOff;

  LG_HDECODER Decoder;

  void setBuffer(const char* buf, size_t blen, uint64_t boff) {
    Buf = buf;
    BufLen = blen;
    BufOff = boff;
  }

  void writeContext(const LG_SearchHit& searchHit);

  void writeHit(const LG_SearchHit& hit){
    const LG_PatternInfo* info = lg_prog_pattern_info(const_cast<ProgramHandle*>(Prog), hit.KeywordIndex);

    Out << hit.Start << '\t'
        << hit.End << '\t'
        << info->UserIndex << '\t'
        << info->Pattern << '\t'
        << info->EncodingChain;
  }
};

template<typename PathOutputFn, typename ContextFn, bool shouldOutput>
void callbackFn(void* userData, const LG_SearchHit* searchHit) {
  HitOutputData* data = reinterpret_cast<HitOutputData*>(userData);
  if (shouldOutput) {
    PathOutputFn::write(*data);
    data->writeHit(*searchHit);
    ContextFn::write(*data, *searchHit);
    data->Out << "\n";
  }

  data->NumHits++;

}

struct WritePath {
  static void write(HitOutputData& data) {
    data.Out << data.path << data.Separator;
  }
};

struct DoNotWritePath {
  static void write(HitOutputData& data) {}
};

struct WriteContext {
  static void write(HitOutputData& data, const LG_SearchHit& searchHit) {
    data.writeContext(searchHit);
  }
};

struct NoContext {
  static void write(HitOutputData& data, const LG_SearchHit& searchHit) {}
};
