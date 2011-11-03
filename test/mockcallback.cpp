
#include "searchhit.h"
#include "mockcallback.h"

#include <vector>

void mockCallback(void* userData, const LG_SearchHit* const hit) {
  std::vector<SearchHit>& hits(*static_cast<std::vector<SearchHit>*>(userData));
  hits.push_back(*static_cast<const SearchHit* const>(hit));
}
