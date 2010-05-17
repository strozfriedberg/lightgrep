#pragma once

#include "basic.h"

#include "instructions.h"
#include "dynamicFSM.h"

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords);

ProgramPtr createProgram(const DynamicFSM& graph);

ProgramPtr createProgram2(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);
