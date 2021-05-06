#pragma once

#include <filesystem>

#include "dirconversion.h"
#include "direntstack.h"
#include "inputreader.h"
#include "recordhasher.h"

class InputHandler;

class DirReader: public InputReader {
public:
  DirReader(const std::string& path);

  virtual ~DirReader() {}

  virtual void setInputHandler(std::shared_ptr<InputHandler> in) override;

  virtual void setOutputHandler(std::shared_ptr<OutputHandler> in) override;

  virtual bool startReading() override;

  void handleFile(const std::filesystem::directory_entry& de);

private:
  void finishDirent();

  std::string Root;

  std::shared_ptr<InputHandler> Input;
  std::shared_ptr<OutputHandler> Output;

  DirConverter Conv;

  DirentStack Dirents;
  RecordHasher RecHasher;
};
