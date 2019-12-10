#include "recordbuffer.h"

#include "filerecord.h"

#include <iomanip>
#include <sstream>

RecordBuffer::RecordBuffer(const std::string& basePath, unsigned int flushBufSize, OutputBase& out):
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
  CurSize += s.size();
  ++CurSize;
}

void RecordBuffer::flush() {
  ++Num;
  std::stringstream pathBuf;
  pathBuf << BasePath << '-' << std::setfill('0') << std::setw(4) << Num << ".jsonl";
  FileRecord rec;
  rec._data = Buf.str();
  rec.Size = CurSize;
  rec.Path = pathBuf.str();

  Out.outputFile(rec);
  CurSize = 0;
}

size_t RecordBuffer::size() const {
  return CurSize;
}
