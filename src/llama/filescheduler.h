#pragma once

#include <memory>
#include <vector>

#include <condition_variable>
#include <mutex>

#include <boost/asio.hpp>

#include "filerecord.h"

struct Options;
class OutputBase;
class Processor;

class FileScheduler {
public:
  FileScheduler(boost::asio::thread_pool& pool,
    const std::shared_ptr<Processor>& protoProc,
    const std::shared_ptr<OutputBase>& output,
    const std::shared_ptr<Options>& opts);

  void scheduleFileBatch(const std::vector<FileRecord>& batch);

private:
  void performScheduling(const std::vector<FileRecord>& batch);

  std::shared_ptr<Processor> popProc();
  void pushProc(const std::shared_ptr<Processor>& proc);

  boost::asio::thread_pool& Pool;
  boost::asio::strand<boost::asio::thread_pool::executor_type> Strand;
  std::shared_ptr<OutputBase> Output;

  std::vector<std::shared_ptr<Processor>> Processors;

  std::unique_ptr<std::mutex> ProcMutex;

  std::unique_ptr<std::condition_variable> ProcCV;
};
