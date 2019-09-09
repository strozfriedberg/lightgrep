#include <scope/test.h>

#include <vector>

#include "options.h"

SCOPE_TEST(getKeyFilesFromActualFiles) {
  Options opts;
  opts.KeyFiles = {
    "test/data/pats.0",
    "test/data/pats.1",
    "test/data/pats.2"
  };

  const std::vector<std::pair<std::string,std::string>> expected = {
    { opts.KeyFiles[0], "a*b+\tUTF-8,UTF-16LE\t0\t0\nJoel\tUTF-8\t1\t1\n" },
    { opts.KeyFiles[1], "(All work and no play makes Jack a dull boy\\. )+\nBALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS\n" },
    { opts.KeyFiles[2], "\n\n\n\n\n\n\n\n\n" }
  };

  const std::vector<std::pair<std::string,std::string>> actual = opts.getPatternLines();

  SCOPE_ASSERT_EQUAL(expected.size(), actual.size());
  for (uint8_t i = 0; i < expected.size(); ++i) {
    SCOPE_ASSERT_EQUAL(expected[i], actual[i]);
  }
}
