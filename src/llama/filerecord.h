#pragma once

#include <string>
#include <sstream>
#include <hasher.h>

// This is just a placeholder
struct FileRecord {
  std::string Path;

  uint64_t Size;

  std::string _data;

  SFHASH_HashValues Hashes;

  const char* fileBegin() const { return _data.c_str(); }

  const char* fileEnd() const { return _data.c_str() + _data.size(); }

  std::string str() const {
    std::string ret;
    ret.reserve(Path.size() * 2);
    ret.append("{\"Path\":\"").append(Path).append("\", \"Size\":").append(std::to_string(Size)).append("}");
    return ret;
  }
};
