#include <algorithm>
#include <atomic>
#include <functional>
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

#ifdef POLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#define BOOST_USE_WINDOWS_H
#endif

#include <boost/thread.hpp>

struct TestCase {
  std::vector<Pattern> patterns;
  std::string text;
  std::vector<SearchHit> expected;

  static std::atomic_uint count;

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
    }

    std::cout << ss.str();

    if (++count % 1000 == 0) {
      std::cerr << count << std::endl;
    }
  }
};

std::atomic_uint TestCase::count(0);

class executor {
public:
  executor(size_t n):
    service_(n), work_(new boost::asio::io_service::work(service_))
  {
    for (size_t i = 0; i < n; ++i) {
      pool_.create_thread(boost::bind(&boost::asio::io_service::run, &service_));
    }
  }

  ~executor() {
    delete work_;
    pool_.join_all();
    std::cerr << TestCase::count << std::endl;
  }

  template <typename F>
  void submit(F task) {
    service_.post(task);
  }

protected:
  boost::thread_group pool_;
  boost::asio::io_service service_;
  boost::asio::io_service::work* work_;
};

void longTest() {
  executor ex(8);

  uint32 count = 0;

  uint32 len, patcount;
  while (std::cin.peek() != -1) {
    TestCase tcase;

    // read number of patterns
    std::cin.read(reinterpret_cast<char*>(&patcount), sizeof(patcount));
    tcase.patterns.reserve(patcount);

    for (uint32 i = 0; i < patcount; ++i) {
      // read pattern
      std::cin.read(reinterpret_cast<char*>(&len), sizeof(len));
      std::string pattern(len, '\0');
      std::cin.read(&pattern[0], len);

      // read fixed
      bool fixed;
      std::cin.read(reinterpret_cast<char*>(&fixed), 1);

      // read case-insensitive
      bool case_insensitive;
      std::cin.read(reinterpret_cast<char*>(&case_insensitive), 1);

      // read encoding
      std::cin.read(reinterpret_cast<char*>(&len), sizeof(len));
      std::string encoding(len, '\0');
      std::cin.read(&encoding[0], len);

      tcase.patterns.emplace_back(pattern, fixed, case_insensitive, 0, encoding);
    }

    // read text
    std::cin.read(reinterpret_cast<char*>(&len), sizeof(len));
    tcase.text.assign(len, '\0');
    std::cin.read(&tcase.text[0], len);

    // NB: Yes, we are reading data directly into the storage for a
    // std::vector. We are trained professionals. Don't try this at
    // home, boys and girls.

    // read hits
    std::cin.read(reinterpret_cast<char*>(&len), sizeof(len));
    tcase.expected.resize(len);
    std::cin.read(reinterpret_cast<char*>(&tcase.expected[0]), len*sizeof(SearchHit));

    ex.submit(tcase);

/*
    if (++count % 1000 == 0) {
      std::cerr << count << std::endl;
    }
*/
  }
}
