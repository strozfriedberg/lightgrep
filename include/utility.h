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

std::vector< std::set< DynamicFSM::vertex_descriptor > > pivotStates(DynamicFSM::vertex_descriptor source, const DynamicFSM& graph);
