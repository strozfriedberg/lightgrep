#pragma once

#include "basic.h"

#include <iostream>
#include <limits>

static const uint32 UNBOUNDED = std::numeric_limits<uint32>::max();

struct ParseNode {

  enum NodeType {
    REGEXP,
    ALTERNATION,
    CONCATENATION,
    GROUP,
    REPETITION,
    REPETITION_NG,
    ELEMENT,
    DOT,
    CHAR_CLASS,
    LITERAL,
    LG_IGNORE
  };

  NodeType  Type;
  ParseNode *Left,
            *Right;
  int       Val;
  uint32    Min,
            Max;
  ByteSet   Bits;

  ParseNode(): Type(LITERAL), Left(0), Right(0), Val(0), Min(0), Max(0)
  {
    Bits.reset();
  }

  ParseNode(NodeType t, uint32 v):
    Type(t), Left(0), Right(0), Val(v), Min(0), Max(0)
  {
    Bits.reset();
    Bits.set(v);
  }

  ParseNode(NodeType t, ParseNode* l):
    Type(t), Left(l), Right(0), Val(0), Min(0), Max(0) {}

  ParseNode(NodeType t, ParseNode* l, ParseNode* r):
    Type(t), Left(l), Right(r), Val(0), Min(0), Max(0) {}

  ParseNode(NodeType t, ParseNode* l, uint32 min, uint32 max):
    Type(t), Left(l), Right(0), Val(0), Min(min), Max(max) {}

  ParseNode(NodeType t, uint32 first, uint32 last):
    Type(t), Left(0), Right(0), Val(0), Min(0), Max(0)
  {
    Bits.reset();
    range(first, last);
  }

  explicit ParseNode(NodeType t, const ByteSet& b):
    Type(t), Left(0), Right(0), Val(0), Min(0), Max(0), Bits(b) {}

  void range(byte first, byte last) {
    for (uint32 i = first; i <= last; ++i) {
      Bits.set(i);
    }
  }
};

std::ostream& operator<<(std::ostream& out, const ParseNode& n);

void printTree(std::ostream& out, const ParseNode& n);
void printTreeDetails(std::ostream& out, const ParseNode& n);
void repetition(std::ostream& out, uint32 min, uint32 max);

