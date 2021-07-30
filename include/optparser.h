#pragma once

#include "options.h"

#include <boost/program_options.hpp>

void parse_opts(int argc, const char* const * argv,
                boost::program_options::options_description& desc,
                Options& opts);
