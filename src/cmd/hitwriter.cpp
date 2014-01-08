#include "hitwriter.h"

#include <ostream>

void nullWriter(void*userData, const LG_SearchHit* const) {
  HitCounterInfo* hi = static_cast<HitCounterInfo*>(userData);
  ++hi->NumHits;
}

void writeHit(HitWriterInfo* hi, const LG_SearchHit* const hit) {
  const LG_PatternInfo* info = lg_pattern_info(hi->Map, hit->KeywordIndex);

  hi->Out << hit->Start << '\t'
          << hit->End << '\t'
          << reinterpret_cast<uint64_t>(info->UserData) << '\t'
          << info->Pattern << '\t'
          << info->EncodingChain << '\n';

  ++hi->NumHits;
}

void hitWriter(void* userData, const LG_SearchHit* const hit) {
  HitWriterInfo* hi = static_cast<HitWriterInfo*>(userData);
  writeHit(hi, hit);
}

void pathWriter(void* userData, const LG_SearchHit* const hit) {
  PathWriterInfo* hi = static_cast<PathWriterInfo*>(userData);
  hi->Out << hi->Path << '\t';
  writeHit(hi, hit);
}
