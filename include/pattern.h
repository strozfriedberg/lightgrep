#pragma once

#include "basic.h"

class Pattern {
public:
  std::string Expression;
  bool        FixedString,
              CaseInsensitive;
  std::string Encoding;

  Pattern(const std::string& expr = "", bool fixed = false, bool insensitive = false, const std::string& enc = ""):
    Expression(expr), FixedString(fixed), CaseInsensitive(insensitive), Encoding(enc) {}

  bool operator==(const Pattern& p) const {
    return FixedString == p.FixedString && CaseInsensitive == p.CaseInsensitive &&
      Expression == p.Expression && Encoding == p.Encoding;
  }
};

std::ostream& operator<<(std::ostream&, const Pattern&);
