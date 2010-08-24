#pragma once

#include "basic.h"

#include <set>

#include "instructions.h"
#include "dynamicFSM.h"
#include "vm.h"

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

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords, uint32 enc = CP_ASCII);
DynamicFSMPtr createDynamicFSM(KwInfo& keyInfo, uint32 enc);

uint32 calculateLMin(const DynamicFSM& graph);

ProgramPtr createProgram(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);

boost::shared_ptr<Vm> initVM(const std::vector<std::string>& keywords, SearchInfo& info);

std::vector< std::vector< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph);

uint32 maxOutbound(const std::vector< std::vector< DynamicFSM::vertex_descriptor > >& tranTable);

void writeGraphviz(std::ostream& out, const DynamicFSM& graph);

void mergeIntoFSM(DynamicFSM& fsm, const DynamicFSM& addend, uint32 keyIdx);
