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

void addNewEdge(DynamicFSM::vertex_descriptor source, DynamicFSM::vertex_descriptor target, DynamicFSM& fsm);

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords, uint32 enc = CP_ASCII, bool caseSensitive = true, bool litMode = false);
DynamicFSMPtr createDynamicFSM(KwInfo& keyInfo, uint32 enc, bool caseSensitive, bool litMode);

class Visitor {
public:
  void discoverVertex(DynamicFSM::vertex_descriptor, const DynamicFSM&) const {}
 
  void treeEdge(DynamicFSM::vertex_descriptor, DynamicFSM::vertex_descriptor, const DynamicFSM&) const {}
};

void bfs(const DynamicFSM& graph, DynamicFSM::vertex_descriptor start, Visitor visitor);

uint32 calculateLMin(const DynamicFSM& graph);

boost::shared_ptr<SkipTable> calculateSkipTable(const DynamicFSM& graph);

ProgramPtr createProgram(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);
void nextBytes(ByteSet& set, DynamicFSM::vertex_descriptor v, const DynamicFSM& graph);

boost::shared_ptr<VmInterface> initVM(const std::vector<std::string>& keywords, SearchInfo& info);

std::vector< std::vector< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph);

uint32 maxOutbound(const std::vector< std::vector< DynamicFSM::vertex_descriptor > >& tranTable);

void writeGraphviz(std::ostream& out, const DynamicFSM& graph);
