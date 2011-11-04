#pragma once

#include "basic.h"
#include "graph.h"
#include "encoding.h"
#include "parsenode.h"
#include "parsetree.h"

#include <limits>
#include <stack>

typedef std::vector<Graph::vertex> InListT;
typedef std::vector< std::pair<Graph::vertex, uint32> > OutListT;

static const uint32 NOSKIP = std::numeric_limits<uint32>::max();

struct Fragment {
  Fragment(): Skippable(NOSKIP) {}
  Fragment(Graph::vertex in, const ParseNode& n):
    InList(1, in), N(n), Skippable(NOSKIP) {}

  /*
   * InList is the list of vertices in this fragment which have incoming
   * edges from outside the fragment. OutList is the is the list of vertices
   * in this fragment which have edges leaving the fragment.
   */
  InListT InList;
  OutListT OutList;
  ParseNode N;

  uint32 Skippable;

  void initFull(Graph::vertex in, const ParseNode& n) {
    N = n;
    Skippable = NOSKIP;
    InList.clear();
    InList.push_back(in);
    OutList.clear();
    OutList.push_back(std::make_pair(in, 0));
  }

  void reset(const ParseNode& n) {
    N = n;
    Skippable = NOSKIP;
    InList.clear();
    OutList.clear();
  }

  void assign(Fragment& f) {
    InList.swap(f.InList);
    OutList.swap(f.OutList);
    N = f.N;
    Skippable = f.Skippable;
  }
};

class NFABuilder {
public:
  NFABuilder();

  void reset();

  virtual void callback(const ParseNode& n);

  void setEncoding(const boost::shared_ptr<Encoding>& e);
  void setCaseSensitive(bool caseSensitive); // defaults to true
  void setSizeHint(uint64 reserveSize);

  void alternate(const ParseNode& n);
  void concatenate(const ParseNode& n);
  void star(const ParseNode& n);
  void plus(const ParseNode& n);
  void question(const ParseNode& n);
  void repetition(const ParseNode& n);
  void star_ng(const ParseNode& n);
  void plus_ng(const ParseNode& n);
  void question_ng(const ParseNode& n);
  void repetition_ng(const ParseNode& n);
  void literal(const ParseNode& n);
  void dot(const ParseNode& n);
  void charClass(const ParseNode& n);

  void finish(const ParseNode&);

  GraphPtr getFsm() const { return Fsm; }
  void resetFsm() { Fsm.reset(); }

  void setCurLabel(uint32 lbl) { CurLabel = lbl; }

  std::stack<Fragment>& stack() { return Stack; }

  bool build(const ParseTree& tree);

private:
  void setLiteralTransition(Graph& g, const Graph::vertex& v, byte val);

  void patch_mid(OutListT& src, const InListT& dst, uint32 dstskip);
  void patch_pre(OutListT& src, const InListT& dst);
  void patch_post(OutListT& src, const InListT& dst);

  void traverse(const ParseNode* n);

  bool IsGood, CaseSensitive;
  uint32 CurLabel;
  uint64 ReserveSize;
  boost::shared_ptr<Encoding> Enc;
  GraphPtr Fsm;
  std::stack<Fragment> Stack;
  std::stack<const ParseNode*, std::vector<const ParseNode*> > ChildStack, ParentStack;

  boost::scoped_array<byte> TempBuf;
  std::vector<TransitionPtr> LitFlyweights;

  Fragment TempFrag;
};
