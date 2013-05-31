#pragma once

#include "pattern.h"

#include <ostream>
#include <string>
#include <vector>

class Key : public Pattern {
public:
  uint32_t UserIndex;

  Key(const std::string& expr = "",
      bool fixed = false,
      bool insensitive = false,
      const std::string& enc = "US-ASCII",
      uint32_t userIndex = 0):
    Pattern(expr, fixed, insensitive, enc),
    UserIndex(userIndex)
  {}

  Key(const Key&) = default;

  Key(Key&&) = default;

  Key& operator=(const Key&) = default;

  Key& operator=(Key&&) = default;

  bool operator==(const Key& k) const {
    return Pattern::operator==(k) && UserIndex == k.UserIndex;
  }
};

std::ostream& operator<<(std::ostream& o, const Key& k);
