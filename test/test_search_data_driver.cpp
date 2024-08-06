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
#include <atomic>
#include <istream>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "basic.h"
#include "pattern.h"

#include "data_reader.h"
#include "executor.h"
#include "stest.h"

struct TestCase {
  std::vector<Pattern> patterns;
  std::string text;
  std::vector<SearchHit> expected;

  static std::atomic_uint count, failed;

  void operator()() {
    std::ostringstream ss;

    for (const Pattern& p : patterns) {
      ss << p.Expression << ' ' << p.Encoding << ' ';
    }

    STest test(patterns);
    test.search(text.c_str(), text.c_str() + text.length(), 0);

    std::vector<SearchHit>& actual = test.Hits;

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

    CHECK(actual == expected);
    if (actual == expected) {
      ss << "ok.\n";
    }
    else {
      // Houston, we have a problem
      ss << "failed!\n";

      ss << "missing: ";

      std::set_difference(
        expected.begin(), expected.end(),
        actual.begin(), actual.end(),
        std::ostream_iterator<SearchHit>(ss, " ")
      );

      ss << '\n';
      ss << "extra: ";

      std::set_difference(
        actual.begin(), actual.end(),
        expected.begin(), expected.end(),
        std::ostream_iterator<SearchHit>(ss, " ")
      );

      ss << '\n';

      ++failed;
    }
    // std::cout << ss.str();
    ++count;
    // if (count % 1000 == 0) {
    //   std::cerr << count << std::endl;
    // }
  }
};

std::atomic_uint TestCase::count(0);
std::atomic_uint TestCase::failed(0);

namespace {
  void longTest(Executor& ex, std::istream& in) {
    while (in.peek() != -1) {
      TestCase tcase;
      if (!readTestData(in, tcase.patterns, tcase.text, tcase.expected)) {
        std::cerr << "failed to read test data" << std::endl;
        TestCase::failed = std::numeric_limits<unsigned int>::max();
        return;
      }
      ex.submit(tcase);
    }
  }
}

TEST_CASE("longTest", "[.]") {
  // scoping ensures that executor is destroyed before we check failed
  {
    Executor ex;
    longTest(ex, std::cin);
  }
  REQUIRE(TestCase::count > 0);
  REQUIRE(TestCase::failed == 0);
}
