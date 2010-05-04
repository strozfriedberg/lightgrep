#pragma once

#include "basic.h"

#include "dynamicFSM.h"
#include "staticFSM.h"
#include "instructions.h"

DynamicFSMPtr createDynamicFSM(const std::vector<std::string>& keywords);

boost::shared_ptr<StaticFSM> convert_to_static(const DynamicFSM& graph);

uint32 staticStateSize(DynamicFSM::vertex_descriptor state, const DynamicFSM& graph);

boost::shared_ptr< std::vector<Instruction> > createProgram(const DynamicFSM& graph);

ByteSet firstBytes(const DynamicFSM& graph);