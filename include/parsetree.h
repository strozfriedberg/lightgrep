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

#pragma once

#include "basic.h"
#include "parsenode.h"

#include <iosfwd>
#include <vector>

class ParseTree {
public:
  ParseNode* Root;

  ParseNode* add(const ParseNode& n);

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
  void init(uint32 len);

  bool operator==(const ParseTree& other) const {
    return !Root ? !other.Root : (other.Root ? *Root == *other.Root : false);
  }

private:
  std::vector<ParseNode> Store;
};

std::ostream& operator<<(std::ostream& out, const ParseTree& tree);
