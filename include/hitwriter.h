#pragma once

#include <lightgrep/api.h>
#include <lightgrep/search_hit.h>
#include <lightgrep/util.h>

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include "searchhit.h"

const char* find_leading_context(const char* const bbeg, const char* const hbeg, size_t lines);

const char* find_trailing_context(const char* const hend, const char* const bend, size_t lines);

struct HitBuffer {
  std::string Context;
  LG_Window HitWindow;
  uint64_t DataOffset;

  HitBuffer() : Context(""), HitWindow({0,0}), DataOffset(0) {}
  HitBuffer(const std::string& con, const LG_Window& win, const uint64_t dataOff): Context(con), HitWindow(win), DataOffset(dataOff) {}

  std::string hit() const {
    return Context.substr(HitWindow.begin, (HitWindow.end - HitWindow.begin));
  }

  bool empty() const {
    return Context.empty();
  }

  void clear() {
    *this = HitBuffer();
  }
};

class HistogramKey {
public:
  std::string HitText;
  std::string Pattern;
  uint64_t UserIndex;

  HistogramKey(std::string hit, std::string pat, uint64_t indx) : HitText(hit), Pattern(pat), UserIndex(indx) {};

  bool operator==(const HistogramKey& node) const {
    return (node.Pattern == Pattern && node.HitText == HitText && node.UserIndex == UserIndex);
  }

  friend std::ostream& operator<<(std::ostream& out, const HistogramKey& hKey);
};

std::ostream& operator<<(std::ostream& out, const HistogramKey& hKey);

typedef std::unordered_map<HistogramKey, int> LG_Histogram;

std::ostream& operator<<(std::ostream& out, const LG_Histogram& histogram);

bool histogramKeyComp(const std::pair<HistogramKey, int> &a, const std::pair<HistogramKey, int> &b);

// custom hash function copied from https://stackoverflow.com/a/17017281
template<>
struct std::hash<HistogramKey>
{
    std::size_t operator()(const HistogramKey& node) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(node.Pattern);
        std::size_t h2 = std::hash<std::string>{}(node.HitText);
        std::size_t h3 = std::hash<uint64_t>{}(node.UserIndex);
        return h1 ^ ((h2 << 1) >> 1) ^ (h3 << 1);
    }
};

struct ContextBuffer {
  const char* Buf;
  size_t BufLen;
  uint64_t BufOff;

  void set(const char* buf, size_t len, uint64_t off) {
    Buf = buf;
    BufLen = len;
    BufOff = off;
  }
};

struct OutputInfo {
  std::ostream &Out;
  std::string Path;
  char Separator;
  uint64_t NumHits;
  int32_t BeforeContext;
  int32_t AfterContext;

  void writeHit(const LG_SearchHit& hit, const LG_PatternInfo* info);
  void writeContext(const HitBuffer&);
  void writeNewLine();
};

struct HistogramInfo {
  bool HistogramEnabled;
  HitBuffer DecodedContext;
  SearchHit LastSearchHit;
  std::unordered_map<HistogramKey, int> Histogram;

  HistogramInfo(bool histEnabled) : HistogramEnabled(histEnabled), Histogram({}) {}
  void writeHistogram(std::ostream& histOut, char sep);
  void writeHitToHistogram(const LG_SearchHit& hit, const LG_PatternInfo* info, std::function<HitBuffer(const LG_SearchHit&)>fn);
};

class HitOutputData {
public:
  OutputInfo OutInfo;
  ProgramHandle* Prog;
  ContextBuffer CtxBuf;
  HistogramInfo HistInfo;
  LG_HDECODER Decoder;

  HitOutputData(std::ostream &out, ProgramHandle* prog, char sep, int32_t bc, int32_t ac, bool histEnabled);

  void setPath(const std::string& path) { this->OutInfo.Path = path; }
  void setBuffer(const char* buf, size_t blen, uint64_t boff);

  HitBuffer decodeContext(const LG_SearchHit& searchHit);

  void writeHitToHistogram(const LG_SearchHit& hit);
  void writeHistogram(std::ostream& histOut) { HistInfo.writeHistogram(histOut, OutInfo.Separator); }
  void writeContext(const HitBuffer& hBuf) { OutInfo.writeContext(hBuf); }
  void writeHit(const LG_SearchHit& hit);
  void writeNewLine() { OutInfo.writeNewLine(); }
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

  if (data->HistInfo.HistogramEnabled) {
    data->writeHitToHistogram(*searchHit);
  }
  ++data->OutInfo.NumHits;
}

struct WritePath {
  static void write(HitOutputData& data);
};

struct DoNotWritePath {
  static void write(HitOutputData&) {}
};

struct WriteContext {
  static void write(HitOutputData& data, const LG_SearchHit& searchHit) {
    data.writeContext(data.decodeContext(searchHit));
  }
};

struct NoContext {
  static void write(HitOutputData&, const LG_SearchHit&) {}
};