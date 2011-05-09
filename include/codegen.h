#pragma once

#include <limits>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "basic.h"
#include "graph.h"
#include "instructions.h"
#include "utility.h"

static const uint32 NONE = std::numeric_limits<uint32>::max();

struct StateLayoutInfo {
  uint32 Start,
         NumEval,
         NumOther,
         CheckIndex;
  OpCodes Op;

  StateLayoutInfo(): Start(NONE), NumEval(NONE), NumOther(NONE), CheckIndex(NONE), Op(UNINITIALIZED) {}

  StateLayoutInfo(uint32 s, uint32 e, uint32 o, uint32 chk = NONE): Start(s), NumEval(e), NumOther(o), CheckIndex(chk), Op(UNINITIALIZED) {}

  uint32 numTotal() const { return NumEval + NumOther; }

  uint32 end() const { return Start + numTotal(); }

  bool operator==(const StateLayoutInfo& x) const {
    return Start == x.Start && NumEval == x.NumEval && NumOther == x.NumOther && CheckIndex == x.CheckIndex;
  }
};

struct CodeGenHelper {
  CodeGenHelper(uint32 numStates): DiscoverRanks(numStates, NONE),
    Snippets(numStates), Guard(0), NumDiscovered(0), NumChecked(0) {}

  void discover(Graph::vertex v, const Graph& graph) {
    DiscoverRanks[v] = NumDiscovered++;
    if (graph.inDegree(v) > 1) {
      Snippets[v].CheckIndex = ++NumChecked;
    }
  }

  void addSnippet(uint32 state, uint32 numEval, uint32 numOther) {
    StateLayoutInfo& info(Snippets[state]);
    info.Start = Guard;
    info.NumEval = numEval;
    info.NumOther = numOther;
    Guard += info.numTotal();
  }

  std::vector<uint32> DiscoverRanks;
  std::vector<StateLayoutInfo> Snippets;
  uint32 Guard,
         NumDiscovered,
         NumChecked;
};

typedef std::vector< std::vector< Graph::vertex > > TransitionTbl;

class CodeGenVisitor {
public:
  CodeGenVisitor(boost::shared_ptr<CodeGenHelper> helper): Helper(helper) {}

  void discover_vertex(Graph::vertex v, const Graph& graph);

  uint32 calcJumpTableSize(Graph::vertex v, const Graph& graph, uint32 outDegree); 

  void finish_vertex(Graph::vertex v, const Graph& graph); 

private:
  boost::shared_ptr<CodeGenHelper> Helper;
};

void specialVisit(const Graph& graph, Graph::vertex startVertex, CodeGenVisitor& vis);

