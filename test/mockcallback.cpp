
#include "mockcallback.h"

void mockcallback(void* userData, const LG_SearchHit* const hit) {
  reinterpret_cast< std::vector<SearchHit>* >(userData)->push_back(*reinterpret_cast<const SearchHit* const>(hit));
}
