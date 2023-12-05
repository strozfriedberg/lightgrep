#include "hitwriter.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <memory>
#include <iostream>

const char* find_leading_context(const char* const bbeg, const char* const hbeg, size_t lines) {
  // context left of hit
  const auto lbeg = std::reverse_iterator<const char*>(hbeg);
  const auto lend = std::reverse_iterator<const char*>(bbeg);

  auto lnl = lbeg - 1;
  for (int i = lines + 1; i > 0 && lnl != lend; --i) {
    lnl = std::find(lnl + 1, lend, '\n');
  }

  return bbeg + (lend - lnl);
}

const char* find_trailing_context(const char* const hend, const char* const bend, size_t lines) {

  auto rnl = hend - 1;
  for (int i = lines + 1; i > 0 && rnl != bend; --i) {
    rnl = std::find(rnl + 1, bend, '\n');
  }

  if (rnl != bend && *(rnl-1) == '\r') {
    // Back up one byte on the right end in case of CRLF line endings;
    // not necessary for the left end due to the LF being on the right
    // half of the EOL.
    --rnl;
  }

  return rnl;
}

bool histogramKeyComp(const std::pair<HistogramKey, int> &a, const std::pair<HistogramKey, int> &b) {
  if (a.second == b.second) {
    if (a.first.UserIndex == b.first.UserIndex ) {
      return a.first.HitText < b.first.HitText;
    }
    else {
      return a.first.UserIndex < b.first.UserIndex;
    }
  }
  else {
    return a.second > b.second;
  }
}

std::ostream& operator<<(std::ostream& out, const HistogramKey& hKey) {
  out << hKey.HitText << ", " << hKey.Pattern << ", " << hKey.UserIndex;
  return out;
}

std::ostream& operator<<(std::ostream& out, const LG_Histogram& histogram) {
  for (auto [hKey, count] : histogram) {
    out << "[" << hKey << "]: " << count << std::endl;
  }
  return out;
}

void WritePath::write(HitOutputData& data) {
  data.OutInfo.Out << data.OutInfo.Path;
  data.OutInfo.Out << data.OutInfo.Separator;
}

/********************************************* OutputInfo ****************************************/

void OutputInfo::writeHit(const LG_SearchHit& hit, const LG_PatternInfo* info) {
  Out << hit.Start << '\t'
      << hit.End << '\t'
      << info->UserIndex << '\t'
      << info->Pattern << '\t'
      << info->EncodingChain;
}

void OutputInfo::writeNewLine() {
  Out << '\n';
}

void OutputInfo::writeContext(const HitBuffer& hitBuf) {
  // print the hit, escaping \t, \n, \r
  const char* utf8 = hitBuf.Context.data();
  const char* utf8_end = utf8 + std::strlen(utf8);
  const char esc[] = "\t\n\r";

  // print offset of start of context
  Out << Separator << hitBuf.DataOffset << Separator;

  for (const char* l = utf8, *r; l != utf8_end; l = r) {
    r = std::find_first_of(l, utf8_end, esc, esc + 3);
    Out.write(l, r - l);
    if (r != utf8_end) {
      switch (*r) {
      case '\t': Out << "\\t"; break;
      case '\n': Out << "\\n"; break;
      case '\r': Out << "\\r"; break;
      }
      ++r;
    }
  }
}

/********************************************* HistogramInfo ****************************************/

void HistogramInfo::writeHistogram(std::ostream& histOut, char sep) {
  std::vector<std::pair<HistogramKey, int>> sortedHistogram;
  sortedHistogram.reserve(Histogram.size());

  for (auto i : Histogram) {
    sortedHistogram.push_back(i);
  }

  std::sort(sortedHistogram.begin(),
            sortedHistogram.end(),
            [](const std::pair<HistogramKey, int> &a, const std::pair<HistogramKey, int> &b){return histogramKeyComp(a, b);});

  for (const auto& [hKey, count] : sortedHistogram) {
    histOut << count          << sep;
    histOut << hKey.HitText   << sep;
    histOut << hKey.UserIndex << sep;
    histOut << hKey.Pattern;
    histOut << '\n';
  }
}

