#include "filescheduler.h"

#include "outputbase.h"

FileScheduler::FileScheduler(boost::asio::thread_pool& pool, const std::shared_ptr<OutputBase>& output):
  Pool(pool), Strand(Pool.get_executor()), Output(output) {}

void FileScheduler::scheduleFileBatch(const std::vector<FileRecord>& batch) {
  boost::asio::post(Strand, [=]() { performScheduling(batch); }); // lambda [=] means the batch is copied, not shared, between threads
}

void FileScheduler::performScheduling(const std::vector<FileRecord>& batch) {
  // check scratch location capacity and other stuff here
  // this is useful work that can be done on a separate thread from TSK traversal

  // then post for multithreaded processing
  boost::asio::post(Pool, [=](){
    for (auto rec: batch) {
      Output->outputFile(rec);
    }
  });
}
