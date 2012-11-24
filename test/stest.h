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

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <vector>

#include "lightgrep_c_api.h"
#include "pattern.h"
#include "searchhit.h"

void collector(void* userData, const LG_SearchHit* const hit);

class STest {
public:
  std::vector<SearchHit> Hits;

  STest(const char* key):
    Prog(nullptr, nullptr), Ctx(nullptr, nullptr)
  {
    init(make_patterns(std::initializer_list<const char*>{key}));
  }

  STest(std::initializer_list<const char*> keys):
    Prog(nullptr, nullptr), Ctx(nullptr, nullptr)
  {
    init(make_patterns(keys));
  }

  template <typename T>
  STest(const T& keys):
    Prog(nullptr, nullptr), Ctx(nullptr, nullptr)
  {
    init(make_patterns(keys));
  }

  STest(const std::vector<Pattern>& patterns):
    Prog(nullptr, nullptr), Ctx(nullptr, nullptr)
  {
    init(patterns);
  }

  void search(const byte* begin, const byte* end, uint64_t offset);

  void startsWith(const byte* begin, const byte* end, uint64_t offset);

  bool parsesButNotValid() const;

private:
  template <typename T>
  static std::vector<Pattern> make_patterns(const T& keys) {
    struct PatternMaker {
      Pattern operator()(const std::string& s) const { return Pattern(s); }
    };

    std::vector<Pattern> pats;
    std::transform(keys.begin(), keys.end(),
                   std::back_inserter(pats), PatternMaker());

    return pats;
  }

  void init(const std::vector<Pattern>& pats);

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> Prog;
  std::unique_ptr<ContextHandle,void(*)(ContextHandle*)> Ctx;
};
