#pragma once

#include <string>
#include <vector>
#include <utility>

#include "pattern.h"

struct PatternInfo {
  virtual ~PatternInfo() {}

  std::vector<Pattern> Patterns;
  std::vector<std::pair<uint32, uint32>> Table;
};
