#pragma once

#include <lightgrep/api.h>
#include <lightgrep/search_hit.h>
#include <lightgrep/util.h>

#include <iosfwd>
#include <string>

struct HitBuffer {
  std::string context;
  LG_Window hitWindow;

  std::string hit() const {
    return context.substr(hitWindow.begin, (hitWindow.end - hitWindow.begin));
  }
};

class HitOutputData {
public:
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

  HitOutputData(std::ostream &out, ProgramHandle* prog, char sep, int32_t bc, int32_t ac)
                : Out(out), path(""), NumHits(0), Prog(prog), Separator(sep), BeforeContext(bc),
                AfterContext(ac), Decoder(lg_create_decoder()) {}

  void setPath(const std::string& path) { this->path = path; }
  void setBuffer(const char* buf, size_t blen, uint64_t boff) {
    Buf = buf;
    BufLen = blen;
    BufOff = boff;
  }

  HitBuffer decodeContext(const LG_SearchHit& searchHit);

  void writeContext(const char* const utf8);
  void writeHit(const LG_SearchHit& hit);
  void writeNewLine();
};

template<typename PathOutputFn, typename ContextFn, bool shouldOutput>
void callbackFn(void* userData, const LG_SearchHit* searchHit) {
  HitOutputData* data = reinterpret_cast<HitOutputData*>(userData);
  if (shouldOutput) {

    PathOutputFn::write(*data);
    data->writeHit(*searchHit);
    ContextFn::write(*data, *searchHit);
    data->writeNewLine();
  }

  data->NumHits++;

}

struct WritePath {
  static void write(HitOutputData& data);
};

struct DoNotWritePath {
  static void write(HitOutputData&) {}
};

struct WriteContext {
  static void write(HitOutputData& data, const LG_SearchHit& searchHit) {
    data.writeContext(data.decodeContext(searchHit).context.data());
  }
};

struct NoContext {
  static void write(HitOutputData&, const LG_SearchHit&) {}
};

const char* find_leading_context(const char* const bbeg, const char* const hbeg, size_t lines);

const char* find_trailing_context(const char* const hend, const char* const bend, size_t lines);
