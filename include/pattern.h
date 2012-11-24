/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "basic.h"
#include "lightgrep/encodings.h"

#include <vector>

class Pattern {
public:
  std::string Expression;
  bool FixedString, CaseInsensitive;
  uint32_t Index;
  std::string Encoding;

  Pattern(const std::string& expr = "",
          bool fixed = false,
          bool insensitive = false,
          uint32_t index = 0,
          const std::string& enc = LG_CANONICAL_ENCODINGS[LG_ENC_ASCII]):
    Expression(expr),
    FixedString(fixed),
    CaseInsensitive(insensitive),
    Index(index),
    Encoding(enc) {}

  Pattern(const Pattern&) = default;

  Pattern(Pattern&&) = default;

  Pattern& operator=(const Pattern&) = default;

  Pattern& operator=(Pattern&&) = default;

  bool operator==(const Pattern& p) const {
    return FixedString == p.FixedString &&
           CaseInsensitive == p.CaseInsensitive &&
           Index == p.Index &&
           Expression == p.Expression &&
           Encoding == p.Encoding;
  }
};

std::ostream& operator<<(std::ostream&, const Pattern&);
