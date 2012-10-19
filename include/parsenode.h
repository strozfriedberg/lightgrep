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
#include "rangeset.h"
#include "byteset.h"

#include <ostream>

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
    BYTE,
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
    UnicodeSet CodePoints;
  };

*/

  ParseNode *Left;

  union {
    ParseNode* Right;
    int Val;
    struct {
      ByteSet Bytes;
      bool Additive;
    } Breakout;
    struct {
      uint32 Min, Max;
    } Rep;
  };

  UnicodeSet CodePoints;

  ParseNode(): Type(LITERAL), Left(nullptr), Val(0) {}

  ParseNode(NodeType t, uint32 v):
    Type(t), Left(nullptr), Val(v), CodePoints()
  {
    if (Type == CHAR_CLASS) {
      Breakout.Bytes.reset();
      Breakout.Additive = true;
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
    Type(t), Left(nullptr), CodePoints(first, last + 1)
  {
    Breakout.Bytes.reset();
    Breakout.Additive = true;
  }

  explicit ParseNode(NodeType t, const ByteSet& b):
    Type(t), Left(nullptr), CodePoints()
  {
    Breakout.Bytes = b;
    Breakout.Additive = true;
  }

  ParseNode(NodeType t, const UnicodeSet& u):
    Type(t), Left(nullptr), CodePoints(u)
  {
    Breakout.Bytes.reset();
    Breakout.Additive = true;
  }

  ParseNode(NodeType t, const UnicodeSet& u, const ByteSet& b, bool additive = true):
    Type(t), Left(nullptr), CodePoints(u)
  {
    Breakout.Bytes = b;
    Breakout.Additive = additive;
  }

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
//      new(&CodePoints) UnicodeSet(n.CodePoints);
      CodePoints = n.CodePoints;
      Breakout.Bytes = n.Breakout.Bytes;
      Breakout.Additive = n.Breakout.Additive;
      break;
    default:
      Val = n.Val;
      break;
    }
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
      return CodePoints == o.CodePoints &&
             Breakout.Additive == o.Breakout.Additive &&
             Breakout.Bytes == o.Breakout.Bytes;
    default:
      return Val == o.Val;
    }
  }
};

std::ostream& operator<<(std::ostream& out, const ParseNode& n);

void printTreeDetails(std::ostream& out, const ParseNode& n);
void repetition(std::ostream& out, uint32 min, uint32 max);
