#include "searchcontroller.h"
#include "timer.h"

#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

void print_cumulative_stats(double seconds, uint64_t offset) {
  uint64_t units = offset >> 20;
  const double bw = units / seconds;
  units >>= 10;
  std::cerr << units << " GB searched in "
            << seconds << " seconds, "
            << bw << " MB/s avg" << std::endl;
}

bool SearchController::searchFile(
  std::shared_ptr<ContextHandle> searcher,
  HitCounterInfo* hinfo,
  Reader& reader,
  LG_HITCALLBACK_FN callback)
{
  Timer searchClock;

  uint64_t blkSize,
           offset = 0;

  const char* buf;

  std::tie(buf, blkSize) = reader.read(BlockSize).get();
  while (blkSize) {
    // start getting next block
    std::future<std::pair<const char*, size_t>> fut = reader.read(BlockSize);

    // search cur block
    hinfo->setBuffer(buf, blkSize, offset);

    lg_search(
      searcher.get(),
      buf,
      buf + blkSize,
      offset, hinfo, callback
    );

    offset += blkSize;
    if (offset % (1024 * 1024 * 1024) == 0) { // FIXME: should change this due to the block size being variable
      print_cumulative_stats(searchClock.elapsed(), offset);
    }

    std::tie(buf, blkSize) = fut.get(); // block on i/o thread completion
  }

  // assert: all data has been read, offset + blkSize == file size,
  // cur is last block
  hinfo->setBuffer(buf, blkSize, offset);

  lg_search(
    searcher.get(),
    buf,
    buf + blkSize,
    offset, hinfo, callback
  );

  lg_closeout_search(searcher.get(), hinfo, callback);
  offset += blkSize;  // be sure to count the last block

  TotalTime += searchClock.elapsed();
  BytesSearched += offset;
  return true;
}
