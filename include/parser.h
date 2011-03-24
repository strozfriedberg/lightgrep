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
    PLUS_NG,
    STAR_NG,
    QUESTION_NG,
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

typedef std::vector<Graph::vertex> InListT;
typedef std::vector< std::pair<Graph::vertex, uint32> > OutListT;

static const uint32 NOSKIP = std::numeric_limits<uint32>::max();

struct Fragment {
  Fragment(): Skippable(NOSKIP) {}
  Fragment(Graph::vertex in, const Node& n): InList(1, in), N(n), Skippable(NOSKIP) {}

  /*
   * InList is the list of vertices in this fragment which have incoming
   * edges from outside the fragment. OutList is the is the list of vertices
   * in this fragment which have edges leaving the fragment.
   */ 
  InListT InList;
  OutListT OutList;
  Node N;

  uint32 Skippable;

  void initFull(Graph::vertex in, const Node& n) {
    N = n;
    Skippable = NOSKIP;
    InList.clear();
    InList.push_back(in);
    OutList.clear();
    OutList.push_back(std::make_pair(in, 0));
  }

  void reset(const Node& n) {
    N = n;
    Skippable = NOSKIP;
    InList.clear(); 
    OutList.clear();
  }
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

  void addElement(const Node& n);
  void alternate(const Node& n);
  void concatenate(const Node& n);
  void star(const Node& n);
  void plus(const Node& n);
  void question(const Node& n);
  void star_ng(const Node& n);
  void plus_ng(const Node& n);
  void question_ng(const Node& n);
  void literal(const Node& n);
  void group(const Node& n);
  void dot(const Node& n);
  void finish(const Node&);
  void charClass(const Node& n, const std::string& lbl);

  GraphPtr getFsm() const { return Fsm; }
  void resetFsm() { Fsm.reset(); }

  void setCurLabel(uint32 lbl) { CurLabel = lbl; }

  std::stack<Fragment>& stack() { return Stack; }
  
private:
  void setLiteralTransition(TransitionPtr& state, byte val);

  void patch_pre(OutListT& src, const InListT& dst);
  void patch_post(const OutListT& src, const InListT& dst);

  bool          IsGood,
                CaseSensitive;
  uint32        CurLabel;
  uint64        ReserveSize;
  boost::shared_ptr<Encoding> Enc;
  GraphPtr Fsm;
  std::stack<Fragment> Stack;
  boost::scoped_array<byte> TempBuf;
  std::vector<TransitionPtr> LitFlyweights;
  
  Fragment  TempFrag;
};

bool parse(const std::string& text, bool litMode, SyntaxTree& tree, NodeHandler& callback);
