#include "node.h"

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

std::ostream& operator<<(std::ostream& out, const Node& n) {
  switch (n.Type) {
  case Node::REGEXP:
    return out << "REGEXP";
  case Node::ALTERNATION:
    return out << '|';
  case Node::CONCATENATION:
    return out << '&';
  case Node::GROUP:
    return out << '(';
  case Node::REPETITION:
    repetition(out, n.Min, n.Max);
    return out;
  case Node::REPETITION_NG:
    repetition(out, n.Min, n.Max);
    return out << '?';
  case Node::ELEMENT:
    return out << "ELEMENT";
  case Node::DOT:
    return out << '.';
  case Node::CHAR_CLASS:
    return out << n.Bits;
  case Node::LITERAL:
    return out << (char) n.Val;
  case Node::IGNORE:
    return out << "IGNORE";
  default:
    return out << "WTF";
  }
}
