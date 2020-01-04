#pragma once

#include <memory>
#include <string>

class FileScheduler;

class InputReaderBase {
public:
  virtual ~InputReaderBase() {}
  virtual bool startReading(const std::shared_ptr<FileScheduler>&) = 0;

  static std::shared_ptr<InputReaderBase> createTSK(const std::string &imgName);
  static std::shared_ptr<InputReaderBase> createDir(const std::string &dirPath);
};
