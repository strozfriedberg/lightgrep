#pragma once

#include "basic.h"

#include <set>

#include "instructions.h"
#include "dynamicFSM.h"
#include "vm_interface.h"

struct SearchInfo {
  
};

enum Encodings {
  CP_ASCII = 1,
  CP_UCS16 = 2
};

struct KwInfo {
  typedef std::vector<std::string> StringVec;
  
  StringVec Keywords,
            Encodings;
  std::vector< std::pair<uint32, uint32> > PatternsTable;
};

typedef DynamicFSM::in_edge_iterator InEdgeIt;
typedef std::pair<InEdgeIt, InEdgeIt> InEdgeRange;
typedef DynamicFSM::out_edge_iterator OutEdgeIt;
typedef std::pair< OutEdgeIt, OutEdgeIt > OutEdgeRange;

void addNewEdge(DynamicFSM::vertex_descriptor source, DynamicFSM::vertex_descriptor target, DynamicFSM& fsm);

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords, uint32 enc = CP_ASCII, bool caseSensitive = true);
DynamicFSMPtr createDynamicFSM(KwInfo& keyInfo, uint32 enc, bool caseSensitive);

uint32 calculateLMin(const DynamicFSM& graph);

boost::shared_ptr<SkipTable> calculateSkipTable(const DynamicFSM& graph);

ProgramPtr createProgram(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);
void nextBytes(ByteSet& set, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph);

boost::shared_ptr<VmInterface> initVM(const std::vector<std::string>& keywords, SearchInfo& info);

std::vector< std::vector< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph);

uint32 maxOutbound(const std::vector< std::vector< DynamicFSM::vertex_descriptor > >& tranTable);

void writeGraphviz(std::ostream& out, const DynamicFSM& graph);
