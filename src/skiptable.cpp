#include "skiptable.h"

#include "utility.h"

SkipTable::SkipTable(uint32 numVertices):
  Distance(numVertices, std::numeric_limits<uint32>::max()),
  SkipVec(256, 256),
  LMin(std::numeric_limits<uint32>::max())
{
  Distance[0] = 0;
}

void SkipTable::relax(uint32 val) {
  LMin = std::min(val, LMin);
}

void SkipTable::calculateTransitions(Graph::vertex v, const Graph& graph) {
  TempSet.reset();
  nextBytes(TempSet, v, graph);
  for (uint32 i = 0; i < 256; ++i) {
    if (TempSet[i]) {
      SkipVec[i] = std::min(Distance[v], SkipVec[i]);
    }
  }
}

void SkipTable::finishSkipVec() {
  uint32 l = l_min();
  for (uint32 i = 0; i < 256; ++i) {
    SkipVec[i] = std::min(l, SkipVec[i]);
  }
}

void SkipTable::setDistance(Graph::vertex source, Graph::vertex target, const Graph& graph) {
  uint32 srcDist = Distance[source];
  uint32 tgtDist = 0;
  if (srcDist == std::numeric_limits<uint32>::max()) {
    tgtDist = srcDist;
  }
  else {
    tgtDist = std::min(srcDist + 1, Distance[target]);
  }

  if (graph[target]->IsMatch) {
    relax(tgtDist);
  }
  Distance[target] = tgtDist;
}
