#pragma once

#include "basic.h"
#include "dynamicFSM.h"

class SkipTable {
public:
  SkipTable(uint32 numVertices);

  void relax(uint32 val);
  void setDistance(DynamicFSM::vertex_descriptor source, DynamicFSM::vertex_descriptor target, const DynamicFSM& graph);
  void calculateTransitions(DynamicFSM::vertex_descriptor v, const DynamicFSM& graph);
  void finishSkipVec();

  uint32 l_min() const { return LMin; }

  const std::vector<uint32>& skipVec() const { return SkipVec; } 

private:
  std::vector<uint32> Distance,
                      SkipVec;
  uint32 LMin;
  ByteSet TempSet;
};
