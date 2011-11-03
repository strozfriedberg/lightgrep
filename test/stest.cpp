
#include "stest.h"

void collector(void* userData, const LG_SearchHit* const hit) {
  STest* stest = static_cast<STest*>(userData);
  stest->Hits.push_back(*static_cast<const SearchHit* const>(hit));
}

