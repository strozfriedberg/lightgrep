#pragma once

#include "basic.h"

#include "instructions.h"
#include "dynamicFSM.h"
#include "vm.h"

struct SearchInfo {
  
};

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords);

ProgramPtr createProgram(const DynamicFSM& graph);

ProgramPtr createProgram2(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);

boost::shared_ptr<Vm> initVM(const std::vector<std::string>& keywords, SearchInfo& info);
