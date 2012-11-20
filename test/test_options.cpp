#include <scope/test.h>

#include <fstream>
#include <vector>

#include "options.h"

SCOPE_TEST(parsePatterns) {
  Options opts;
  std::string line("Expression\t1\t1\tUTF-8,UTF-16");
  std::vector<Pattern> pats;
  SCOPE_ASSERT(opts.parseLine(0, line, pats));
  SCOPE_ASSERT_EQUAL(2u, pats.size());
  SCOPE_ASSERT_EQUAL(Pattern("Expression", true, true, 0, "UTF-8"), pats[0]);
  SCOPE_ASSERT_EQUAL(Pattern("Expression", true, true, 0, "UTF-16"), pats[1]);
}

SCOPE_TEST(parsePatternNoOpts) {
  Options opts;
  opts.LiteralMode = false;
  opts.CaseInsensitive = false;
  opts.Encodings = { "UTF-8" };

  std::string line("Expression");
  std::vector<Pattern> pats;
  SCOPE_ASSERT(opts.parseLine(0, line, pats));
  SCOPE_ASSERT_EQUAL(1u, pats.size());
  SCOPE_ASSERT_EQUAL(Pattern("Expression", false, false, 0, "UTF-8"), pats[0]);
}
