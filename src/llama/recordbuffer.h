#pragma once

#include <sstream>

#include "outputbase.h"

class RecordBuffer {
public:
  RecordBuffer(const std::string& basePath, unsigned int flushBufSize, OutputBase& output);
  ~RecordBuffer();

  void write(const std::string& s);
  void flush();

  std::ostream& get() { return Buf; }

  size_t size() const;

private:
  RecordBuffer(const RecordBuffer&);

  mutable std::stringstream Buf;

  std::string BasePath;

  unsigned int FlushSize,
               CurSize,
               Num;

  OutputBase& Out;
};
