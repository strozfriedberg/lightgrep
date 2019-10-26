#pragma once

#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "filerecord.h"

class OutputBase;

class FileScheduler {
public:
  FileScheduler(boost::asio::thread_pool& pool, const std::shared_ptr<OutputBase>& output);

  void scheduleFileBatch(const std::vector<FileRecord>& batch);

private:
  void performScheduling(const std::vector<FileRecord>& batch);

  boost::asio::thread_pool& Pool;
  boost::asio::strand<boost::asio::thread_pool::executor_type> Strand;
  std::shared_ptr<OutputBase> Output;
};
