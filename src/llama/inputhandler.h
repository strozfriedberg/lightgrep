#pragma once

class FileRecord;

class InputHandler {
public:
  virtual ~InputHandler() {}

  virtual void push(FileRecord&& f) = 0;

  virtual void flush() = 0;
};
