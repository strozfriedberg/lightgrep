#include <scope/test.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "options.h"
#include "optparser.h"

#define TEST_OPTS(cargv, opts) \
  const int cargc = std::extent<decltype(cargv)>::value; \
\
  const int argc = cargc + 1; \
\
  uint32_t total_len = 0; \
  for (int i = 0; i < cargc; ++i) { \
    total_len += strlen(cargv[i]) + 1; \
  } \
\
  std::unique_ptr<char[]> cs(new char[total_len+1]{}); \
  std::unique_ptr<char*[]> ss(new char*[argc]); \
\
  char** argv = ss.get(); \
  argv[0] = cs.get(); \
\
  for (int i = 0, pos = 1; i < cargc; ++i) { \
    argv[i+1] = argv[0] + pos; \
    strcpy(argv[i+1], cargv[i]); \
    pos += strlen(cargv[i]) + 1; \
  } \
\
  boost::program_options::options_description desc; \
\
  parse_opts(argc, argv, desc, opts);

SCOPE_TEST(kAndpIncompatibleOptions) {
  const char* cargv[] = { "--keywords", "foo", "--pattern", "bar" };
  Options opts;

  SCOPE_EXPECT(
    TEST_OPTS(cargv, opts),
    boost::program_options::error
  );
}

SCOPE_TEST(kOptionNoPosArg) {
  const char* cargv[] = { "--keywords", "foo" };
  Options opts;
  TEST_OPTS(cargv, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "-" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(kOptionOnePosArg) {
  const char* cargv[] = { "--keywords", "foo", "bar" };
  Options opts;
  TEST_OPTS(cargv, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(endOnePosArg) {
  const char* cargv[] = { "--", "foo" };
  Options opts;
  TEST_OPTS(cargv, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "-" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(endTwoPosArgs) {
  const char* cargv[] = { "--", "foo", "bar" };
  Options opts;
  TEST_OPTS(cargv, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}

SCOPE_TEST(endThreePosArgs) {
  const char* cargv[] = { "--", "foo", "bar", "baz" };
  Options opts;
  TEST_OPTS(cargv, opts);

  const std::vector<std::string> kf{ "foo" }, inputs{ "bar", "baz" };

  SCOPE_ASSERT_EQUAL(kf, opts.KeyFiles);
  SCOPE_ASSERT_EQUAL(inputs, opts.Inputs);
}
