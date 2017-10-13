#pragma once

#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <future>
#include <memory>
#include <utility>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

class Reader {
public:
  virtual ~Reader() {}

  virtual std::future<std::pair<const char*, size_t>> read(size_t len) = 0;
};


class FileReader: public Reader {
public:
  FileReader(const std::string& path, size_t blockSize);

  virtual ~FileReader();

  virtual std::future<std::pair<const char*, size_t>> read(size_t len);

private:
  FILE* File;
  std::unique_ptr<char[]> Cur, Next;
};

namespace bip = boost::interprocess;

class MemoryMappedFileReader: public Reader {
public:

  MemoryMappedFileReader(const std::string& path):
    M(path.c_str(), bip::read_only), R(M, bip::read_only),
    Buf(static_cast<const char*>(R.get_address())), Bend(Buf + R.get_size())
  {
    R.advise(bip::mapped_region::advice_sequential);
  }

  virtual std::future<std::pair<const char*, size_t>> read(size_t len) {
    len = std::min(len, static_cast<size_t>(Bend - Buf));
    std::promise<std::pair<const char*, size_t>> p;
    p.set_value(std::make_pair(Buf, len));
    Buf += len;
    return p.get_future();
  }

private:
  bip::file_mapping M;
  bip::mapped_region R;
  const char* Buf;
  const char* const Bend;
};
