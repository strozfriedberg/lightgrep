#pragma once

#include "basic.h"

#include <set>

#include "instructions.h"
#include "dynamicFSM.h"
#include "vm.h"

struct SearchInfo {
  
};

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords);

ProgramPtr createProgram(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);

boost::shared_ptr<Vm> initVM(const std::vector<std::string>& keywords, SearchInfo& info);

std::vector< std::vector< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph);

void writeGraphviz(std::ostream& out, const DynamicFSM& graph);

void mergeIntoFSM(DynamicFSM& fsm, const DynamicFSM& addend, uint32 keyIdx);