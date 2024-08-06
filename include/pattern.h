/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "basic.h"

class Pattern {
public:
  std::string Expression;
  bool        FixedString,
              CaseInsensitive,
              UnicodeMode;
  std::string Encoding;

  Pattern(const char* expr,
          bool fixed = false,
          bool insensitive = false,
          bool unicode_mode = false,
          const std::string& enc = "US-ASCII"):
    Expression(expr),
    FixedString(fixed),
    CaseInsensitive(insensitive),
    UnicodeMode(unicode_mode),
    Encoding(enc) {}

  Pattern(const std::string& expr = "",
          bool fixed = false,
          bool insensitive = false,
          bool unicode_mode = false,
          const std::string& enc = "US-ASCII"):
    Expression(expr),
    FixedString(fixed),
    CaseInsensitive(insensitive),
    UnicodeMode(unicode_mode),
    Encoding(enc) {}

  Pattern(const Pattern&) = default;

  Pattern(Pattern&&) = default;

  Pattern& operator=(const Pattern&) = default;

  Pattern& operator=(Pattern&&) = default;

  bool operator==(const Pattern& p) const {
    return FixedString == p.FixedString &&
           CaseInsensitive == p.CaseInsensitive &&
           UnicodeMode == p.UnicodeMode &&
           Expression == p.Expression &&
           Encoding == p.Encoding;
  }

  virtual ~Pattern() {}
};

std::ostream& operator<<(std::ostream&, const Pattern&);
