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
 
 #pragma once

#include <cstdio>
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

  virtual std::future<std::pair<const char*, size_t>> read(size_t len) override;

private:
  FILE* File;
  std::unique_ptr<char[]> Cur, Next;
};

namespace bip = boost::interprocess;

class MemoryMappedFileReader: public Reader {
public:
  MemoryMappedFileReader(const std::string& path);

  virtual std::future<std::pair<const char*, size_t>> read(size_t len) override;

private:
  bip::file_mapping M;
  bip::mapped_region R;
  const char* Buf;
  const char* const Bend;
};
