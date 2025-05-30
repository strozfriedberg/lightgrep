/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "basic.h"
#include "rangeset.h"
#include "byteset.h"

#include <new>
#include <ostream>

static const uint32_t UNBOUNDED = std::numeric_limits<uint32_t>::max();

struct ParseNode {
  enum NodeType {
    REGEXP,
    LOOKBEHIND_POS,
    LOOKBEHIND_NEG,
    LOOKAHEAD_POS,
    LOOKAHEAD_NEG,
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

  struct RepetitionInternals {
    uint32_t Min, Max;
  };

  struct ParentalNodeInternals {
    ParseNode* Left;
    union {
      ParseNode* Right;
      RepetitionInternals Rep;
    };
  };

  struct CharacterClassInternals {
    UnicodeSet CodePoints;
    struct {
      ByteSet Bytes;
      bool Additive;
    } Breakout;
  };

  union {
    ParentalNodeInternals Child;
    CharacterClassInternals Set;
    int Val;
  };

  ParseNode(): Type(LITERAL), Val(0) {}

  ParseNode(NodeType t, uint32_t v): Type(t) {
    if (Type == CHAR_CLASS) {
// FIXME: should we check that Set.CodePoints is word-aligned?
      new(&Set.CodePoints) UnicodeSet();
      Set.Breakout.Bytes.reset();
      Set.Breakout.Additive = true;
    }
    else {
      Val = v;
    }
  }

  ParseNode(NodeType t, ParseNode* l, ParseNode* r = nullptr): Type(t) {
    Child.Left = l;
    Child.Right = r;
  }

  ParseNode(NodeType t, ParseNode* l, uint32_t min, uint32_t max): Type(t) {
    Child.Left = l;
    Child.Rep.Min = min;
    Child.Rep.Max = max;
  }

  ParseNode(NodeType t, uint32_t first, uint32_t last): Type(t) {
    new(&Set.CodePoints) UnicodeSet(first, last + 1);
    Set.Breakout.Bytes.reset();
    Set.Breakout.Additive = true;
  }

  explicit ParseNode(NodeType t, const ByteSet& b): Type(t) {
    new(&Set.CodePoints) UnicodeSet();
    Set.Breakout.Bytes = b;
    Set.Breakout.Additive = true;
  }

  ParseNode(NodeType t, const UnicodeSet& u): Type(t) {
    new(&Set.CodePoints) UnicodeSet(u);
    Set.Breakout.Bytes.reset();
    Set.Breakout.Additive = true;
  }

  ParseNode(NodeType t, const UnicodeSet& u, const ByteSet& b, bool additive = true): Type(t)
  {
    new(&Set.CodePoints) UnicodeSet(u);
    Set.Breakout.Bytes = b;
    Set.Breakout.Additive = additive;
  }

  ParseNode(const ParseNode& o): Type(o.Type) {
    switch (Type) {
    case REGEXP:
    case LOOKBEHIND_POS:
    case LOOKBEHIND_NEG:
    case LOOKAHEAD_POS:
    case LOOKAHEAD_NEG:
      Child.Left = o.Child.Left;
      Child.Right = nullptr;
      break;
    case ALTERNATION:
    case CONCATENATION:
      Child.Left = o.Child.Left;
      Child.Right = o.Child.Right;
      break;
    case REPETITION:
    case REPETITION_NG:
      Child.Left = o.Child.Left;
      Child.Rep = o.Child.Rep;
      break;
    case CHAR_CLASS:
      new(&Set.CodePoints) UnicodeSet(o.Set.CodePoints);
      Set.Breakout = o.Set.Breakout;
      break;
    default:
      Val = o.Val;
      break;
    }
  }

  ParseNode(ParseNode&& o): Type(o.Type) {
    switch (Type) {
    case REGEXP:
    case LOOKBEHIND_POS:
    case LOOKBEHIND_NEG:
    case LOOKAHEAD_POS:
    case LOOKAHEAD_NEG:
      Child.Left = o.Child.Left;
      Child.Right = nullptr;
      break;
    case ALTERNATION:
    case CONCATENATION:
      Child.Left = o.Child.Left;
      Child.Right = o.Child.Right;
      break;
    case REPETITION:
    case REPETITION_NG:
      Child.Left = o.Child.Left;
      Child.Rep = o.Child.Rep;
      break;
    case CHAR_CLASS:
      new(&Set.CodePoints) UnicodeSet(std::move(o.Set.CodePoints));
      Set.Breakout = o.Set.Breakout;
      break;
    default:
      Val = o.Val;
      break;
    }
  }

