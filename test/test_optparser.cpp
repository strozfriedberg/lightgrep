#include <scope/test.h>

#include <string>
#include <type_traits>
#include <vector>

#include <boost/program_options.hpp>

#include "options.h"
#include "optparser.h"

SCOPE_TEST(kAndpIncompatibleOptions) {
  const char* argv[] = { "lightgrep", "--keywords", "foo", "--pattern", "bar" };
  Options opts;
  boost::program_options::options_description desc;

  SCOPE_EXPECT(
    parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts),
    boost::program_options::error
  );
}

SCOPE_TEST(kOptionNoPosArg) {
  const char* argv[] = { "lightgrep", "--keywords", "foo" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "-" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(kOptionOnePosArg) {
  const char* argv[] = { "lightgrep", "--keywords", "foo", "bar" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(endOnePosArg) {
  const char* argv[] = { "lightgrep", "--", "foo" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "-" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(endTwoPosArgs) {
  const char* argv[] = { "lightgrep", "--", "foo", "bar" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(endThreePosArgs) {
  const char* argv[] = { "lightgrep", "--", "foo", "bar", "baz" };
  Options opts;
  boost::program_options::options_description desc;
  parse_opts(std::extent<decltype(argv)>::value, argv, desc, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar", "baz" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}
