#pragma once

#include <cstdio>
#include <memory>

#include "basic.h"
#include "hitwriter.h"
#include "lightgrep_c_api.h"

class SearchController {
public:
  SearchController(uint32 blkSize):
    BlockSize(blkSize),
    Cur(new char[blkSize]),
    Next(new char[blkSize]) {}

  bool searchFile(
    std::shared_ptr<ContextHandle> search,
    HitCounterInfo* hinfo,
    FILE* file,
    LG_HITCALLBACK_FN callback
  );

  uint32 BlockSize;
  uint64 BytesSearched = 0;
  double TotalTime = 0.0;
  std::unique_ptr<char[]> Cur, Next;
};
