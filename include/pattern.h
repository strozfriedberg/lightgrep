#pragma once

#include "basic.h"
#include "encodings.h"

class Pattern {
public:
  std::string Expression;
  bool FixedString, CaseInsensitive;
  uint32 Index;
  std::string Encoding;

  Pattern(const std::string& expr = "",
          bool fixed = false,
          bool insensitive = false,
          uint32 index = 0,
          const std::string& enc = LG_CANONICAL_ENCODINGS[LG_ENC_ASCII]):
    Expression(expr),
    FixedString(fixed),
    CaseInsensitive(insensitive),
    Index(index),
    Encoding(enc) {}

  bool operator==(const Pattern& p) const {
    return FixedString == p.FixedString &&
           CaseInsensitive == p.CaseInsensitive &&
           Index == p.Index &&
           Expression == p.Expression &&
           Encoding == p.Encoding;
  }
};

std::ostream& operator<<(std::ostream&, const Pattern&);
