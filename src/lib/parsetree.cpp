#include "parsetree.h"

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
