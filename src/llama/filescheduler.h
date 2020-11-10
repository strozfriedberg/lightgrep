#pragma once

#include <memory>
#include <vector>

#include <condition_variable>
#include <mutex>

#include "boost_asio.h"

class FileRecord;
struct Options;
class OutputHandler;
class Processor;

class FileScheduler {
public:
  FileScheduler(boost::asio::thread_pool& pool,
                const std::shared_ptr<Processor>& protoProc,
                const std::shared_ptr<OutputHandler>& output,
                const std::shared_ptr<Options>& opts);

  void scheduleFileBatch(const std::shared_ptr<std::vector<FileRecord>>& batch);

private:
  void performScheduling(const std::shared_ptr<std::vector<FileRecord>>& batch);

  std::shared_ptr<Processor> popProc();
  void pushProc(const std::shared_ptr<Processor>& proc);

  boost::asio::thread_pool& Pool;
  boost::asio::strand<boost::asio::thread_pool::executor_type> Strand;
  std::shared_ptr<OutputHandler> Output;

  std::vector<std::shared_ptr<Processor>> Processors;

  std::unique_ptr<std::mutex> ProcMutex;

  std::unique_ptr<std::condition_variable> ProcCV;
};
