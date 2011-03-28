#include "node.h"

std::ostream& operator<<(std::ostream& out, const Node& n) {
  switch (n.Type) {
  case Node::REGEXP:
    out << "REGEXP";
    break;
  case Node::ALTERNATION:
    out << '|';
    break;
  case Node::CONCATENATION:
    out << '&';
    break;
  case Node::GROUP:
    out << '(';
    break;
  case Node::PLUS:
    out << '+';
    break;
  case Node::STAR:
    out << '*';
    break;
  case Node::QUESTION:
    out << '?';
    break;
  case Node::PLUS_NG:
    out << "+?";
    break;
  case Node::STAR_NG:
    out << "*?";
    break;
  case Node::QUESTION_NG:
    out << "??";
    break;
  case Node::ELEMENT:
    out << "ELEMENT";
    break;
  case Node::DOT:
    out << '.';
    break;
  case Node::CHAR_CLASS:
    out << n.Bits;
    break;
  case Node::LITERAL:
    out << (char) n.Val;
    break;
  case Node::IGNORE:
    out << "IGNORE";
    break;
  default:
    out << "WTF";
    break;
  }

  return out;
}
