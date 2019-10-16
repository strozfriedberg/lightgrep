#include <scope/test.h>

#include "cli.h"

#include <regex>
#include <sstream>

SCOPE_TEST(testCLIVersion) {
	const char* args[] = {"llama", "--version"};
	std::stringstream output;
	Cli cli;
	auto opts = cli.parse(output, 2, args);
	SCOPE_ASSERT_EQUAL("version", opts->Command);
}
