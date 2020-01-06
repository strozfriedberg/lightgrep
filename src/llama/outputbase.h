#pragma once

#include <string>

#include "boost_asio.h"

struct FileRecord;

class OutputBase {
public:
  virtual ~OutputBase() {}

  virtual void outputFile(const FileRecord &rec) = 0;

  virtual void outputRecord(const FileRecord &rec) = 0;
  virtual void outputRecords(const std::shared_ptr<std::vector<FileRecord>>& batch) {
    for (auto& rec: *batch) { outputRecord(rec); }
  }

  virtual void outputSearchHit(const std::string &hit) = 0;
  virtual void outputSearchHits(const std::vector<std::string>& batch) {
    for (auto& hit: batch) { outputSearchHit(hit); }
  }

  static std::shared_ptr<OutputBase>
  createTarWriter(boost::asio::thread_pool &pool, const std::string &path);
};
