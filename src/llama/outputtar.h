#pragma once

#include <memory>
#include <string>

#include "codec.h"
#include "outputwriter.h"

class archive;

class OutputTar: public OutputWriter {
public:
  OutputTar(const std::string& path, Codec codec);

  virtual ~OutputTar() {
    close();
  }

  virtual void outputDirent(const FileRecord& rec) override;

  virtual void outputInode(const FileRecord& rec) override;

  virtual void outputSearchHit(const std::string&) override {
  }

  virtual void close() override {
  }

private:
  void doOutput(const FileRecord& rec);

  std::string Path;

  std::shared_ptr<archive> Archive;
};
