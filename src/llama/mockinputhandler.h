#pragma once

#include "inputhandler.h"
#include "filerecord.h"

#include <vector>

class MockInputHandler: public InputHandler {
public:
  virtual ~MockInputHandler() {}

  virtual void push(FileRecord&& f) override {
    batch.push_back(std::move(f));
  }

  virtual void flush() override {}

  std::vector<FileRecord> batch;
};
