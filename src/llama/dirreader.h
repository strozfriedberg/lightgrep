#pragma once

#include "inputreader.h"

class InputHandler;

class DirReader: public InputReader {
public:
  DirReader(const std::string& path);

  virtual ~DirReader() {}

  virtual void setInputHandler(std::shared_ptr<InputHandler> in) override;

  virtual bool startReading() override;

private:
  std::string Root;

  std::shared_ptr<InputHandler> Input;
};
