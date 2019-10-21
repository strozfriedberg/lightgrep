#pragma once

#include <iosfwd>
#include <memory>

#include <boost/program_options.hpp>

#include "options.h"

class Cli {
public:
	Cli();

	std::unique_ptr<Options> parse(int argc, const char* const argv[]) const;

	void printVersion(std::ostream& out) const;
	void printHelp(std::ostream& out) const;

private:
	std::string figureOutCommand(const boost::program_options::variables_map& optsMap) const;

	boost::program_options::options_description All;
};
