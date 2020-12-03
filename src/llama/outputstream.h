#pragma once

#include <iosfwd>

#include "outputwriter.h"

class OutputStream: public OutputWriter {
public:
  OutputStream(std::ostream& os): os(os) {}

  virtual void outputDirent(const FileRecord& rec) override;

  virtual void outputInode(const FileRecord& rec) override;
  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) override;

  virtual void outputSearchHit(const std::string& hit) override;
  virtual void outputSearchHits(const std::vector<std::string>& batch) override;

  virtual void close() override;

private:
  std::ostream& os;
};
