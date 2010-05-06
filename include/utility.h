#pragma once

#include "basic.h"

#include "instructions.h"
#include "dynamicFSM.h"

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords);

boost::shared_ptr< std::vector<Instruction> > createProgram(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);