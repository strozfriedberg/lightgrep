#pragma once

#include <memory>
#include <vector>
#include <string>

class FileRecord;

class OutputHandler {
public:
  virtual ~OutputHandler() {}

  virtual void outputDirent(const FileRecord& rec) = 0;

  virtual void outputInode(const FileRecord& rec) = 0;

  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) = 0;

  virtual void outputSearchHit(const std::string&) = 0;

  virtual void outputSearchHits(const std::vector<std::string>& batch) = 0;

  virtual void close() = 0;
}
