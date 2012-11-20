#include "searchcontroller.h"

#include <cstdio>
#include <iostream>

#include <boost/timer.hpp>

#include "include_boost_thread.h"

uint64 readNext(FILE* file, char* buf, unsigned int blockSize) {
  return std::fread(static_cast<void*>(buf), 1, blockSize, file);
}

bool SearchController::searchFile(
  std::shared_ptr<ContextHandle> searcher,
  HitCounterInfo* hinfo,
  FILE* file,
  LG_HITCALLBACK_FN callback)
{
  boost::timer searchClock;
  uint64 blkSize = 0,
         offset = 0;

  blkSize = readNext(file, Cur.get(), BlockSize);
  if (!feof(file)) {
    do {
      // read the next block on a separate thread
      boost::packaged_task<uint64> task(
        std::bind(&readNext, file, Next.get(), BlockSize)
      );
      boost::unique_future<uint64> sizeFut = task.get_future();
      boost::thread exec(std::move(task));

      // search cur block
      lg_search(
        searcher.get(),
        Cur.get(),
        Cur.get() + blkSize,
        offset, hinfo, callback
      );

      offset += blkSize;
      if (offset % (1024 * 1024 * 1024) == 0) { // FIXME: should change this due to the block size being variable
        const double lastTime = searchClock.elapsed();
        uint64 units = offset >> 20;
        const double bw = units / lastTime;
        units >>= 10;
        std::cerr << units << " GB searched in " << lastTime
                  << " seconds, " << bw << " MB/s avg" << std::endl;
      }
      blkSize = sizeFut.get(); // block on i/o thread completion
      Cur.swap(Next);
    } while (!feof(file)); // note file is shared btwn threads, but safely
  }

  // assert: all data has been read, offset + blkSize == file size,
  // cur is last block
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
