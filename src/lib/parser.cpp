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

#include "basic.h"
#include "parser.h"
#include "rewriter.h"

#include <string>

namespace {
  bool containsPossibleNongreedy(const std::string& pattern) {
    // The trailing '?' of a nongreedy operator must have at least
    // two characters preceeding it.
    return pattern.find('?', 2) != std::string::npos;
  }

  bool containsPossibleCountedRepetition(const std::string& pattern) {
    // The '{' of a counted repetition operator must have at least one
    // character preceeding it and two characters following it.
    const std::string::size_type cr = pattern.rfind('{', pattern.length()-3);
    return cr > 0 && cr != std::string::npos;
  }
}

void parseAndReduce(const Pattern& pattern, ParseTree& tree) {
  // parse the pattern
  if (!parse(pattern, tree)) {
    THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("Could not parse");
  }
  reduce(pattern.Expression, tree);
}

void reduce(const std::string& text, ParseTree& tree) {
  // rewrite the parse tree, if necessary
  bool rewrite = makeBinopsRightAssociative(tree.Root);
  rewrite |= combineConsecutiveRepetitions(tree.Root);

  if (containsPossibleNongreedy(text)) {
    rewrite |= reduceTrailingNongreedyThenEmpty(tree.Root);
    rewrite |= reduceTrailingNongreedyThenGreedy(tree.Root);
  }

  if (rewrite || containsPossibleCountedRepetition(text)) {
    reduceEmptySubtrees(tree.Root);
    reduceUselessRepetitions(tree.Root);
  }
}
