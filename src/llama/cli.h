#pragma once

#include <memory>
#include <iosfwd>

#include <boost/program_options.hpp>

#include "options.h"

class Cli {
public:
	Cli();

	std::unique_ptr<Options> parse(std::ostream& out, int argc, const char* argv[]);

private:
	boost::program_options::options_description All;
};
