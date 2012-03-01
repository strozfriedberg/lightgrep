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

  union {
    int Val;
    struct {
      uint32 Min, Max;
    } Range;
    ByteSet Bits;
  };

  ParseNode(): Type(LITERAL), Left(0), Right(0), Val(0) {}

  ParseNode(NodeType t, uint32 v):
    Type(t), Left(0), Right(0)
  {
    if (Type == CHAR_CLASS) {
      Bits.reset();
      Bits.set(v);
    }
    else {
      Val = v;
    }
  }

  ParseNode(NodeType t, ParseNode* l):
    Type(t), Left(l), Right(0), Val(0) {}

  ParseNode(NodeType t, ParseNode* l, ParseNode* r):
    Type(t), Left(l), Right(r), Val(0) {}

  ParseNode(NodeType t, ParseNode* l, uint32 min, uint32 max):
    Type(t), Left(l), Right(0)
  {
    Range.Min = min;
    Range.Max = max;
  }

  ParseNode(NodeType t, uint32 first, uint32 last):
    Type(t), Left(0), Right(0), Bits()
  {
    Bits.reset();
    range(first, last);
  }

  explicit ParseNode(NodeType t, const ByteSet& b):
    Type(t), Left(0), Right(0), Bits(b) {}

  void range(uint32 first, uint32 last) {
    for (uint32 i = first; i <= last; ++i) {
      Bits.set(i);
    }
  }
};

std::ostream& operator<<(std::ostream& out, const ParseNode& n);

void printTree(std::ostream& out, const ParseNode& n);
void printTreeDetails(std::ostream& out, const ParseNode& n);
void repetition(std::ostream& out, uint32 min, uint32 max);
