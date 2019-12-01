#include "filescheduler.h"

#include "options.h"
#include "outputbase.h"
#include "processor.h"

FileScheduler::FileScheduler(boost::asio::thread_pool &pool,
                             const std::shared_ptr<Processor> &protoProc,
                             const std::shared_ptr<OutputBase> &output,
                             const std::shared_ptr<Options> &opts)
    : Pool(pool), Strand(Pool.get_executor()), Output(output),
      ProcMutex(new std::mutex), ProcCV(new std::condition_variable) {
  for (unsigned int i = 0; i < opts->NumThreads; ++i) {
    Processors.push_back(protoProc->clone());
  }
}

void FileScheduler::scheduleFileBatch(const std::vector<FileRecord> &batch) {
  // lambda [=] means the batch is copied, not shared, between threads
  boost::asio::post(Strand, [=]() { performScheduling(batch); });
}

void FileScheduler::performScheduling(const std::vector<FileRecord> &batch) {
  // check scratch location capacity and other stuff here
  // this is useful work that can be done on a separate thread from TSK
  // traversal

  // then post for multithreaded processing
  auto proc = popProc(); // blocks
  boost::asio::post(Pool, [=]() {
    for (auto rec : batch) {
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
    ProcCV->wait(
        lock); // Releases mutex inside wait(), but reacquires before returning
  }
  auto batterUp = Processors.back();
  Processors.pop_back();
  return batterUp;
}

void FileScheduler::pushProc(const std::shared_ptr<Processor> &proc) {
  std::unique_lock<std::mutex> lock(*ProcMutex);
  Processors.push_back(proc);
  ProcCV->notify_one();
}