#pragma once

#include "basic.h"
#include "automata.h"
#include "parsenode.h"

#include <vector>

typedef std::vector<NFA::VertexDescriptor> InListT;
typedef std::vector<std::pair<NFA::VertexDescriptor, uint32>> OutListT;

static const uint32 NOSKIP = std::numeric_limits<uint32>::max();

struct Fragment {
  Fragment(): Skippable(NOSKIP) {}

  Fragment(NFA::VertexDescriptor in, const ParseNode& n):
    InList(1, in), N(n), Skippable(NOSKIP) {}

  /*
   * InList is the list of vertices in this fragment which have incoming
   * edges from outside the fragment. OutList is the is the list of vertices
   * in this fragment which have edges leaving the fragment.
   */
  InListT InList;
  OutListT OutList;
  ParseNode N;

  uint32 Skippable;

  void initFull(NFA::VertexDescriptor in, const ParseNode& n) {
    N = n;
    Skippable = NOSKIP;
    InList.clear();
    InList.push_back(in);
    OutList.clear();
    OutList.emplace_back(in, 0);
  }

  void reset(const ParseNode& n) {
    N = n;
    Skippable = NOSKIP;
    InList.clear();
    OutList.clear();
  }

  void assign(Fragment& f) {
    InList.swap(f.InList);
    OutList.swap(f.OutList);
    N = f.N;
    Skippable = f.Skippable;
  }
};
