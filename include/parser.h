#pragma once

#include "basic.h"
#include "dynamicFSM.h"
#include "encoding.h"

#include <boost/function.hpp>

#include <stack>

enum NodeType {
  REGEXP,
  ALTERNATION,
  CONCATENATION,
  GROUP,
  PLUS,
  STAR,
  QUESTION,
  ATOM,
  DOT,
  CHAR_CLASS,
  LITERAL,
  IGNORE
};

struct Node {
  NodeType  Type;
  Node      *Left,
            *Right;
  int       Val;
  ByteSet   Bits;

  Node(): Type(LITERAL), Left(0), Right(0), Val(0) { Bits.reset(); }

  Node(NodeType t, Node* l, Node* r, unsigned int v): Type(t), Left(l), Right(r), Val(v) { Bits.reset(); Bits.set(Val); }

  void range(byte first, byte last) {
    for (uint32 i = first; i <= last; ++i) {
      Bits.set(i);
    }
  }
};

struct SyntaxTree {

  Node* Last;
  std::vector<Node> Store;

  Node* add(const Node& n) {
    Store.push_back(n);
    Last = &Store[Store.size()-1];
    return Last;
  }

  void reset() {
    Store.clear();
    Last = 0;
  }
};

typedef std::vector< DynamicFSM::vertex_descriptor > VList;

std::ostream& operator<<(std::ostream& out, const VList& list);

struct Fragment {
  Fragment(): Skippable(false) {}
  Fragment(VList in, const Node& n): InList(in), N(n), Skippable(false) {}
  Fragment(DynamicFSM::vertex_descriptor in, const Node& n): N(n), Skippable(false) { InList.push_back(in); }
  Fragment(VList in, const Node& n, const VList& out):
    InList(in), OutList(out), N(n), Skippable(false) {}

  std::vector< DynamicFSM::vertex_descriptor > InList, OutList;
  Node N;
  bool Skippable;

  void addToOut(DynamicFSM::vertex_descriptor v) {
    add(v, OutList);
  }

  void addToIn(DynamicFSM::vertex_descriptor v) {
    add(v, InList);
  }

  void merge(const Fragment& f);

  static void add(DynamicFSM::vertex_descriptor v, VList& list);
  static void mergeLists(VList& l1, const VList& l2);
};

class NodeHandler {
public:
  virtual ~NodeHandler() {}

  virtual void callback(const std::string&, const Node&) = 0;
};

class Parser: public NodeHandler {
public:
  Parser();

  bool good() const { return IsGood; }
  
  void reset();

  virtual void callback(const std::string& type, const Node& n);

  void setEncoding(const boost::shared_ptr<Encoding>& e);

  void patch(Fragment& first, const Fragment& second, const Node& n);
  void patch(const VList& sources, const VList& targets);

  void addAtom(const Node& n);
  void alternate(const Node& n);
  void concatenate(const Node& n);
  void star(const Node& n);
  void plus(const Node& n);
  void question(const Node& n);
  void literal(const Node& n);
  void group(const Node& n);
  void dot(const Node& n);
  void finish(const Node&);
  void charClass(const Node& n, const std::string& lbl);

  DynamicFSMPtr getFsm() const { return Fsm; }
  void resetFsm() { Fsm.reset(); }

  void setCurLabel(uint32 lbl) { CurLabel = lbl; }

private:
  bool          IsGood;
  uint32        CurLabel;
  boost::shared_ptr<Encoding> Enc;
  DynamicFSMPtr Fsm;
  std::stack< Fragment > Stack;
  boost::scoped_array<byte> TempBuf;
};

bool parse(const std::string& text, SyntaxTree& tree, NodeHandler& callback);
