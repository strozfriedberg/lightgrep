#include "hitwriter.h"

void HitWriter::collect(const SearchHit& hit) {
  std::pair< uint32, uint32 > info(Table[hit.Label]);
  Out << hit.Offset << '\t' << hit.Length << '\t' << info.first << '\t'
    << Keys[info.first] << '\t' << Encodings[info.second] << '\n';
  ++NumHits;
}

void PathWriter::collect(const SearchHit& hit) {
  std::pair< uint32, uint32 > info(Table[hit.Label]);
  Out << Path << '\t' << hit.Offset << '\t' << hit.Length << '\t' << info.first << '\t'
    << Keys[info.first] << '\t' << Encodings[info.second] << '\n';
  ++NumHits;
}
