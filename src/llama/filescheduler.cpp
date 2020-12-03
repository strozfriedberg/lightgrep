#include "filescheduler.h"

#include "filerecord.h"
#include "options.h"
#include "outputhandler.h"
#include "processor.h"

FileScheduler::FileScheduler(boost::asio::thread_pool& pool,
                             const std::shared_ptr<Processor>& protoProc,
                             const std::shared_ptr<OutputHandler>& output,
                             const std::shared_ptr<Options>& opts)
    : Pool(pool), Strand(Pool.get_executor()), Output(output),
      ProcMutex(new std::mutex), ProcCV(new std::condition_variable) {
  for (unsigned int i = 0; i < opts->NumThreads; ++i) {
    Processors.push_back(protoProc->clone());
  }
}

void FileScheduler::scheduleFileBatch(const std::shared_ptr<std::vector<FileRecord>>& batch) {
  // lambda [=] means the batch is copied, not shared, between threads
  boost::asio::post(Strand, [=]() { performScheduling(batch); });
}

void FileScheduler::performScheduling(const std::shared_ptr<std::vector<FileRecord>>& batch) {
  // check scratch location capacity and other stuff here
  // this is useful work that can be done on a separate thread from TSK
  // traversal

  Output->outputInodes(batch);
  // then post for multithreaded processing
  auto proc = popProc(); // blocks
  boost::asio::post(Pool, [=]() {
    for (auto rec : *batch) {
      proc->process(rec, *Output);
    }
    this->pushProc(proc);
  });
}

std::shared_ptr<Processor> FileScheduler::popProc() {
  // Having a fixed number of Processor objects adds back pressure to
  // FileScheduler here -- it cannot dispatch more batches beyond the
  // size of the Processor pool.
  std::unique_lock<std::mutex> lock(*ProcMutex);
  while (Processors.empty()) {
    // Releases mutex inside wait(), but reacquires before returning
    ProcCV->wait(lock);
  }
  auto batterUp = Processors.back();
  Processors.pop_back();
  return batterUp;
}

void FileScheduler::pushProc(const std::shared_ptr<Processor>& proc) {
  std::unique_lock<std::mutex> lock(*ProcMutex);
  Processors.push_back(proc);
  ProcCV->notify_one();
}
