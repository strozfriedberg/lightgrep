#pragma once

#include <memory>
#include <string>
#include <vector>

#include "boost_asio.h"
#include "options.h"

struct FileRecord;

class OutputWriter {
public:
  virtual ~OutputWriter() {}

  virtual void outputFile(const FileRecord& rec) = 0;

  virtual void outputInode(const FileRecord& rec) = 0;
  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) = 0;

  virtual void outputSearchHit(const std::string& hit) = 0;
  virtual void outputSearchHits(const std::vector<std::string>& batch) = 0;

  virtual void close() = 0;
};
