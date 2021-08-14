#pragma once

#include <functional>
#include <ostream>
#include <sstream>
#include <string>

class OutputChunk;

class RecordBuffer {
public:
  RecordBuffer(
    const std::string& basePath,
    unsigned int flushBufSize,
    std::function<void(const OutputChunk&)> output
  );

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

  std::function<void(const OutputChunk&)> Out;
};