  ParseNode& operator=(const ParseNode& o) {
    if (this != &o) {
      if (Type == CHAR_CLASS && o.Type != CHAR_CLASS) {
        Set.CodePoints.~UnicodeSet();
      }

      switch (o.Type) {
      case REGEXP:
      case LOOKBEHIND_POS:
      case LOOKBEHIND_NEG:
      case LOOKAHEAD_POS:
      case LOOKAHEAD_NEG:
        Child.Left = o.Child.Left;
        Child.Right = nullptr;
        break;
      case ALTERNATION:
      case CONCATENATION:
        Child.Left = o.Child.Left;
        Child.Right = o.Child.Right;
        break;
      case REPETITION:
      case REPETITION_NG:
        Child.Left = o.Child.Left;
        Child.Rep = o.Child.Rep;
        break;
      case CHAR_CLASS:
        if (Type == CHAR_CLASS) {
          Set.CodePoints = o.Set.CodePoints;
        }
        else {
          new(&Set.CodePoints) UnicodeSet(o.Set.CodePoints);
        }
        Set.Breakout = o.Set.Breakout;
        break;
      default:
        Val = o.Val;
        break;
      }

      Type = o.Type;
    }

    return *this;
  }

  ParseNode& operator=(ParseNode&& o) {
    if (Type == CHAR_CLASS) {
      Set.CodePoints.~UnicodeSet();
    }

    Type = o.Type;

    switch (Type) {
    case REGEXP:
    case LOOKBEHIND_POS:
    case LOOKBEHIND_NEG:
    case LOOKAHEAD_POS:
    case LOOKAHEAD_NEG:
      Child.Left = o.Child.Left;
      Child.Right = nullptr;
      break;
    case ALTERNATION:
    case CONCATENATION:
      Child.Left = o.Child.Left;
      Child.Right = o.Child.Right;
      break;
    case REPETITION:
    case REPETITION_NG:
      Child.Left = o.Child.Left;
      Child.Rep = o.Child.Rep;
      break;
    case CHAR_CLASS:
      new(&Set.CodePoints) UnicodeSet(std::move(o.Set.CodePoints));
      Set.Breakout = o.Set.Breakout;
      break;
    default:
      Val = o.Val;
      break;
    }

    return *this;
  }

  ~ParseNode() {
    // We have to call the dtor for UnicodeSet ourselves, because
    // it has a nontrivial dtor and is part of an unrestricted union.
    if (Type == CHAR_CLASS) {
      Set.CodePoints.~UnicodeSet();
    }
  }

  void setType(NodeType t) {
    if (Type != t) {
      if (Type == CHAR_CLASS) {
        Set.CodePoints.~UnicodeSet();
      }

      Type = t;
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
    case LOOKBEHIND_POS:
    case LOOKBEHIND_NEG:
    case LOOKAHEAD_POS:
    case LOOKAHEAD_NEG:
      return !Child.Left ? !o.Child.Left :
        (o.Child.Left ? *Child.Left == *o.Child.Left : false);
    case ALTERNATION:
    case CONCATENATION:
      return
        (!Child.Left ? !o.Child.Left :
          (o.Child.Left ? *Child.Left == *o.Child.Left : false)) &&
        (!Child.Right ? !o.Child.Right :
          (o.Child.Right ? *Child.Right == *o.Child.Right : false));
    case REPETITION:
    case REPETITION_NG:
      return Child.Rep.Min == o.Child.Rep.Min &&
             Child.Rep.Max == o.Child.Rep.Max &&
             (!Child.Left ? !o.Child.Left :
               (o.Child.Left ? *Child.Left == *o.Child.Left : false));
    case CHAR_CLASS:
      return Set.Breakout.Additive == o.Set.Breakout.Additive &&
             Set.Breakout.Bytes == o.Set.Breakout.Bytes &&
             Set.CodePoints == o.Set.CodePoints;
    default:
      return Val == o.Val;
    }
  }
};

std::ostream& operator<<(std::ostream& out, const ParseNode& n);

void printTreeDetails(std::ostream& out, const ParseNode& n);
void repetition(std::ostream& out, uint32_t min, uint32_t max);
