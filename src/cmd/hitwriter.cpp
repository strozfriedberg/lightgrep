#include "hitwriter.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <memory>
#include <iostream>
#include <ostream>


void nullWriter(void* userData, const LG_SearchHit* const) {
  HitCounterInfo* hi = static_cast<HitCounterInfo*>(userData);
  ++hi->NumHits;
}

void writeHit(HitWriterInfo* hi, const LG_SearchHit* const hit) {
  ++hi->NumHits;
  const LG_PatternInfo* info = lg_pattern_info(hi->Map, hit->KeywordIndex);

  hi->Out << hit->Start << '\t'
          << hit->End << '\t'
          << reinterpret_cast<uint64_t>(info->UserData) << '\t'
          << info->Pattern << '\t'
          << info->EncodingChain;
}

void hitWriter(void* userData, const LG_SearchHit* const hit) {
  HitWriterInfo* hi = static_cast<HitWriterInfo*>(userData);
  writeHit(hi, hit);
  hi->Out << '\n';
}

void pathWriter(void* userData, const LG_SearchHit* const hit) {
  PathWriterInfo* hi = static_cast<PathWriterInfo*>(userData);
  hi->Out << hi->Path << '\t';
  writeHit(hi, hit);
  hi->Out << '\n';
}

void writeGroupSeparator(LineContextHitWriterInfo* hi) {
  // print the group separator
  if (hi->BeforeContext > 0 || hi->AfterContext > 0) {
    if (hi->FirstHit) {
      hi->FirstHit = false;
    }
    else {
      hi->Out << hi->GroupSeparator << '\n';
    }
  }
}

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

void writeLineContext(LineContextHitWriterInfo* hi, const LG_SearchHit* const hit) {
  // bounds of the hit in the buffer, clipped to buffer bounds
  const char* const hbeg = hi->Buf + (hit->Start < hi->BufOff ? 0 : hit->Start - hi->BufOff);
  const char* const hend = hi->Buf + std::min(hit->End - hi->BufOff, hi->BufLen);

  // beginning of context (left of hit)
  const char* const cbeg = find_leading_context(hi->Buf, hbeg, hi->BeforeContext);

  // end of context (right of hit)
  const char* const cend = find_trailing_context(hend, hi->Buf + hi->BufLen, hi->AfterContext);

  // print the offset of the start of context
  hi->Out << (hi->BufOff + (cbeg - hi->Buf)) << '\t';

  // transcode the context to UTF-8
  LG_Error* err = nullptr;
  LG_Window inner{hit->Start, hit->End}, outer, dh;
  const char* utf8 = nullptr;
  const LG_PatternInfo* info = lg_pattern_info(hi->Map, hit->KeywordIndex);

  lg_hit_context(
    hi->Decoder,
    cbeg, cend, hi->BufOff + (cbeg - hi->Buf),
    &inner,
    info->EncodingChain, cend - cbeg, 0xFFFD, &utf8, &outer, &dh, &err
  );

  std::unique_ptr<const char[],void(*)(const char*)> utf8_ptr(
    utf8, &lg_free_hit_context_string
  );

  if (err) {
    std::cerr << err->Message << std::endl;
    lg_free_error(err);
    return;
  }

  // print the hit, escaping \t, \n, \r
  const char* utf8_end = utf8 + std::strlen(utf8);
  const char esc[] = "\t\n\r";
  for (const char* l = utf8, *r; l != utf8_end; l = r) {
    r = std::find_first_of(l, utf8_end, esc, esc + 3);
    hi->Out.write(l, r - l);
    if (r != utf8_end) {
      switch (*r) {
      case '\t': hi->Out << "\\t"; break;
      case '\n': hi->Out << "\\n"; break;
      case '\r': hi->Out << "\\r"; break;
      }
      ++r;
    }
  }
}

void lineContextHitWriter(void* userData, const LG_SearchHit* const hit) {
  LineContextHitWriterInfo* hi = static_cast<LineContextHitWriterInfo*>(userData);
  writeGroupSeparator(hi);
  writeHit(hi, hit);
  hi->Out << '\t';
  writeLineContext(hi, hit);
  hi->Out << '\n';
}

void lineContextPathWriter(void* userData, const LG_SearchHit* const hit) {
  LineContextPathWriterInfo* hi = static_cast<LineContextPathWriterInfo*>(userData);
  writeGroupSeparator(hi);
  hi->Out << hi->Path << '\t';
  writeHit(hi, hit);
  hi->Out << '\t';
  writeLineContext(hi, hit);
  hi->Out << '\n';
}
