#pragma once

#include "basic.h"
#include "dynamicFSM.h"

#include <boost/function.hpp>

#include <stack>

enum NodeType {
  REGEXP,
  ALTERNATION,
  CONCATENATION,
  ATOM,
  GROUP,
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

typedef std::vector< DynamicFSM::vertex_descriptor > VList;

std::ostream& operator<<(std::ostream& out, const VList& list);

struct Fragment {
  Fragment(VList in, const Node& n): InList(in), N(n) {}
  Fragment(DynamicFSM::vertex_descriptor in, const Node& n): N(n) { InList.push_back(in); }
  Fragment(VList in, const Node& n, const VList& out):
    InList(in), OutList(out), N(n) {}

  std::vector< DynamicFSM::vertex_descriptor > InList, OutList;
  Node N;

  void addToOut(DynamicFSM::vertex_descriptor v) {
    add(v, OutList);
  }

  void addToIn(DynamicFSM::vertex_descriptor v) {
    add(v, InList);
  }

  void add(DynamicFSM::vertex_descriptor v, VList& list);
  void merge(const Fragment& f);
};

class Parser {
public:
  Parser(): Fsm(new DynamicFSM(1)) {}

  void callback(const std::string& type, Node n);

  void patch(const VList& sources, const VList& targets, DynamicFSM& fsm);

  void addAtom(const Node& n);
  void alternate(const Node& n);
  void concatenate(const Node& n);
  void literal(const Node& n);
  void group(const Node& n);
  void finish(const Node&);

  DynamicFSMPtr getFsm() const { return Fsm; }

private:
  DynamicFSMPtr Fsm;
  std::stack< Fragment > Stack;
};

bool parse(const std::string& text, SyntaxTree& tree, boost::function< void(std::string, Node) > callback);
