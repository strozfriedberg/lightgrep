#pragma once

#include "hitwriter.h"
#include "reader.h"

#include <lightgrep/api.h>

class SearchController {
public:
  SearchController(uint32_t blkSize):
    BlockSize(blkSize),
    BytesSearched(0),
    TotalTime(0.0) {}

  bool searchFile(
    std::shared_ptr<ContextHandle> searcher,
    HitCounterInfo* hinfo,
    Reader& reader,
    LG_HITCALLBACK_FN callback
  );

  size_t BlockSize;
  uint64_t BytesSearched;
  double TotalTime;
};
