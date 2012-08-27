#include "parsetree.h"
#include <ostream>

ParseNode* ParseTree::add(const ParseNode& n) {
  Store.emplace_back(n);
  return &Store[Store.size()-1];
}

void ParseTree::init(uint32 len) {
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
