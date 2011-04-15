
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include <utility>

#include "basic.h"
#include "stest.h"

void longTest() {

  uint32 len;
  while (std::cin.peek() != -1) {

    // read pattern
    std::cin.read((char*)&len, 4);
    std::string pattern(len, '\0');
    std::cin.read(&pattern[0], len);

    // read text
    std::cin.read((char*)&len, 4);
    std::string text(len, '\0');
    std::cin.read(&text[0], len);

    // read hits
    std::cin.read((char*)&len, 4);
    std::vector<SearchHit> expected(len);
    std::cin.read((char*)&expected[0], len*24);

    std::cout << pattern << ' ';

    // run lg on the text with the pattern
    STest test(pattern);
    const byte* text_ptr = (const byte*) text.data();
    test.search(text_ptr, text_ptr + text.length(), 0, test);

    std::vector<SearchHit>& actual = test.Hits;

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

/*
    std::copy(expected.begin(), expected.end(),
              std::ostream_iterator<SearchHit>(std::cout, " "));

    std::cout << '\n';

    std::copy(actual.begin(), actual.end(),
              std::ostream_iterator<SearchHit>(std::cout, " "));
*/

    if (actual == expected) {
      std::cout << "ok.\n";
    }
    else {
      // Houston, we have a problem
      std::cout << "failed!\n";

      std::cout << "missing: ";

      std::set_difference(
        expected.begin(), expected.end(),
        actual.begin(), actual.end(),
        std::ostream_iterator<SearchHit>(std::cout, " ")
      );

      std::cout << '\n';
      std::cout << "extra: ";

      std::set_difference(
        actual.begin(), actual.end(),
        expected.begin(), expected.end(),
        std::ostream_iterator<SearchHit>(std::cout, " ")
      );

      std::cout << '\n';
    }
  }
}
