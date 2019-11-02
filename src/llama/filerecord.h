#pragma once

#include <string>

#include <hasher.h>

// This is just a placeholder
struct FileRecord {
  std::string Path;

  uint64_t Size;

  SFHASH_HashValues Hashes;

  const void *fileBegin() const { return _data.c_str(); }

  const void *fileEnd() const { return _data.c_str() + _data.size(); }

  std::string _data;
};
