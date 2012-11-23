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

#include "parsetree.h"
#include <ostream>

ParseNode* ParseTree::add(const ParseNode& n) {
  Store.push_back(n);
  return &Store[Store.size()-1];
}

void ParseTree::init(uint32_t len) {
  Root = 0;
  Store.clear();
  Store.reserve(2*len);
}

void printTree(std::ostream& out, const ParseNode& n) {
  if ((n.Type == ParseNode::CONCATENATION ||
       n.Type == ParseNode::ALTERNATION) && n.Right) {
    printTree(out, *n.Right);
  }

  if (n.Left) {
    printTree(out, *n.Left);
  }

  out << n << '\n';
}

std::ostream& operator<<(std::ostream& out, const ParseTree& tree) {
  if (tree.Root) {
    printTree(out, *tree.Root);
  }
  return out;
}
