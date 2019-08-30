#pragma once

#include <memory>
#include <vector>

#include "lightgrep/api.h"

struct PatternMap {
  std::vector<LG_PatternInfo> Patterns;

  PatternMap(unsigned int sizeHint): Patterns() { Patterns.reserve(sizeHint); }

  ~PatternMap() {
    for (LG_PatternInfo& pi: Patterns) {
      delete[] pi.Pattern;
      delete[] pi.EncodingChain;
    }
  }

  void addPattern(const char* pattern, const char* chain, uint64_t index);

  size_t bufSize() const;
  std::vector<char> marshall() const;
  static std::unique_ptr<PatternMap> unmarshall(const void* buf, size_t len);

  bool operator==(const PatternMap& rhs) const;
};

bool operator==(const LG_PatternInfo& lhs, const LG_PatternInfo& rhs);
