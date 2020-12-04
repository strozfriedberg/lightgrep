#include "outputstream.h"

#include "filerecord.h"

#include <ostream>

void OutputStream::outputDirent(const FileRecord& rec) {
  os << rec._data;
}

void OutputStream::outputInode(const FileRecord& rec) {
  os << rec._data;
}

void OutputStream::outputSearchHit(const std::string& hit) {
}

void OutputStream::close() {
  os.flush();
}
