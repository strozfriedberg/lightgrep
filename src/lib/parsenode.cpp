#include "parsenode.h"

void repetition(std::ostream& out, uint32 min, uint32 max) {
  if (min == 0) {
    if (max == 1) {
      // ? is {0,1}
      out << '?';
      return;
    }
    else if (max == UNBOUNDED) {
      // * is {0,}
      out << '*';
      return;
    }
  }
  else if (min == 1 && max == UNBOUNDED) {
    // + is {1,}
    out << '+';
    return;
  }

  out << '{' << min;

  if (max == UNBOUNDED) {
    out << ',';
  }
  else if (max != min) {
    out << ',' << max;
  }

  out << '}';
}

std::ostream& operator<<(std::ostream& out, const ParseNode& n) {
  switch (n.Type) {
  case ParseNode::REGEXP:
    return out << "REGEXP";
  case ParseNode::ALTERNATION:
    return out << '|';
  case ParseNode::CONCATENATION:
    return out << '&';
  case ParseNode::GROUP:
    return out << '(';
  case ParseNode::REPETITION:
    repetition(out, n.Min, n.Max);
    return out;
  case ParseNode::REPETITION_NG:
    repetition(out, n.Min, n.Max);
    return out << '?';
  case ParseNode::ELEMENT:
    return out << "ELEMENT";
  case ParseNode::DOT:
    return out << '.';
  case ParseNode::CHAR_CLASS:
    return out << n.Bits;
  case ParseNode::LITERAL:
    return out << (char) n.Val;
  case ParseNode::LG_IGNORE:
    return out << "IGNORE";
  default:
    return out << "WTF";
  }
}

void printTree(std::ostream& out, const ParseNode& n) {
  if (n.Right) {
    printTree(out, *n.Right);
  }

  if (n.Left) {
    printTree(out, *n.Left);
  }

  out << n << '\n';
}

void printTreeDetails(std::ostream& out, const ParseNode& n) {
  if (n.Right) {
    printTreeDetails(out, *n.Right);
  }

  if (n.Left) {
    printTreeDetails(out, *n.Left);
  }

  out << &n << ' ' << n.Type << ' ' << n.Left << ' ' << n.Right << ' '
      << n.Val << ' ' << n.Min << ' ' << n.Max << '\n';
}

