#pragma once

#include "basic.h"
#include "fwd_pointers.h"

#include <set>

void matchgen(const NFA& g, std::set<std::string>& matches, uint32 maxMatches = std::numeric_limits<uint32>::max(), uint32 maxLoops = 1);

