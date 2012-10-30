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
#include <vector>

#include "fwd_pointers.h"
#include "pattern.h"
#include "vm_interface.h"

void collector(void* userData, const LG_SearchHit* const hit);

struct STest {
  std::vector<SearchHit> Hits;
  NFAPtr Fsm;
  ProgramPtr Prog;
  std::shared_ptr<VmInterface> Grep;

  STest(const char* key);

  STest(std::initializer_list<const char*> keys);

  STest(const std::vector<Pattern>& patterns);

  template <typename T>
  STest(const T& keys) {
    init(keys);
  }

  template <typename T>
  void init(const T& keys) {
    struct PatternMaker {
      Pattern operator()(const std::string& s) { return Pattern(s); }
    };

    std::vector<Pattern> pats;
    std::transform(keys.begin(), keys.end(),
                   std::back_inserter(pats), PatternMaker());

    init(pats);
  }

  void init(std::vector<Pattern>& pats);

  void search(const byte* begin, const byte* end, uint64 offset);

  void startsWith(const byte* begin, const byte* end, uint64 offset);

  static bool parsesButNotValid(const std::string& pattern);
};
