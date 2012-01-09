#include <scope/test.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include <boost/scoped_array.hpp>
#include <boost/program_options.hpp>

#include "options.h"
#include "optparser.h"

#define TEST_OPTS(cargv, opts) \
  const int cargc = sizeof(cargv) / sizeof(cargv[0]); \
\
  const int argc = cargc + 1; \
\
  uint32 total_len = 1; \
  for (int i = 0; i < cargc; ++i) { \
    total_len += strlen(cargv[i]) + 1; \
  } \
\
  boost::scoped_array<char> cs(new char[total_len]); \
  boost::scoped_array<char*> ss(new char*[argc]); \
\
  char** argv = ss.get(); \
  argv[0] = cs.get(); \
  argv[0][0] = '\0'; \
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

/*
SCOPE_TEST(kTooManyOptions) {
  const char* cargv[] = { "--keywords", "foo", "bar", "baz" };
  Options opts;

  SCOPE_EXPECT(
    TEST_OPTS(cargv, opts),
    boost::program_options::too_many_positional_options_error
  );
}
*/

/*
SCOPE_TEST(pTooManyOptions) {
  const char* cargv[] = { "--pattern", "foo", "bar", "baz" };
  Options opts;

  SCOPE_EXPECT(
    TEST_OPTS(cargv, opts),
    boost::program_options::too_many_positional_options_error
  );
}
*/

SCOPE_TEST(endOnePosArgOptions) {
  const char* cargv[] = { "--", "foo" };
  Options opts;
  TEST_OPTS(cargv, opts);

  SCOPE_ASSERT_EQUAL(cargv[1], opts.KeyFile);
  SCOPE_ASSERT_EQUAL("-", opts.Input);
}

/*
SCOPE_TEST(endTwoPosArgsOptions) {
  const char* cargv[] = { "--", "foo", "bar" };
  Options opts;
  TEST_OPTS(cargv, opts);

  SCOPE_ASSERT_EQUAL(cargv[1], opts.KeyFile);
  SCOPE_ASSERT_EQUAL(cargv[2], opts.Input);
}
*/

/*
SCOPE_TEST(endThreePosArgsOptions) {
  const char* cargv[] = { "--", "foo", "bar", "baz" };
  Options opts;

  SCOPE_EXPECT(
    TEST_OPTS(cargv, opts),
    boost::program_options::too_many_positional_options_error
  );
}
*/

