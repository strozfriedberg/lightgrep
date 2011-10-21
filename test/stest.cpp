
#include "stest.h"

void collector(void* userData, const LG_SearchHit* const hit) {
  reinterpret_cast<STest*>(userData)->Hits.push_back(*reinterpret_cast<const SearchHit* const>(hit));
}

