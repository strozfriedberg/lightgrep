#pragma once

#include "basic.h"
#include "graph.h"
#include "encoding.h"

#include <boost/function.hpp>

#include <stack>

struct Node {
  enum NodeType {
    REGEXP,
    ALTERNATION,
    CONCATENATION,
    GROUP,
    PLUS,
    STAR,
    QUESTION,
    ELEMENT,
    DOT,
    CHAR_CLASS,
    LITERAL,
    IGNORE
  };

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

typedef std::vector< Graph::vertex_descriptor > VList;

class FastVList {
public:
  friend std::ostream& operator<<(std::ostream& out, const FastVList& list);

  FastVList();
  FastVList(Graph::vertex_descriptor v);
  FastVList(const FastVList& x);

  FastVList& operator=(const FastVList& x);

  Graph::vertex_descriptor operator[](unsigned int i) const;

  size_t size() const;

  void reset();
  void reset(Graph::vertex_descriptor v);
  void merge(const FastVList& x);
  void add(Graph::vertex_descriptor v);

  void patch(const FastVList& targets, Graph& fsm) const;

private:
  Graph::vertex_descriptor Single;
  boost::scoped_ptr< VList > List;  
};

std::ostream& operator<<(std::ostream& out, const FastVList& list);

struct Fragment {
  Fragment(): Skippable(false) {}
  Fragment(Graph::vertex_descriptor in, const Node& n): InList(in), N(n), Skippable(false) {}

  FastVList InList, OutList;
  Node N;
  bool Skippable;

  void initFull(Graph::vertex_descriptor in, const Node& n) { N = n; Skippable = false; InList.reset(in); OutList.reset(in); }
  void initFull(Graph::vertex_descriptor in, Graph::vertex_descriptor out, const Node& n) { N = n; Skippable = false; InList.reset(in); OutList.reset(out); }
  void reset(const Node& n) { Skippable = false; N = n; InList.reset(); OutList.reset(); }

  void addToOut(Graph::vertex_descriptor v) {
    OutList.add(v);
  }

  void addToIn(Graph::vertex_descriptor v) {
    InList.add(v);
  }

  void merge(const Fragment& f);
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
  void setCaseSensitive(bool caseSensitive); // defaults to true
  void setSizeHint(uint64 reserveSize);

  void patch(Fragment& first, const Fragment& second, const Node& n);
  void patch(const FastVList& sources, const FastVList& targets);

  void addElement(const Node& n);
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

  GraphPtr getFsm() const { return Fsm; }
  void resetFsm() { Fsm.reset(); }

  void setCurLabel(uint32 lbl) { CurLabel = lbl; }

private:
  void setLiteralTransition(TransitionPtr& state, byte val);

  bool          IsGood,
                CaseSensitive;
  uint32        CurLabel;
  uint64        ReserveSize;
  boost::shared_ptr<Encoding> Enc;
  GraphPtr Fsm;
  std::stack< Fragment > Stack;
  boost::scoped_array<byte> TempBuf;
  std::vector< TransitionPtr > LitFlyweights;
  
  Fragment  TempFrag;
};

bool parse(const std::string& text, bool litMode, SyntaxTree& tree, NodeHandler& callback);
