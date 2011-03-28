#pragma once

#include "basic.h"

#include <iostream>

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

  Node(NodeType t, Node* l, Node* r, unsigned int first, unsigned int last):
    Type(t), Left(l), Right(r), Val(0)
  {
    Bits.reset();
    range(first, last);
  }

  Node(NodeType t, Node* l, Node* r, unsigned int v):
    Type(t), Left(l), Right(r), Val(v) { Bits.reset(); Bits.set(Val); }

  Node(NodeType t, Node* l, Node* r, unsigned int v, const ByteSet& b):
    Type(t), Left(l), Right(r), Val(v), Bits(b) {}

  void range(byte first, byte last) {
    for (uint32 i = first; i <= last; ++i) {
      Bits.set(i);
    }
  }
};

std::ostream& operator<<(std::ostream& out, const Node& n);

