#pragma once

#include <string>

#include <hasher.h>

// This is just a placeholder
struct FileRecord {
  std::string Path;

  uint64_t Size;

  std::string _data;

  SFHASH_HashValues Hashes;

  const char* fileBegin() const { return _data.c_str(); }

  const char* fileEnd() const { return _data.c_str() + _data.size(); }
};
