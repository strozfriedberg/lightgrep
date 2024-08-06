/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <algorithm>
#include <cerrno>
#include <cstring>
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
      const size_t alen = std::fread(buf, 1, len, file);
      if (std::ferror(file)) {
        throw std::runtime_error(std::strerror(errno));
      }
      return std::pair<const char*, size_t>{buf, alen};
    },
    Next.get(), len, File
  );
}

MemoryMappedFileReader::MemoryMappedFileReader(const std::string& path):
  M(path.c_str(), bip::read_only), R(M, bip::read_only),
  Buf(static_cast<const char*>(R.get_address())), Bend(Buf + R.get_size())
{
  R.advise(bip::mapped_region::advice_sequential);
}

std::future<std::pair<const char*, size_t>> MemoryMappedFileReader::read(size_t len) {
  len = std::min(len, static_cast<size_t>(Bend - Buf));
  std::promise<std::pair<const char*, size_t>> p;
  p.set_value(std::make_pair(Buf, len));
  Buf += len;
  return p.get_future();
}
