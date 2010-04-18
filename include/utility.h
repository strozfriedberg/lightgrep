#pragma once

#include "basic.h"

#include "dynamicFSM.h"
#include "staticFSM.h"

boost::shared_ptr<StaticFSM> convert_to_static(const DynamicFSM& graph);
uint32 staticStateSize(DynamicFSM::vertex_descriptor state, const DynamicFSM& graph);
