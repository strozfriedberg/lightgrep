/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2023, Aon Cyber Solutions

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

#include <catch2/catch_test_macros.hpp>

#include "automata.h"
#include "fwd_pointers.h"
#include "nfabuilder.h"
#include "parser.h"


NFAPtr construct(const std::string& pattern) {
  Pattern pat(pattern);
  ParseTree tree;
  parse(pat, tree);
  NFABuilder builder;
  builder.build(tree);
  return builder.getFsm();
}

TEST_CASE("test_simple_factor") {
  NFAPtr nfa = construct("glushkov");
  REQUIRE(nfa);
  REQUIRE(nfa->verticesSize() == 9u);
}