#pragma once

#include <cstdio>
#include <memory>

#include "basic.h"
#include "hitwriter.h"
#include "lightgrep/api.h"

class SearchController {
public:
  SearchController(uint32_t blkSize):
    BlockSize(blkSize),
    Cur(new char[blkSize]),
    Next(new char[blkSize]) {}

  bool searchFile(
    std::shared_ptr<ContextHandle> search,
    HitCounterInfo* hinfo,
    FILE* file,
    LG_HITCALLBACK_FN callback
  );

  uint32_t BlockSize;
  uint64_t BytesSearched;
  double TotalTime;
  std::unique_ptr<char[]> Cur, Next;
};
