#pragma once

#include <memory>
#include <string>

#include "codec.h"
#include "outputbase.h"

class archive;

class OutputTar: public OutputBase {
public:
  OutputTar(const std::string& path, Codec codec);

  virtual ~OutputTar() {
    close();
  }

  virtual void outputFile(const FileRecord& rec) override;

  virtual void outputInode(const FileRecord& rec) override {
  }

  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) override {
  }

  virtual void outputSearchHit(const std::string&) override {
  }

  virtual void outputSearchHits(const std::vector<std::string>& batch) override {
  }

  virtual void close() override {
  }

private:
  std::string Path;

  std::shared_ptr<archive> Archive;
};
