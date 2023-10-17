#pragma once

#include "options.h"

void parse_opts(int argc, const char* const * argv,
                po::options_description& desc,
                Options& opts);
