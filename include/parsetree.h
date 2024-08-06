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

#pragma once

#include "basic.h"
#include "parsenode.h"

#include <iosfwd>
#include <vector>

class ParseTree {
public:
  ParseNode* Root;

  template <class... Args>
  ParseNode* add(Args&&... args) {
    Store.emplace_back(std::forward<Args>(args)...);
    return &Store[Store.size()-1];
  }

  //
  // Sizing explanation:
  //
  // * Every character in a pattern contributes at most one node to
  // the parse tree. Some characters, such as parentheses, the square
  // brackets for character classes, and the nongreedy marker '?'
  // contribute none.
  //
  // * Concatenation is implicit in patterns. Each intercharacter
  // position potentially contributes one node to the parse tree.
  //
  // * The root is one node in the parse tree.
  //
  // The worst case is a pattern made up of n literals, which will
  // generate n nodes for the literals, n-1 nodes for the concatenations,
  // and one node for the root. n + n - 1 + 1 = 2n.
  //
  // Therefore, sizing the vector to twice the length of the pattern
  // ensures that the vector will never resize on us and invalidate our
  // ParseNode pointers.
  //
  void init(uint32_t len);

  bool operator==(const ParseTree& other) const {
    return !Root ? !other.Root : (other.Root ? *Root == *other.Root : false);
  }

private:
  std::vector<ParseNode> Store;
};

std::ostream& operator<<(std::ostream& out, const ParseTree& tree);
