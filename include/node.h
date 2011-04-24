#pragma once

#include "basic.h"

#include <iostream>
#include <limits>

static const uint32 UNBOUNDED = std::numeric_limits<uint32>::max();

struct Node {
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
    IGNORE
  };

  NodeType  Type;
  Node      *Left,
            *Right;
  int       Val;
  uint32    Min,
            Max;
  ByteSet   Bits;

  Node(): Type(LITERAL), Left(0), Right(0), Val(0), Min(0), Max(0)
  {
    Bits.reset();
  }

  Node(NodeType t, unsigned int v):
    Type(t), Left(0), Right(0), Val(v), Min(0), Max(0)
  {
    Bits.reset();
    Bits.set(v);
  }

  Node(NodeType t, Node* l):
    Type(t), Left(l), Right(0), Val(0), Min(0), Max(0) {}

  Node(NodeType t, Node* l, Node* r):
    Type(t), Left(l), Right(r), Val(0), Min(0), Max(0) {}

  Node(NodeType t, Node* l, uint32 min, uint32 max):
    Type(t), Left(l), Right(0), Val(0), Min(min), Max(max) {}

  Node(NodeType t, unsigned int first, unsigned int last):
    Type(t), Left(0), Right(0), Val(0), Min(0), Max(0)
  {
    Bits.reset();
    range(first, last);
  }

  explicit Node(NodeType t, const ByteSet& b):
    Type(t), Left(0), Right(0), Val(0), Min(0), Max(0), Bits(b) {}

  void range(byte first, byte last) {
    for (uint32 i = first; i <= last; ++i) {
      Bits.set(i);
    }
  }
};

std::ostream& operator<<(std::ostream& out, const Node& n);

void printTree(std::ostream& out, const Node& n);
void printTreeDetails(std::ostream& out, const Node& n);
void repetition(std::ostream& out, uint32 min, uint32 max);

