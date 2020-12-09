#pragma once

#include <vector>

#include "outputchunk.h"
#include "outputwriter.h"

class MockOutputWriter: public OutputWriter {
public:
  virtual ~MockOutputWriter() {}

  virtual void outputDirent(const OutputChunk& c) override {
     Dirents.push_back(c);
  }

  virtual void outputInode(const OutputChunk& c) override {
    Inodes.push_back(c);
  }

  virtual void outputSearchHit(const std::string& hit) override {}

  virtual void close() override {}

  std::vector<OutputChunk> OutFiles; // TODO: remove
  std::vector<OutputChunk> Dirents;
  std::vector<OutputChunk> Inodes;
};
