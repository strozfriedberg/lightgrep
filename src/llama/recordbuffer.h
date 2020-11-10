#pragma once

#include <ostream>
#include <sstream>
#include <string>

class OutputHandler;

class RecordBuffer {
public:
  RecordBuffer(const std::string& basePath, unsigned int flushBufSize, OutputHandler& output);

  ~RecordBuffer();

  RecordBuffer(const RecordBuffer&) = delete;

  void write(const std::string& s);

  void flush();

  std::ostream& get() { return Buf; }

  size_t size() const;

private:
  mutable std::stringstream Buf;

  std::string BasePath;

  unsigned int FlushSize,
               CurSize,
               Num;

  OutputHandler& Out;
};
