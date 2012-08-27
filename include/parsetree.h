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
