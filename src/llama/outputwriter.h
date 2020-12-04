#pragma once

#include <memory>
#include <string>
#include <vector>

struct FileRecord;

class OutputWriter {
public:
  virtual ~OutputWriter() {}

  virtual void outputDirent(const FileRecord& rec) = 0;

  virtual void outputInode(const FileRecord& rec) = 0;

  virtual void outputSearchHit(const std::string& hit) = 0;

  virtual void close() = 0;
};
