/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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
  ContextHandle* searcher,
  HitOutputData* hinfo,
  Reader& reader,
  LG_HITCALLBACK_FN callback)
{
  Timer searchClock;
  double thisTime, lastTime = searchClock.elapsed();

  uint64_t blkSize,
           offset = 0;

  const char* buf;

  std::tie(buf, blkSize) = reader.read(BlockSize).get();
  while (blkSize) {
    // start getting next block
    std::future<std::pair<const char*, size_t>> fut = reader.read(BlockSize);

    // search cur block
    hinfo->setBuffer(buf, blkSize, offset);

    lg_search(searcher, buf, buf + blkSize, offset, hinfo, callback);

    offset += blkSize;

    thisTime = searchClock.elapsed();
    if (thisTime - lastTime > 30.0) {
      print_cumulative_stats(searchClock.elapsed(), offset);
      lastTime = thisTime;
    }

    std::tie(buf, blkSize) = fut.get(); // block on i/o thread completion
  }

  // assert: all data has been read, offset + blkSize == file size,
  // cur is last block
  hinfo->setBuffer(buf, blkSize, offset);

  lg_search(searcher, buf, buf + blkSize, offset, hinfo, callback);

  lg_closeout_search(searcher, hinfo, callback);
  offset += blkSize;  // be sure to count the last block

  TotalTime += searchClock.elapsed();
  BytesSearched += offset;
  return true;
}
