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

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <vector>

#include "lightgrep/api.h"

#include "pattern.h"
#include "searchhit.h"

class STest {
public:
  using ProgPtr = std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)>;

  std::vector<SearchHit> Hits;
  ProgPtr Prog;
  uint64_t RetVal;

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

  STest(ProgPtr prog):
    Hits(), Prog(std::move(prog)), RetVal(0), Ctx(nullptr, nullptr)
  {
    LG_ContextOptions ctxOpts;
    Ctx = std::unique_ptr<ContextHandle, void(*)(ContextHandle*)>(
      lg_create_context(Prog.get(), &ctxOpts),
      lg_destroy_context
    );
  }

  void search(const char* begin, const char* end, uint64_t offset);

  void search(const std::string& s, uint64_t offset = 0) { search(s.data(), s.data() + s.length(), offset); }

  void startsWith(const char* begin, const char* end, uint64_t offset);

  void startsWith(const std::string& s, uint64_t offset = 0) { startsWith(s.data(), s.data() + s.length(), offset); }

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

  std::unique_ptr<ContextHandle,void(*)(ContextHandle*)> Ctx;
};
