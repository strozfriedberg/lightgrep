#include <stdexcept>

#include "reader.h"

namespace {

FILE* try_open(const std::string& path) {
  if (path == "-") {
    return stdin;
  }
  else {
    FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) {
      throw std::runtime_error(std::strerror(errno));
    }
    return f;
  }
}

}

FileReader::FileReader(const std::string& path, size_t blockSize):
    File(try_open(path)), Cur(new char[blockSize]), Next(new char[blockSize])
{
  std::setbuf(File, 0); // unbuffered, bitte
}

FileReader::~FileReader() {
  std::fclose(File);
}

// TODO: would this be better as a 2-element circular buffer, and just
// reuse the read thread?
std::future<std::pair<const char*, size_t>> FileReader::read(size_t len){
  std::swap(Cur, Next);
  return std::async(
    std::launch::async,
    [](char* buf, size_t len, FILE* file) {
      return std::pair<const char*, size_t>{
        buf, std::fread(buf, 1, len, file)
      };
    },
    Next.get(), len, File
  );
}
