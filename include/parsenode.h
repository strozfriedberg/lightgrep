#pragma once

#include "basic.h"
#include "rangeset.h"

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
    DOT,
    CHAR_CLASS,
    LITERAL,
    TEMPORARY
  };

  NodeType Type;

  ParseNode *Left;

  union  {
    ParseNode* Right;
    int Val;
    struct {
      uint32 Min, Max;
    } Rep;
  };

  UnicodeSet Bits;

  ParseNode(): Type(LITERAL), Left(0), Val(0), Bits() {}

  ParseNode(NodeType t, uint32 v): Type(t), Left(0), Val(v), Bits() {
    if (Type == CHAR_CLASS) {
      Bits.set(v);
    }
  }

  ParseNode(NodeType t, ParseNode* l):
    Type(t), Left(l), Right(0), Bits() {}

  ParseNode(NodeType t, ParseNode* l, ParseNode* r):
    Type(t), Left(l), Right(r), Bits() {}

  ParseNode(NodeType t, ParseNode* l, uint32 min, uint32 max):
    Type(t), Left(l), Bits()
  {
    Rep.Min = min;
    Rep.Max = max;
  }

  ParseNode(NodeType t, uint32 first, uint32 last):
    Type(t), Left(0), Bits(first, last + 1) {}

  explicit ParseNode(NodeType t, const ByteSet& b):
    Type(t), Left(0), Bits(b) {}

<<<<<<< HEAD
  ParseNode(NodeType t, const UnicodeSet& b):
    Type(t), Left(0), Bits(b) {}

  ParseNode(const ParseNode& n): Type(n.Type), Left(n.Left) {
    init_union(n);
  }

  ~ParseNode() {
/*
    // we have to call the dtor for UnicodeSet ourselves,
    // because it has a nontrivial dtor and is part of a union
    if (Type == CHAR_CLASS) {
      Bits.~UnicodeSet();
    }
*/
  }

  ParseNode& operator=(const ParseNode& n) {
    // self-assignment is bad, due to the placement new in init_union
    if (this != &n) {
      Type = n.Type;
      Left = n.Left;
      init_union(n);
    }
    return *this;
  }

  void init_union(const ParseNode& n) {
    switch (Type) {
    case ALTERNATION:
    case CONCATENATION:
      Right = n.Right;
      break;
    case REPETITION:
    case REPETITION_NG:
      Rep = n.Rep;
      break;
    case CHAR_CLASS:
//      new(&Bits) UnicodeSet(n.Bits);
      Bits = n.Bits;
      break;
    default:
      Val = n.Val;
      break;
    }
  }

  explicit ParseNode(NodeType t, const UnicodeSet& b):
    Type(t), Left(0), Bits(b) {}

  void range(uint32 first, uint32 last) {
    Bits.insert(first, last + 1);
  }
};

std::ostream& operator<<(std::ostream& out, const ParseNode& n);

void printTree(std::ostream& out, const ParseNode& n);
void printTreeDetails(std::ostream& out, const ParseNode& n);
void repetition(std::ostream& out, uint32 min, uint32 max);
