#pragma once

#include "basic.h"

class Pattern {
public:
  std::string Expression;
  bool        FixedString,
              CaseInsensitive;

  Pattern(const std::string& expr = "", bool fixed = false, bool nocase = false):
    Expression(expr), FixedString(fixed), CaseInsensitive(nocase) {}
};
