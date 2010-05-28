#pragma once

#include "basic.h"

#include <boost/function.hpp>

enum NodeType {
  REGEXP,
  ALTERNATION,
  CONCATENATION,
  ATOM,
  LITERAL
};

struct Node {
  NodeType  Type;
  Node      *Left,
            *Right;
  int       Val;

  Node(): Type(LITERAL), Left(0), Right(0), Val(0) {}

  Node(NodeType t, Node* l, Node* r, int v): Type(t), Left(l), Right(r), Val(v) {}
};

struct SyntaxTree {

  Node* Last;
  std::vector<Node> Store;

  Node* add(const Node& n) {
    Store.push_back(n);
    Last = &Store[Store.size()-1];
    return Last;
  }
};

bool parse(const std::string& text, SyntaxTree& tree, boost::function< void(std::string, Node) > callback);
