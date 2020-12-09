#include "recordbuffer.h"

#include "outputchunk.h"
#include "outputhandler.h"

#include <iomanip>
#include <iostream>

RecordBuffer::RecordBuffer(
  const std::string& basePath,
  unsigned int flushBufSize,
  std::function<void(const OutputChunk&)> output
):
  Buf(),
  BasePath(basePath),
  FlushSize(flushBufSize),
  CurSize(0),
  Num(0), Out(output) {}

RecordBuffer::~RecordBuffer() {
  if (size()) {
    flush();
  }
}

void RecordBuffer::write(const std::string& s) {
  if (size() >= FlushSize) {
    flush();
  }
  Buf << s << '\n';
}

void RecordBuffer::flush() {
  ++Num;
  std::stringstream pathBuf;
  pathBuf << BasePath << '-' << std::setfill('0') << std::setw(4) << Num << ".jsonl";
  OutputChunk c{size(), pathBuf.str(), Buf.str()};

  std::cerr << "RecordBuffer flushing " << c.path << " (" << c.size << " bytes)" << std::endl;
  Out(c);
  Buf.str("");
}

size_t RecordBuffer::size() const {
  return Buf.tellp();
}
