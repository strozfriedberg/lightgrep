#pragma once

#include "basic.h"
#include "parsenode.h"

#include <vector>

class ParseTree {
public:
  ParseNode* Root;

  template <class... Args>
  ParseNode* add(Args&&... args) {
    Store.emplace_back(args...);
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
    // ParseNode pointers.
    //
    Root = 0;
    Store.clear();
    Store.reserve(2*len);
  }

private:
  std::vector<ParseNode> Store;
};
