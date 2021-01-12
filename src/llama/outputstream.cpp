#include "outputstream.h"

#include "outputchunk.h"

#include <ostream>

void OutputStream::outputImage(const OutputChunk& c) {
  os << c.data;
}

void OutputStream::outputDirent(const OutputChunk& c) {
  os << c.data;
}

void OutputStream::outputInode(const OutputChunk& c) {
  os << c.data;
}

void OutputStream::outputSearchHit(const std::string& hit) {
}

void OutputStream::close() {
  os.flush();
}
