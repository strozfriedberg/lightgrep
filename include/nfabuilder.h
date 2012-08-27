#pragma once

#include "basic.h"
#include "fwd_pointers.h"
#include "fragment.h"

#include <stack>

class ParseNode;
class Encoder;
class ParseTree;
class TransitionFactory;

class NFABuilder {
public:
  NFABuilder();

  void reset();

  void callback(const ParseNode& n);

  void setEncoder(const std::shared_ptr<Encoder>& e);
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
  void rawByte(const ParseNode& n);
  void dot(const ParseNode& n);
  void charClass(const ParseNode& n);

  void finish(const ParseNode&);

  NFAPtr getFsm() const { return Fsm; }
  void resetFsm() { Fsm.reset(); }

  void setCurLabel(uint32 lbl) { CurLabel = lbl; }

  std::stack<Fragment>& stack() { return Stack; }

  bool build(const ParseTree& tree);

  std::shared_ptr<TransitionFactory> getTransFac() { return TransFac; }

private:
  void init();

  void patch_mid(OutListT& src, const InListT& dst, uint32 dstskip);
  void patch_pre(OutListT& src, const InListT& dst);
  void patch_post(OutListT& src, const InListT& dst);

  void traverse(const ParseNode* root);

  bool IsGood;
  uint32 CurLabel;
  uint64 ReserveSize;
  std::shared_ptr<Encoder> Enc;
  NFAPtr Fsm;
  std::shared_ptr<TransitionFactory> TransFac;

  // these are all temporaries we need frequently
  std::unique_ptr<byte[]> TempBuf;
  Fragment TempFrag;
  std::vector<std::vector<ByteSet>> TempEncRanges;
  std::stack<Fragment> Stack;
  std::stack<const ParseNode*, std::vector<const ParseNode*>> ChildStack, ParentStack;
};
