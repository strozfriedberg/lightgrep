#include "searchcontroller.h"

#include <cstdio>
#include <iostream>

// FIXME: Replace boost::thread with std::thread
#include <boost/thread.hpp>
// FIXME: Replace boost::timer with something from std::chrono
#include <boost/timer.hpp>

uint64_t readNext(FILE* file, char* buf, unsigned int blockSize) {
  return std::fread(static_cast<void*>(buf), 1, blockSize, file);
}

bool SearchController::searchFile(
  std::shared_ptr<ContextHandle> searcher,
  HitCounterInfo* hinfo,
  FILE* file,
  LG_HITCALLBACK_FN callback)
{
  boost::timer searchClock;
  uint64_t blkSize = 0,
           offset = 0;

  blkSize = readNext(file, Cur.get(), BlockSize);
  while (!std::feof(file)) {
    // read the next block on a separate thread
    boost::packaged_task<uint64_t> task(
      std::bind(&readNext, file, Next.get(), BlockSize)
    );
    boost::unique_future<uint64_t> sizeFut = task.get_future();
    boost::thread exec(std::move(task));

    // search cur block
    hinfo->setBuffer(Cur.get(), blkSize, offset);

    lg_search(
      searcher.get(),
      Cur.get(),
      Cur.get() + blkSize,
      offset, hinfo, callback
    );

    offset += blkSize;
    if (offset % (1024 * 1024 * 1024) == 0) { // FIXME: should change this due to the block size being variable
      const double lastTime = searchClock.elapsed();
      uint64_t units = offset >> 20;
      const double bw = units / lastTime;
      units >>= 10;
      std::cerr << units << " GB searched in " << lastTime
                << " seconds, " << bw << " MB/s avg" << std::endl;
    }
    blkSize = sizeFut.get(); // block on i/o thread completion
    Cur.swap(Next);
  }

  // assert: all data has been read, offset + blkSize == file size,
  // cur is last block
  hinfo->setBuffer(Cur.get(), blkSize, offset);

  lg_search(
    searcher.get(),
    Cur.get(),
    Cur.get() + blkSize,
    offset, hinfo, callback
  );

  lg_closeout_search(searcher.get(), hinfo, callback);
  offset += blkSize;  // be sure to count the last block

  TotalTime += searchClock.elapsed();
  BytesSearched += offset;
  return true;
}
