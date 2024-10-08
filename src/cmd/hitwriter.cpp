/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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
  // context right of hit
  auto rnl = hend - 1;
  for (int i = lines + 1; i > 0 && rnl != bend; --i) {
    rnl = std::find(rnl + 1, bend, '\n');
  }

  if (rnl > hend && rnl != bend && *(rnl-1) == '\r') {
    // Back up one byte on the right end in case of CRLF line endings;
    // not necessary for the left end due to the LF being on the right
    // half of the EOL.
    --rnl;
  }

  return rnl;
}

bool histogramKeyComp(const LG_Histogram::value_type& a, const LG_Histogram::value_type& b) {
  // order descending by count, then ascending by user index and hit text
  return (a.second > b.second)
      || (a.second == b.second && (a.first.UserIndex < b.first.UserIndex 
                                    || (a.first.UserIndex == b.first.UserIndex && a.first.HitText < b.first.HitText)));
}

std::ostream& operator<<(std::ostream& out, const HistogramKey& hKey) {
  out << hKey.HitText << ", " << hKey.Pattern << ", " << hKey.UserIndex;
  return out;
}

std::ostream& operator<<(std::ostream& out, const LG_Histogram& histogram) {
  for (const auto& [hKey, count] : histogram) {
    out << "[" << hKey << "]: " << count << std::endl;
  }
  return out;
}

void WritePath::write(HitOutputData& data) {
  data.OutInfo.Out << data.OutInfo.Path << data.OutInfo.Separator;
}

void WriteContext::writeGroupSeparator(HitOutputData& data) {
  data.writeGroupSeparator();
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

void OutputInfo::writeGroupSeparator() {
  Out << GroupSeparator << '\n';
}

std::string escapeControlChars(const std::string& str) {
  std::string escaped;
  escaped.reserve(str.size() + 4); // give some extra space for escaped characters
  for (const char c : str) {
    switch(c) {
      case '\a':
        escaped += "\\a";
        continue;
      case '\b':
        escaped += "\\b";
        continue;
      case '\t':
        escaped += "\\t";
        continue;
      case '\n':
        escaped += "\\n";
        continue;
      case '\v':
        escaped += "\\v";
        continue;
      case '\f':
        escaped += "\\f";
        continue;
      case '\r':
        escaped += "\\r";
        continue;
      default:
        escaped += c;
    }
  }
  return escaped;
}

/********************************************* HistogramInfo ****************************************/

void HistogramInfo::writeHistogram(std::ostream& histOut, char sep) {
  std::vector<std::pair<HistogramKey, uint64_t>> sortedHistogram;
  sortedHistogram.reserve(Histogram.size());

  for (const auto& i : Histogram) {
    sortedHistogram.push_back(i);
  }

  std::sort(sortedHistogram.begin(),
            sortedHistogram.end(),
            [](const LG_Histogram::value_type& a, const LG_Histogram::value_type& b){return histogramKeyComp(a, b);});

  for (const auto& [hKey, count] : sortedHistogram) {
    histOut << count << sep
            << escapeControlChars(hKey.HitText) << sep
            << hKey.UserIndex << sep
            << escapeControlChars(hKey.Pattern) << '\n';
  }
}

void HistogramInfo::writeHitToHistogram(const LG_SearchHit& hit, const LG_PatternInfo* info, std::function<HitBuffer(const LG_SearchHit&)> decodeFun) {
  HitBuffer hitText = (SearchHit(hit) == LastSearchHit && !DecodedContext.empty()) ? DecodedContext : decodeFun(hit);
  HistogramKey hitKey {hitText.hit(), info->Pattern, info->UserIndex};
  ++Histogram[hitKey];
}

/********************************************* HitOutputData ****************************************/

HitOutputData::HitOutputData(std::ostream &out, ProgramHandle* prog, char separator, const std::string& groupSep, int32_t beforeContext, int32_t afterContext, bool histEnabled)
              : OutInfo({out, "", beforeContext, afterContext, separator, groupSep}), Prog(prog), HistInfo(HistogramInfo(histEnabled)), Decoder(lg_create_decoder(), lg_destroy_decoder) {}

void HitOutputData::setBuffer(const char* buf, size_t blen, uint64_t boff) {
  HistInfo.resetCache();
  CtxBuf.set(buf, blen, boff);
}

HitBuffer HitOutputData::decodeContext(const LG_SearchHit& searchHit) {
  const char* const hbeg = CtxBuf.Buf + (searchHit.Start < CtxBuf.BufOff ? 0 : searchHit.Start - CtxBuf.BufOff);
  const char* const hend = CtxBuf.Buf + std::min(searchHit.End - CtxBuf.BufOff, static_cast<uint64_t>(CtxBuf.BufLen));

  // beginning of context (left of hit)
  const char* const cbeg = OutInfo.BeforeContext < 0 ? hbeg : find_leading_context(CtxBuf.Buf, hbeg, OutInfo.BeforeContext);
  // end of context (right of hit)
  const char* const cend = OutInfo.AfterContext < 0 ? hend : find_trailing_context(hend, CtxBuf.Buf + CtxBuf.BufLen, OutInfo.AfterContext);

  // offset of the start of context
  const uint64_t dataOffset = CtxBuf.BufOff + (cbeg - CtxBuf.Buf);

  // transcode the context to UTF-8
  LG_Error* err = nullptr;
  LG_Window inner{searchHit.Start, searchHit.End},
            outer,
            decodedHit;
  const char* utf8 = nullptr;
  const LG_PatternInfo* info = lg_prog_pattern_info(Prog, searchHit.KeywordIndex);

  lg_hit_context(
    Decoder.get(),
    cbeg, cend,
    CtxBuf.BufOff + (cbeg - CtxBuf.Buf),
    &inner,
    info->EncodingChain,
    cend - cbeg,
    0xFFFD,
    &utf8, &outer, &decodedHit, &err
  );

  std::unique_ptr<const char[],void(*)(const char*)> utf8_ptr(
    utf8, &lg_free_hit_context_string
  );

  if (err) {
    lg_free_error(err);
    return HitBuffer();
  }

  HistInfo.LastSearchHit = SearchHit(searchHit);
  HistInfo.DecodedContext = HitBuffer(std::string(utf8_ptr.get()), decodedHit, dataOffset);
  return HistInfo.DecodedContext;
}

void HitOutputData::writeHitToHistogram(const LG_SearchHit& hit){
  LG_PatternInfo* info = lg_prog_pattern_info(Prog, hit.KeywordIndex);
  HistInfo.writeHitToHistogram(hit, info, [this](const LG_SearchHit& hit){ return decodeContext(hit); });
}

void HitOutputData::writeHit(const LG_SearchHit& hit) {
  const LG_PatternInfo* info = lg_prog_pattern_info(Prog, hit.KeywordIndex);
  OutInfo.writeHit(hit, info);
}


