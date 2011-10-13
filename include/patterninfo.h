#pragma once

#include <string>
#include <vector>
#include <utility>

struct PatternInfo {
  std::vector<std::string> Patterns,
                           Encodings;
  std::vector< std::pair<uint32, uint32> > Table;
};
