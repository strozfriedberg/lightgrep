#pragma once

#include "outputhandler.h"

class MockOutputHandler: public OutputHandler {
public:
  virtual ~MockOutputHandler() {}

  virtual void outputFile(const FileRecord& rec) override {
    OutFiles.push_back(rec);
  }

  virtual void outputInode(const FileRecord& rec) override {
    Received.push_back(rec);
  }

  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) override {
    for (const auto& rec: *batch) {
      outputInode(rec);
    }
  }

  virtual void outputSearchHit(const std::string&) override {}

  virtual void outputSearchHits(const std::vector<std::string>&) override {}

  virtual void close() override {}

  std::vector<FileRecord> OutFiles;
  std::vector<FileRecord> Received;
};
