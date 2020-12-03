#include "outputstream.h"

#include "filerecord.h"

#include <ostream>

void OutputStream::outputDirent(const FileRecord& rec) {
  os << rec._data;
}

void OutputStream::outputInode(const FileRecord& rec) {
  os << rec._data;
}

void OutputStream::outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) {
}

void OutputStream::outputSearchHit(const std::string& hit) {
}

void OutputStream::outputSearchHits(const std::vector<std::string>& batch) {
}

void OutputStream::close() {
  os.flush();
}
