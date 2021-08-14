#include "catch.hpp"

#include <string>
#include <type_traits>
#include <vector>

#include <boost/program_options.hpp>

#include "options.h"
#include "optparser.h"

TEST_CASE("kAndpIncompatibleOptions") {
  const char* argv[] = { "lightgrep", "--keywords", "foo", "--pattern", "bar" };
  Options opts;
  boost::program_options::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts),
    boost::program_options::error
  );
}

TEST_CASE("kOptionNoPosArg") {
  const char* argv[] = { "lightgrep", "--keywords", "foo" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "-" };

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("kOptionOnePosArg") {
  const char* argv[] = { "lightgrep", "--keywords", "foo", "bar" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar" };

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("endOnePosArg") {
  const char* argv[] = { "lightgrep", "--", "foo" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "-" };

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("endTwoPosArgs") {
  const char* argv[] = { "lightgrep", "--", "foo", "bar" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar" };

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}

TEST_CASE("endThreePosArgs") {
  const char* argv[] = { "lightgrep", "--", "foo", "bar", "baz" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar", "baz" };

  REQUIRE(kf == opts.KeyFiles);
  REQUIRE(inputs == opts.Inputs);
}
