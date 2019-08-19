/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

void fixture(const char* pattern, const char** expected, uint32_t max_matches, uint32_t max_loops) {
  NFABuilder nfab;
  ParseTree tree;
  SCOPE_ASSERT(parse({pattern, false, false}, tree));
  SCOPE_ASSERT(nfab.build(tree));

  std::set<std::string> aset;
  matchgen(*nfab.getFsm(), aset, max_matches, max_loops);

  std::set<std::string> eset(expected, expected + max_matches);
  SCOPE_ASSERT(eset == aset);
}

SCOPE_TEST(aSampleMatches) {
  const char pattern[] = "a";
  const char* expected[] = { "a" };
  fixture(pattern, expected, std::extent<decltype(expected)>::value, 1);
}

/*
SCOPE_TEST(aOrbSampleMatches) {
  const char pattern[] = "a|b";
  const char* expected[] = { "a", "b" };
  fixture(pattern, expected, std::extent<decltype(expected)>::value, 1);
}
*/

/*
SCOPE_TEST(LPaOrbRPLPcOrdRPSampleMatches) {
  const char pattern[] = "(a|b)(c|d)";
  const char* expected[] = { "ac", "ad", "bc", "bd" };
  fixture(pattern, expected, std::extent<decltype(expected)>::value, 1);
}
*/

SCOPE_TEST(aPSampleMatches1) {
  const char pattern[] = "a+";
  const char* expected[] = { "a" };
  fixture(pattern, expected, std::extent<decltype(expected)>::value, 1);
}

/*
SCOPE_TEST(aPSampleMatches2) {
  const char pattern[] = "a+";
  const char* expected[] = { "a", "aa" };
  fixture(pattern, expected, std::extent<decltype(expected)>::value, 2);
}

SCOPE_TEST(aPSampleMatches3) {
  const char pattern[] = "a+";
  const char* expected[] = { "a", "aa", "aaa" };
  fixture(pattern, expected, std::extent<decltype(expected)>::value, 3);
}
*/
