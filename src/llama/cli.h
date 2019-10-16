#pragma once

#include <memory>

#include <boost/program_options.hpp>

#include "options.h"

class Cli {
public:
	Cli();

	std::unique_ptr<Options> parse(int argc, const char* argv[]) const;

private:
	std::string figureOutCommand(const boost::program_options::variables_map& optsMap) const;

	boost::program_options::options_description All;
};
