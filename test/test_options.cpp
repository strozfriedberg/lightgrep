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

  SCOPE_ASSERT_EQUAL(expected, opts.getPatternLines());
}
