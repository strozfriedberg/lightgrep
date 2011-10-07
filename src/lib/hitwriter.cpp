#include "hitwriter.h"

#include <ostream>

void HitWriter::collect(const LG_SearchHit& hit) {
  const std::pair<uint32,uint32>& info(Table[hit.KeywordIndex]);
  Out << hit.Start << '\t' << hit.End << '\t' << info.first << '\t'
      << Keys[info.first] << '\t' << Encodings[info.second] << '\n';
  ++NumHits;
}

void PathWriter::collect(const LG_SearchHit& hit) {
  const std::pair<uint32,uint32>& info(Table[hit.KeywordIndex]);
  Out << Path << '\t' << hit.Start << '\t' << hit.End << '\t'
      << info.first << '\t' << Keys[info.first] << '\t'
      << Encodings[info.second] << '\n';
  ++NumHits;
}
