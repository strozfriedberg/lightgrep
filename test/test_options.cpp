#include <catch2/catch_test_macros.hpp>

#include "config.h"

#include <vector>

#include "options.h"

TEST_CASE("getKeyFilesFromActualFiles") {
  Options opts;
  opts.KeyFiles = {
    LG_TEST_DATA_DIR "/pats.0",
    LG_TEST_DATA_DIR "/pats.1",
    LG_TEST_DATA_DIR "/pats.2"
  };

  const std::vector<std::pair<std::string,std::string>> expected = {
    { opts.KeyFiles[0], "a*b+\tUTF-8,UTF-16LE\t0\t0\nJoel\tUTF-8\t1\t1\n" },
    { opts.KeyFiles[1], "(All work and no play makes Jack a dull boy\\. )+\nBALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS BALLS\n" },
    { opts.KeyFiles[2], "\n\n\n\n\n\n\n\n\n" }
  };

  REQUIRE(expected == opts.getPatternLines());
}
