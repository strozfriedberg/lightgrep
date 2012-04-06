#include <scope/test.h>

#include <fstream>
#include "options.h"

SCOPE_TEST(parsePatterns) {
  Options opts;
  std::string line("Expression\t1\t1\tUTF-8,UTF-16");
  PatternInfo ps;
  SCOPE_ASSERT(opts.parseLine(0, line, ps));
  SCOPE_ASSERT_EQUAL(2u, ps.Patterns.size());
  SCOPE_ASSERT_EQUAL(Pattern("Expression", true, true, 0, "UTF-8"), ps.Patterns[0]);
  SCOPE_ASSERT_EQUAL(Pattern("Expression", true, true, 0, "UTF-16"), ps.Patterns[1]);
}

SCOPE_TEST(parsePatternNoOpts) {
  Options opts;
  opts.LiteralMode = false;
  opts.CaseInsensitive = false;
  opts.Encoding = "UTF-8";

  std::string line("Expression");
  PatternInfo ps;
  SCOPE_ASSERT(opts.parseLine(0, line, ps));
  SCOPE_ASSERT_EQUAL(1u, ps.Patterns.size());
  SCOPE_ASSERT_EQUAL(Pattern("Expression", false, false, 0, "UTF-8"), ps.Patterns[0]);
}
