#pragma once

#include <string>

#include <boost/asio/thread_pool.hpp>

struct FileRecord;

class OutputBase {
public:
  virtual ~OutputBase() {}

  virtual void outputFile(const FileRecord &rec) = 0;
  virtual void outputRecord(const FileRecord &rec) = 0;
  virtual void outputSearchHit(const std::string &hit) = 0;

  static std::shared_ptr<OutputBase>
  createTarWriter(boost::asio::thread_pool &pool, const std::string &path);
};
