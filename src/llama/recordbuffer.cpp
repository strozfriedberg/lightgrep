#include "recordbuffer.h"

#include "filerecord.h"
#include "outputhandler.h"

#include <iomanip>
#include <iostream>

RecordBuffer::RecordBuffer(const std::string& basePath, unsigned int flushBufSize, OutputHandler& out):
  Buf(), BasePath(basePath), FlushSize(flushBufSize), CurSize(0), Num(0), Out(out) {}

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
  FileRecord rec;
  rec._data = Buf.str();
  rec.Size = size();
  rec.Path = pathBuf.str();

  // std::cerr << "RecordBuffer flushing " << rec.Path << " (" << rec.Size << " bytes)" << std::endl;
  Out.outputFile(rec);
  Buf.str("");
}

size_t RecordBuffer::size() const {
  return Buf.tellp();
}
