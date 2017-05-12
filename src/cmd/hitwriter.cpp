#include "hitwriter.h"

#include <algorithm>
#include <iterator>
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

void writeLineContext(LineContextHitWriterInfo* hi, const LG_SearchHit* const hit) {
  // bounds of the hit in the buffer
  const char* hbeg = hi->Buf + (hit->Start - hi->BufOff);
  const char* hend = hi->Buf + (hit->End - hi->BufOff);

  // context left of hit
  const auto lbeg = std::reverse_iterator<const char*>(hbeg);
  const auto lend = std::reverse_iterator<const char*>(hi->Buf);

  auto lnl = lbeg;
  for (int i = hi->BeforeContext + 1; i > 0; --i) {
    lnl = std::find(lnl + 1, lend, '\n');
  }

  // context right of hit
  const auto rend = hi->Buf + hi->BufLen;

  auto rnl = hend - 1;
  for (int i = hi->AfterContext + 1; i > 0; --i) {
    rnl = std::find(rnl + 1, rend, '\n');
  }

  if (rnl != rend && *rnl == '\n' && *(rnl-1) == '\r') {
    // Back up one byte on the right end in case of CRLF line endings;
    // not necessary for the left end due to the LF being on the right
    // end of the EOL.
    --rnl;
  }

  // bounds of the hit's context in the buffer
  const char* cbeg = hbeg - (lnl - lbeg);
  const char* cend = rnl;

  // print the line offset
  hi->Out << (hi->BufOff + (cbeg - hi->Buf)) << '\t';

  // print the hit, escaping \t\n\r
  const char esc[] = "\t\n\r";
  for (const char* l = cbeg, *r; l != cend; l = r) {
    r = std::find_first_of(l, cend, esc, esc + 3);
    hi->Out.write(l, r - l);
    if (r != cend) {
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
