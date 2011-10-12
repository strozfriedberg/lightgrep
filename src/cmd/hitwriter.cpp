#include "hitwriter.h"

#include <ostream>

void nullWriter(void*, const LG_SearchHit* const) {}

void hitWriter(void* userData, const LG_SearchHit* const hit) {
  HitWriterInfo* hi = reinterpret_cast<HitWriterInfo*>(userData);
  
  const std::pair<uint32,uint32>& info(hi->Table[hit->KeywordIndex]);
  hi->Out << hit->Start << '\t'
          << hit->End << '\t'
          << info.first << '\t'
          << hi->Patterns[info.first] << '\t'
          << hi->Encodings[info.second] << '\n';
  ++hi->NumHits;
}

void pathWriter(void* userData, const LG_SearchHit* const hit) {
  PathWriterInfo* hi = reinterpret_cast<PathWriterInfo*>(userData);
  
  const std::pair<uint32,uint32>& info(hi->Table[hit->KeywordIndex]);
  hi->Out << hi->Path << '\t'
          << hit->Start << '\t'
          << hit->End << '\t'
          << info.first << '\t'
          << hi->Patterns[info.first] << '\t'
          << hi->Encodings[info.second] << '\n';
  ++hi->NumHits;
}

