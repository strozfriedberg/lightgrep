
#include "graph.h"

#include <limits>
#include <set>
#include <string>

void matchgen(const Graph& g, std::set<std::string>& matches, uint32 max_loops = 1, uint32 max_matches = std::numeric_limits<uint32>::max());

