#pragma once

#include "basic.h"
#include "graph.h"

class SkipTable {
public:
  SkipTable(uint32 numVertices);

  void relax(uint32 val);
  void setDistance(Graph::vertex source, Graph::vertex target, const Graph& graph);
  void calculateTransitions(Graph::vertex v, const Graph& graph);
  void finishSkipVec();

  uint32 l_min() const { return LMin; }

  const std::vector<uint32>& skipVec() const { return SkipVec; } 

private:
  std::vector<uint32> Distance,
                      SkipVec;
  uint32 LMin;
  ByteSet TempSet;
};
