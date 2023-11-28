#pragma once

#include <lightgrep/api.h>
#include <lightgrep/search_hit.h>
#include <lightgrep/util.h>

#include <iosfwd>
#include <map>
#include <ostream>
#include <string>
#include <vector>

const char* find_leading_context(const char* const bbeg, const char* const hbeg, size_t lines);

const char* find_trailing_context(const char* const hend, const char* const bend, size_t lines);

struct HitBuffer {
  uint64_t dataOffset;
  std::string context;
  LG_Window hitWindow;

  std::string hit() const {
    return context.substr(hitWindow.begin, (hitWindow.end - hitWindow.begin));
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

class HitOutputData {
public:
  std::ostream &Out;
  std::string path;
  uint64_t NumHits;
  ProgramHandle* Prog;
  char Separator;
  int32_t BeforeContext;
  int32_t AfterContext;
  bool HistogramEnabled;

  const char* Buf;
  size_t BufLen;
  uint64_t BufOff;

  LG_HDECODER Decoder;
  std::unordered_map<HistogramKey, int> Histogram;

  HitOutputData(std::ostream &out, ProgramHandle* prog, char sep, int32_t bc, int32_t ac, bool hist)
                : Out(out), path(""), NumHits(0), Prog(prog), Separator(sep), BeforeContext(bc),
                AfterContext(ac), HistogramEnabled(hist), Decoder(lg_create_decoder()), Histogram({}) {}

  void setPath(const std::string& path) { this->path = path; }
  void setBuffer(const char* buf, size_t blen, uint64_t boff);

  HitBuffer decodeContext(const LG_SearchHit& searchHit);

  void writeHitToHistogram(const LG_SearchHit& hit);
  void writeHistogram();
  void writeContext(HitBuffer);
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
    data.writeContext(data.decodeContext(searchHit));
  }
};

struct NoContext {
  static void write(HitOutputData&, const LG_SearchHit&) {}
};