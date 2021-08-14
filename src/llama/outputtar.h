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

  virtual void outputImage(const OutputChunk& c) override;

  virtual void outputDirent(const OutputChunk& c) override;

  virtual void outputInode(const OutputChunk& c) override;

  virtual void outputSearchHit(const std::string&) override {
  }

  virtual void close() override {
  }

private:
  void doOutput(const OutputChunk& c);
  void doOutput(const char* path, const char* data, size_t len);

  std::string Path;

  std::shared_ptr<archive> Archive;
};
