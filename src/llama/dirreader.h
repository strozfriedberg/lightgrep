#pragma once

#include <filesystem>

#include "dirconversion.h"
#include "inputreader.h"

class InputHandler;

class DirReader: public InputReader {
public:
  DirReader(const std::string& path);

  virtual ~DirReader() {}

  virtual void setInputHandler(std::shared_ptr<InputHandler> in) override;

  virtual bool startReading() override;

  void handleFile(const std::filesystem::directory_entry& de);

private:
  std::string Root;

  std::shared_ptr<InputHandler> Input;

  DirConverter Conv;
};