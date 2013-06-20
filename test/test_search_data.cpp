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
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "basic.h"
#include "pattern.h"
#include "stest.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

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
    const byte* text_ptr = reinterpret_cast<const byte*>(text.data());
    test.search(text_ptr, text_ptr + text.length(), 0);

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

class executor {
public:
  executor(size_t n):
    service_(n), work_(new boost::asio::io_service::work(service_))
  {
    for (size_t i = 0; i < n; ++i) {
      pool_.emplace_back([this](){ service_.run(); });
    }
  }

  ~executor() {
    delete work_;
    for (boost::thread& t : pool_) { t.join(); }
  }

  template <typename F>
  void submit(F task) {
    service_.post(task);
  }

protected:
  std::vector<boost::thread> pool_;
  boost::asio::io_service service_;
  boost::asio::io_service::work* work_;
};

void longTest(executor& ex, std::istream& in) {
  uint32_t len, patcount;
  while (in.peek() != -1) {
    TestCase tcase;

    // read number of patterns
    in.read(reinterpret_cast<char*>(&patcount), sizeof(patcount));
    tcase.patterns.reserve(patcount);

    for (uint32_t i = 0; i < patcount; ++i) {
      // read pattern
      in.read(reinterpret_cast<char*>(&len), sizeof(len));
      std::string pattern(len, '\0');
      in.read(&pattern[0], len);

      // read fixed
      bool fixed;
      in.read(reinterpret_cast<char*>(&fixed), 1);

      // read case-insensitive
      bool case_insensitive;
      in.read(reinterpret_cast<char*>(&case_insensitive), 1);

      // read encoding
      in.read(reinterpret_cast<char*>(&len), sizeof(len));
      std::string encoding(len, '\0');
      in.read(&encoding[0], len);

      tcase.patterns.emplace_back(pattern, fixed, case_insensitive, encoding);
    }

    // read text
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    tcase.text.assign(len, '\0');
    in.read(&tcase.text[0], len);

    // read hits
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    tcase.expected.resize(len);
    in.read(reinterpret_cast<char*>(&tcase.expected[0]), len*sizeof(SearchHit));

    ex.submit(tcase);
  }
}

bool longTest(std::istream& in) {
  // scoping ensures that executor is destroyed before we check failed
  {
    executor ex(boost::thread::hardware_concurrency());
    longTest(ex, in);
  }

  std::cerr << TestCase::count << std::endl;
  return TestCase::failed == 0;
}
