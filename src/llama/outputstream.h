#pragma once

#include <iosfwd>

#include "outputwriter.h"

class OutputStream: public OutputWriter {
public:
  OutputStream(std::ostream& os): os(os) {}

  virtual void outputDirent(const OutputChunk& c) override;

  virtual void outputInode(const OutputChunk& c) override;

  virtual void outputSearchHit(const std::string& hit) override;

  virtual void close() override;

private:
  std::ostream& os;
};
