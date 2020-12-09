#pragma once

#include <memory>
#include <string>
#include <vector>

struct OutputChunk;

class OutputWriter {
public:
  virtual ~OutputWriter() {}

  virtual void outputDirent(const OutputChunk& c) = 0;

  virtual void outputInode(const OutputChunk& c) = 0;

  virtual void outputSearchHit(const std::string& hit) = 0;

  virtual void close() = 0;
};
