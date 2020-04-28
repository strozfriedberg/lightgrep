#pragma once

#include <string>

#include "boost_asio.h"
#include "options.h"

struct FileRecord;

class OutputBase {
public:
  virtual ~OutputBase() {}

  virtual void outputFile(const FileRecord &rec) = 0;

  virtual void outputInode(const FileRecord &rec) = 0;
  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) {
    for (auto& rec: *batch) { outputInode(rec); }
  }

  virtual void outputSearchHit(const std::string &hit) = 0;
  virtual void outputSearchHits(const std::vector<std::string>& batch) {
    for (auto& hit: batch) { outputSearchHit(hit); }
  }

  virtual void close() = 0;

  static std::shared_ptr<OutputBase>
  createTarWriter(boost::asio::thread_pool &pool, const std::string &path, Options::Codecs codec);
};
