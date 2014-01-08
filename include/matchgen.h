#pragma once

#include "fwd_pointers.h"

#include <limits>
#include <set>
#include <string>

void matchgen(const NFA& g, std::set<std::string>& matches, uint32_t maxMatches = std::numeric_limits<uint32_t>::max(), uint32_t maxLoops = 1);

