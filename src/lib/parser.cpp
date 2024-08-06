/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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
