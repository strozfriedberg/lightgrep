#include "hitwriter.h"

void HitWriter::collect(const SearchHit& hit) {
  Out << hit.Offset << '\t' << hit.Length << '\t' << hit.Label << '\n';
  ++NumHits;
}
