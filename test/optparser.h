#pragma once

#include "options.h"

#include <boost/program_options.hpp>

void parse_opts(int argc, char** argv,
                boost::program_options::options_description& desc,
                Options& opts);
