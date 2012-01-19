
#include "automata.h"

#include <limits>
#include <set>
#include <string>

void matchgen(const NFA& g, std::set<std::string>& matches, uint32 max_matches = std::numeric_limits<uint32>::max(), uint32 max_loops = 1);

