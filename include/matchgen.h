#pragma once

#include "basic.h"
#include "fwd_pointers.h"

#include <set>

void matchgen(const NFA& g, std::set<std::string>& matches, uint32_t maxMatches = std::numeric_limits<uint32_t>::max(), uint32_t maxLoops = 1);

