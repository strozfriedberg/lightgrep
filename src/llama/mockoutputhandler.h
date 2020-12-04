#pragma once

#include "outputhandler.h"

class MockOutputHandler: public OutputHandler {
public:
  virtual ~MockOutputHandler() {}

  virtual void outputDirent(const FileRecord& rec) override {
    Dirents.push_back(rec);
  }

  virtual void outputInode(const FileRecord& rec) override {
    Inodes.push_back(rec);
  }

  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) override {
    for (const auto& rec: *batch) {
      outputInode(rec);
    }
  }

  virtual void outputSearchHit(const std::string&) override {}

  virtual void outputSearchHits(const std::vector<std::string>&) override {}

  virtual void close() override {}

  std::vector<FileRecord> OutFiles; // TODO: remove
  std::vector<FileRecord> Received; // TODO: remove
  std::vector<FileRecord> Dirents;
  std::vector<FileRecord> Inodes;
};
