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
  case ParseNode::REPETITION:
    repetition(out, n.Rep.Min, n.Rep.Max);
    return out;
  case ParseNode::REPETITION_NG:
    repetition(out, n.Rep.Min, n.Rep.Max);
    return out << '?';
  case ParseNode::DOT:
    return out << '.';
  case ParseNode::CHAR_CLASS:
    return out << n.Bits;
  case ParseNode::LITERAL:
    return out << (char) n.Val;
  case ParseNode::TEMPORARY:
    return out << "TEMPORARY";
  default:
    return out << "WTF";
  }
}

void printTreeDetails(std::ostream& out, const ParseNode& n) {
  if ((n.Type == ParseNode::CONCATENATION ||
       n.Type == ParseNode::ALTERNATION) && n.Right) {
    printTreeDetails(out, *n.Right);
  }

  if (n.Left) {
    printTreeDetails(out, *n.Left);
  }

  out << &n << ' ' << n.Type << ' ' << n.Left << ' ';

  switch (n.Type) {
  case ParseNode::CONCATENATION:
  case ParseNode::ALTERNATION:
    out << n.Right;
    break;
  case ParseNode::REPETITION:
  case ParseNode::REPETITION_NG:
    out << n.Rep.Min << ' ' << n.Rep.Max;
    break;
  case ParseNode::LITERAL:
    out << n.Val;
    break;
  case ParseNode::CHAR_CLASS:
  default:
    break;
  }

  out << '\n';
}
