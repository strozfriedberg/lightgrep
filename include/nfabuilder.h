#pragma once

#include "basic.h"
#include "graph.h"
#include "encoding.h"
#include "node.h"
#include "parsetree.h"

#include <limits>
#include <stack>

typedef std::vector<Graph::vertex> InListT;
typedef std::vector< std::pair<Graph::vertex, uint32> > OutListT;

static const uint32 NOSKIP = std::numeric_limits<uint32>::max();

struct Fragment {
  Fragment(): Skippable(NOSKIP) {}
  Fragment(Graph::vertex in, const Node& n):
    InList(1, in), N(n), Skippable(NOSKIP) {}

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

class NFABuilder {
public:
  NFABuilder();

  void reset();

  virtual void callback(const std::string& type, const Node& n);

  void setEncoding(const boost::shared_ptr<Encoding>& e);
  void setCaseSensitive(bool caseSensitive); // defaults to true
  void setSizeHint(uint64 reserveSize);

  void alternate(const Node& n);
  void concatenate(const Node& n);
  void star(const Node& n);
  void plus(const Node& n);
  void question(const Node& n);
  void repeat(const Node& n);
  void star_ng(const Node& n);
  void plus_ng(const Node& n);
  void question_ng(const Node& n);
  void repeat_ng(const Node& n);
  void literal(const Node& n);
  void dot(const Node& n);
  void charClass(const Node& n, const std::string& lbl);

  void finish(const Node&);

  GraphPtr getFsm() const { return Fsm; }
  void resetFsm() { Fsm.reset(); }

  void setCurLabel(uint32 lbl) { CurLabel = lbl; }

  std::stack<Fragment>& stack() { return Stack; }
 
  bool build(const ParseTree& tree);
 
private:
  void setLiteralTransition(TransitionPtr& state, byte val);

  void patch_pre(OutListT& src, const InListT& dst);
  void patch_post(const OutListT& src, const InListT& dst);

  void traverse(const Node* n);

  bool IsGood, CaseSensitive;
  uint32 CurLabel;
  uint64 ReserveSize;
  boost::shared_ptr<Encoding> Enc;
  GraphPtr Fsm;
  std::stack<Fragment> Stack;
  boost::scoped_array<byte> TempBuf;
  std::vector<TransitionPtr> LitFlyweights;
  
  Fragment  TempFrag;
};
