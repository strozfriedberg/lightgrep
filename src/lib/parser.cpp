/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

static bool contains_possible_nongreedy(const std::string& pattern) {
  // The trailing '?' of a nongreedy operator must have at least
  // two characters preceeding it.
  return pattern.find('?', 2) != std::string::npos;
}

static bool contains_possible_counted_repetition(const std::string& pattern) {
  // The '{' of a counted repetition operator must have at least one
  // character preceeding it and two characters following it.
  const std::string::size_type cr = pattern.rfind('{', pattern.length()-3);
  return cr > 0 && cr != std::string::npos;
}

void parse_and_reduce(const std::string& text, bool litMode, bool caseInsensitive, ParseTree& tree) {
  // parse the pattern
  if (!parse(text, litMode, caseInsensitive, tree)) {
    THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("Could not parse");
  }

  reduce(text, tree);
}

void reduce(const std::string& text, ParseTree& tree) {
  // rewrite the parse tree, if necessary
  bool rewrite = false;

  rewrite = make_binops_right_associative(tree.Root);
  rewrite |= combine_consecutive_repetitions(tree.Root);

  if (contains_possible_nongreedy(text)) {
    rewrite |= reduce_trailing_nongreedy_then_empty(tree.Root);
    rewrite |= reduce_trailing_nongreedy_then_greedy(tree.Root);
  }

  if (rewrite || contains_possible_counted_repetition(text)) {
    reduce_empty_subtrees(tree.Root);
    reduce_useless_repetitions(tree.Root);
  }
}
