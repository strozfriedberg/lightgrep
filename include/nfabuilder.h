/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
