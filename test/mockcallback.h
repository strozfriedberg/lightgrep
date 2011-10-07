#pragma once

#include "vm.h"

/*
class MockCallback: public HitCallback {
public:
  virtual void collect(const SearchHit& hit) {
    Hits.push_back(hit);
  }

  std::vector<SearchHit> Hits;
};
*/

void mockcallback(void* userData, const LG_SearchHit* const hit);

