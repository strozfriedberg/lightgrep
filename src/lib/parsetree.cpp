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

#include "parsetree.h"
#include <ostream>

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
void ParseTree::init(uint32_t len) {
  Root = nullptr;
  Store.clear();
  Store.reserve(2*len);
}

void printTree(std::ostream& out, const ParseNode& n) {
  switch (n.Type) {
  case ParseNode::ALTERNATION:
  case ParseNode::CONCATENATION:
    if (n.Child.Right) {
      printTree(out, *n.Child.Right);
    }
  case ParseNode::REGEXP:
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    if (n.Child.Left) {
      printTree(out, *n.Child.Left);
    }
    break;
  default:
    break;
  }

  out << n << '\n';
}

std::ostream& operator<<(std::ostream& out, const ParseTree& tree) {
  if (tree.Root) {
    printTree(out, *tree.Root);
  }
  return out;
}