void HistogramInfo::writeHitToHistogram(const LG_SearchHit& hit, const LG_PatternInfo* info, std::function<HitBuffer(const LG_SearchHit&)> decodeFun) {
  HitBuffer hitText = (SearchHit(hit) == LastSearchHit && !DecodedContext.empty()) ? DecodedContext : decodeFun(hit);
  HistogramKey hitKey {hitText.hit(), info->Pattern, info->UserIndex};
  auto found = Histogram.find(hitKey);
  if (found != Histogram.end()) {
    ++found->second;
  }
  else {
    Histogram.insert({hitKey, 1});
  }
}

/********************************************* HitOutputData ****************************************/

HitOutputData::HitOutputData(std::ostream &out, ProgramHandle* prog, char sep, int32_t bc, int32_t ac, bool histEnabled)
              : OutInfo({out, "", sep, 0, bc, ac}), Prog(prog), HistInfo(HistogramInfo(histEnabled)), Decoder(lg_create_decoder()) {}

void HitOutputData::setBuffer(const char* buf, size_t blen, uint64_t boff) {
  HistInfo.LastSearchHit = SearchHit();
  HistInfo.DecodedContext.clear();
  CtxBuf.set(buf, blen, boff);
}

HitBuffer HitOutputData::decodeContext(const LG_SearchHit& searchHit) {
  const char* const hbeg = CtxBuf.Buf + (searchHit.Start < CtxBuf.BufOff ? 0 : searchHit.Start - CtxBuf.BufOff);
  const char* const hend = CtxBuf.Buf + std::min(searchHit.End - CtxBuf.BufOff, static_cast<uint64_t>(CtxBuf.BufLen));

  // beginning of context (left of hit)
  const char* const cbeg = (OutInfo.BeforeContext < 0) ? hbeg : find_leading_context(CtxBuf.Buf, hbeg, OutInfo.BeforeContext);
  // end of context (right of hit)
  const char* const cend = (OutInfo.AfterContext < 0) ? hend : find_trailing_context(hend, CtxBuf.Buf + CtxBuf.BufLen, OutInfo.AfterContext);

  // offset of the start of context
  uint64_t dataOffset = CtxBuf.BufOff + (cbeg - CtxBuf.Buf);

  // transcode the context to UTF-8
  LG_Error* err = nullptr;
  LG_Window inner{searchHit.Start, searchHit.End},
            outer,
            dh;
  const char* utf8 = nullptr;
  const LG_PatternInfo* info = lg_prog_pattern_info(const_cast<ProgramHandle*>(Prog), searchHit.KeywordIndex);

  lg_hit_context(
    Decoder,
    cbeg, cend,
    CtxBuf.BufOff + (cbeg - CtxBuf.Buf),
    &inner,
    info->EncodingChain,
    cend - cbeg,
    0xFFFD,
    &utf8, &outer, &dh, &err
  );

  std::unique_ptr<const char[],void(*)(const char*)> utf8_ptr(
    utf8, &lg_free_hit_context_string
  );

  if (err) {
    std::cerr << err->Message << std::endl;
    lg_free_error(err);
    return HitBuffer();
  }

  HistInfo.LastSearchHit = SearchHit(searchHit);
  HistInfo.DecodedContext = HitBuffer(dataOffset, std::string(utf8_ptr.get()), dh);
  return HistInfo.DecodedContext;
}

void HitOutputData::writeHitToHistogram(const LG_SearchHit& hit){
  LG_PatternInfo* info = lg_prog_pattern_info(const_cast<ProgramHandle*>(Prog), hit.KeywordIndex);
  HistInfo.writeHitToHistogram(hit, info, [this](const LG_SearchHit& hit){ return this->decodeContext(hit); });
}

void HitOutputData::writeHit(const LG_SearchHit& hit) {
  const LG_PatternInfo* info = lg_prog_pattern_info(const_cast<ProgramHandle*>(Prog), hit.KeywordIndex);
  OutInfo.writeHit(hit, info);
}


