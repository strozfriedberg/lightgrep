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
    REPETITION,
    REPETITION_NG,
    DOT,
    CHAR_CLASS,
    LITERAL,
    TEMPORARY
  };

  NodeType Type;

/*
  TOOD: For minimum size, the union should be:

  union {
    struct {
      ParseNode* Left;
      union {
        ParseNode* Right;
        struct {
          uint32 Min, Max;
        } Rep;
      };
    } Inner;

    int Val;
    UnicodeSet Bits;
  };

*/

  ParseNode *Left;

  union {
    ParseNode* Right;
    int Val;
    struct {
      uint32 Min, Max;
    } Rep;
  };

  UnicodeSet Bits;

  ParseNode(): Type(LITERAL), Left(nullptr), Val(0) {}

  ParseNode(NodeType t, uint32 v): Type(t), Left(nullptr), Val(v), Bits() {
    if (Type == CHAR_CLASS) {
      Bits.set(v);
    }
  }

  ParseNode(NodeType t, ParseNode* l):
    Type(t), Left(l), Right(nullptr) {}

  ParseNode(NodeType t, ParseNode* l, ParseNode* r):
    Type(t), Left(l), Right(r) {}

  ParseNode(NodeType t, ParseNode* l, uint32 min, uint32 max):
    Type(t), Left(l)
  {
    Rep.Min = min;
    Rep.Max = max;
  }

  ParseNode(NodeType t, uint32 first, uint32 last):
    Type(t), Left(nullptr), Right(nullptr), Bits(first, last + 1) {}

  explicit ParseNode(NodeType t, const ByteSet& b):
    Type(t), Left(nullptr), Right(nullptr), Bits(b) {}

  ParseNode(NodeType t, const UnicodeSet& b):
    Type(t), Left(nullptr), Right(nullptr), Bits(b) {}

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
    case REGEXP:
      Right = nullptr;
      break;
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
      Right = nullptr;
      break;
    default:
      Val = n.Val;
      break;
    }
  }

  void range(uint32 first, uint32 last) {
    Bits.insert(first, last + 1);
  }

  bool operator==(const ParseNode& o) const {
    if (this == &o) {
      return true;
    }

    if (Type != o.Type) {
      return false;
    }

    switch (Type) {
    case REGEXP:
      return !Left ? !o.Left : (o.Left ? *Left == *o.Left : false);
    case ALTERNATION:
    case CONCATENATION:
      return (!Left ? !o.Left : (o.Left ? *Left == *o.Left : false)) &&
             (!Right ? !o.Right : (o.Right ? *Right == *o.Right : false));
    case REPETITION:
    case REPETITION_NG:
      return Rep.Min == o.Rep.Min && Rep.Max == o.Rep.Max &&
             !Left ? !o.Left : (o.Left ? *Left == *o.Left : false);
    case CHAR_CLASS:
      return Bits == o.Bits;
    default:
      return Val == o.Val;
    }
  }
};

std::ostream& operator<<(std::ostream& out, const ParseNode& n);

void printTreeDetails(std::ostream& out, const ParseNode& n);
void repetition(std::ostream& out, uint32 min, uint32 max);
