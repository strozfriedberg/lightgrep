
#include "unparser.h"

#include <sstream>

#include <boost/lexical_cast.hpp>

bool is_binary(const Node* n) {
  return n->Type == Node::ALTERNATION || n->Type == Node::CONCATENATION;
}

void open_paren(const Node* n, std::stringstream& ss) {
  // parentheses are necessary only when unary operators are the
  // parents of binary operators
  if (is_binary(n->Left)) {
    ss << '(';
  }
} 

void close_paren(const Node *n, std::stringstream& ss) {
  if (is_binary(n->Left)) {
    ss << ')';
  }
} 

void unparse(const Node* n, std::stringstream& ss) {
  switch (n->Type) {
  case Node::REGEXP:
    unparse(n->Left, ss);
    break;

  case Node::ALTERNATION:
    unparse(n->Left, ss);
    ss << '|';
    unparse(n->Right, ss);
    break;

  case Node::CONCATENATION:
    unparse(n->Left, ss);
    unparse(n->Right, ss);
    break;

  case Node::PLUS:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << '+';
    break;

  case Node::STAR:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << '*';
    break;

  case Node::QUESTION:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << '?';
    break;

  case Node::PLUS_NG:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << "+?";
    break;

  case Node::STAR_NG:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << "*?";
    break;

  case Node::QUESTION_NG:
    open_paren(n, ss);
    unparse(n->Left, ss);
    close_paren(n, ss);
    ss << "??";
    break;

  case Node::DOT:
    ss << '.';
    break;

  case Node::CHAR_CLASS:
    ss << '[';
    // FXIME: what do do here???
    ss << ']';
    break;

  case Node::LITERAL:
    ss << (char) n->Val;
    break;

  default:
    // WTF?
    throw std::logic_error(boost::lexical_cast<std::string>(n->Type));
  }
}

std::string unparse(const ParseTree& tree) {
  std::stringstream ss;
  unparse(tree.Root, ss);
  return ss.str();
}

