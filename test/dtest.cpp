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

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "basic.h"
#include "pattern.h"
#include "searchhit.h"

#include "data_reader.h"
#include "dtest.h"
#include "executor.h"
#include "stest.h"

namespace {
  struct TestCase {
    std::vector<Pattern> patterns;
    std::string text;
    std::vector<SearchHit> expected;

    void operator()() {
      STest test(patterns);
      test.search(text.c_str(), text.c_str() + text.length(), 0);

      std::vector<SearchHit>& actual = test.Hits;

      REQUIRE(expected.size() == actual.size());

      std::sort(expected.begin(), expected.begin());
      std::sort(actual.begin(), actual.end());

      std::pair<std::vector<SearchHit>::iterator,
                std::vector<SearchHit>::iterator> mis(
        std::mismatch(expected.begin(), expected.end(), actual.begin())
      );

      if (mis.first != expected.end()) {
        // This is guaranteed to fail. We assert just to get the message.
        REQUIRE(*mis.first == *mis.second);
      }
    }
  };
}

void DTest::run(const char* path) {
  std::ifstream in(path, std::ios_base::binary);
  REQUIRE(in);

  Executor Exec;

  while (in.peek() != -1) {
    TestCase tcase;
    REQUIRE(readTestData(in, tcase.patterns, tcase.text, tcase.expected));
    Exec.submit(tcase);
  }
}
