#include "reader.h"

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
