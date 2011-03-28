#pragma once

#include "node.h"
#include "parsetree.h"

#include <string>

bool parse(const std::string& text, bool litMode, ParseTree& tree);

