#include "hitwriter.h"
#include "encodings.h"

#include <ostream>

void nullWriter(void*userData, const LG_SearchHit* const) {
  HitCounterInfo* hi = static_cast<HitCounterInfo*>(userData);
  ++hi->NumHits;
}

void writeHit(HitWriterInfo* hi, const LG_SearchHit* const hit) {
  const std::pair<uint32,uint32>& info(hi->Table[hit->KeywordIndex]);
  hi->Out << hit->Start << '\t'
          << hit->End << '\t'
          << info.first << '\t'
          << hi->Patterns[info.first].Expression << '\t'
          << LG_CANONICAL_ENCODINGS[info.second] << '\n';
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
