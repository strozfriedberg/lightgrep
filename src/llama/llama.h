#pragma once

#include "cli.h"

class Llama {
public:
	int run(int argc, const char* const argv[]);

private:
	Cli CliParser;
};
