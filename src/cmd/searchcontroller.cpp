#include "searchcontroller.h"

#include <chrono>
#include <cstdio>
#include <future>
#include <iostream>
#include <thread>

uint64_t readNext(FILE* file, char* buf, unsigned int blockSize) {
  return std::fread(static_cast<void*>(buf), 1, blockSize, file);
}

class Timer {
public:
  double elapsed() const {
    return std::chrono::duration<double>(
      std::chrono::high_resolution_clock::now() - start
    ).count();
  }

private:
  const std::chrono::time_point<std::chrono::high_resolution_clock> start =
    std::chrono::high_resolution_clock::now();
};

bool SearchController::searchFile(
  std::shared_ptr<ContextHandle> searcher,
  HitCounterInfo* hinfo,
  FILE* file,
  LG_HITCALLBACK_FN callback)
{
  Timer searchClock;

  uint64_t blkSize = 0,
           offset = 0;

  blkSize = readNext(file, Cur.get(), BlockSize);
  while (!std::feof(file)) {
    // read the next block on a separate thread
    std::packaged_task<uint64_t(FILE*, char*, unsigned int)> task(readNext);
    std::future<uint64_t> sizeFut = task.get_future();
    std::thread exec(std::move(task), file, Next.get(), BlockSize);

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

    exec.join();
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
