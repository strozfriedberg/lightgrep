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
#include "node.h"

#include <vector>

class ParseTree {
public:
  Node* Root;

  Node* add(const Node& n) {
    Store.push_back(n);
    return &Store[Store.size()-1];
  }

  void init(uint32 len) {
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
    // Node pointers.
    //
    Root = 0;
    Store.clear();
    Store.reserve(2*len);
  }

private:
  std::vector<Node> Store;
};
