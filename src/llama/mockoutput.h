#pragma once

#include <vector>

#include "outputbase.h"

class MockOutput: public OutputBase {
public:
  virtual ~MockOutput() {}

  virtual void outputFile(const FileRecord &rec) override {
    OutFiles.push_back(rec);
  }

  virtual void outputInode(const FileRecord &rec) override {
    Received.push_back(rec);
  }

  virtual void outputSearchHit(const std::string &) override {}

  virtual void close() override {}

  std::vector<FileRecord> OutFiles;
  std::vector<FileRecord> Received;
};
