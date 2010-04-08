#pragma once

#include "basic.h"

#include "dynamicFSM.h"
#include "staticFSM.h"

boost::shared_ptr<StaticFSM> convert_to_static(const DynamicFSM& graph);
