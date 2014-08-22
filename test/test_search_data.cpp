/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#include <algorithm>
#include <atomic>
#include <istream>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

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

    std::cout << ss.str();

    if (++count % 1000 == 0) {
      std::cerr << count << std::endl;
    }
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

bool longTest(std::istream& in) {
  // scoping ensures that executor is destroyed before we check failed
  {
    Executor ex;
    longTest(ex, in);
  }

  std::cerr << TestCase::count << std::endl;
  return TestCase::failed == 0;
}
