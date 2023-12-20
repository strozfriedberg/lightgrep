#pragma once

#include "options.h"

#include "boost_program_options.h"

void parse_opts(int argc, const char* const * argv,
                boost::program_options::options_description& desc,
                Options& opts);
