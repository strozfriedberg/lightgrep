#include <scope/test.h>

#include "graph.h"
#include "matchgen.h"
#include "nfabuilder.h"
#include "parser.h"
#include "parsetree.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>

void fixture(const char* pattern, const char** expected, uint32 max_matches, uint32 max_loops) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse(pattern, false, tree));
  SCOPE_ASSERT(nfab.build(tree));

  std::set<std::string> aset;
  matchgen(*nfab.getFsm(), aset, max_loops, max_matches);

  std::set<std::string> eset(expected, expected + max_matches);

  SCOPE_ASSERT(eset == aset);
}

SCOPE_TEST(aSampleMatches) {
  const char* pattern = "a";
  const char* expected[] = { "a" };
  fixture(pattern, expected, sizeof(expected)/sizeof(expected[0]), 1);
}

SCOPE_TEST(aOrbSampleMatches) {
  const char* pattern = "a|b";
  const char* expected[] = { "a", "b" };
  fixture(pattern, expected, sizeof(expected)/sizeof(expected[0]), 1);
}

SCOPE_TEST(LPaOrbRPLPcOrdRPSampleMatches) {
  const char* pattern = "(a|b)(c|d)";
  const char* expected[] = { "ac", "ad", "bc", "bd" };
  fixture(pattern, expected, sizeof(expected)/sizeof(expected[0]), 1);
}

SCOPE_TEST(aPSampleMatches1) {
  const char* pattern = "a+";
  const char* expected[] = { "a" };
  fixture(pattern, expected, sizeof(expected)/sizeof(expected[0]), 1);
}

SCOPE_TEST(aPSampleMatches2) {
  const char* pattern = "a+";
  const char* expected[] = { "a", "aa" };
  fixture(pattern, expected, sizeof(expected)/sizeof(expected[0]), 2);
}

SCOPE_TEST(aPSampleMatches3) {
  const char* pattern = "a+";
  const char* expected[] = { "a", "aa", "aaa" };
  fixture(pattern, expected, sizeof(expected)/sizeof(expected[0]), 3);
}
