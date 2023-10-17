#include <catch2/catch_test_macros.hpp>

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

TEST_CASE("analyzeCommandOption") {
  const char* argv[] = { "lightgrep", "-c", "analyze", "-p", "foo"};
  Options opts;

  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  REQUIRE(Options::ANALYZE == opts.Command);
}

TEST_CASE("programFileOption") {
  const char* argv[] = { "lightgrep", "--program-file", "test-prog.txt", "test1.txt"};
  Options opts;

  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(0 == opts.KeyFiles.size());
  REQUIRE("test1.txt" == opts.Inputs.at(0));
}

TEST_CASE("programFileAndPatternOption") {
  const char* argv[] = { "lightgrep", "--program-file", "test-prog.txt", "--pattern", "test", "test1.txt"};
  Options opts;

  boost::program_options::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts),
    boost::program_options::error
  );
}

TEST_CASE("programFileAndKeywordsOption") {
  const char* argv[] = { "lightgrep", "--program-file", "test-prog.txt", "--keywords", "patterns.txt", "test1.txt"};
  Options opts;

  boost::program_options::options_description desc;

  REQUIRE_THROWS_AS(
    parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts),
    boost::program_options::error
  );
}

TEST_CASE("memoryMappedOption") {
  const char* argv[] = { "lightgrep", "--program-file", "test-prog.txt", "-C", "3", "test1.txt"};
  Options opts;

  po::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  REQUIRE(Options::SEARCH == opts.Command);
  REQUIRE("test-prog.txt" == opts.ProgramFile);
  REQUIRE(0 == opts.KeyFiles.size());
  REQUIRE(opts.MemoryMapped == true);
}