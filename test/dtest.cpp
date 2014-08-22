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
#include <fstream>
#include <string>
#include <vector>

#include <scope/test.h>

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

      SCOPE_ASSERT_EQUAL(expected.size(), actual.size());

      std::sort(expected.begin(), expected.begin());
      std::sort(actual.begin(), actual.end());

      std::pair<std::vector<SearchHit>::iterator,
                std::vector<SearchHit>::iterator> mis(
        std::mismatch(expected.begin(), expected.end(), actual.begin())
      );

      if (mis.first != expected.end()) {
        // This is guaranteed to fail. We assert just to get the message.
        SCOPE_ASSERT_EQUAL(*mis.first, *mis.second);
      }
    }
  };
}

void DTest::run(const char* path) {
  std::ifstream in(path, std::ios_base::binary);
  SCOPE_ASSERT(in);

  Executor Exec;

  while (in.peek() != -1) {
    TestCase tcase;
    SCOPE_ASSERT(readTestData(in, tcase.patterns, tcase.text, tcase.expected));
    Exec.submit(tcase);
  }
}
