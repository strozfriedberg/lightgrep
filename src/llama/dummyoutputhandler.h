#pragma once

#include "outputhandler.h"

class DummyOutputHandler: public OutputHandler {
public:
  virtual ~DummyOutputHandler() {}

  virtual void outputImage(const FileRecord& rec) override {
  }

  virtual void outputDirent(const FileRecord& rec) override {
  }

  virtual void outputInode(const FileRecord& rec) override {
  }

  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) override {
  }

  virtual void outputSearchHit(const std::string&) override {}

  virtual void outputSearchHits(const std::vector<std::string>&) override {}

  virtual void close() override {}
};
