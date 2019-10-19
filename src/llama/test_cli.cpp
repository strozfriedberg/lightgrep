#include <scope/test.h>

#include "cli.h"

#include <regex>
#include <sstream>

SCOPE_TEST(testCLIVersion) {
	const char* args[] = {"llama", "--version"};
	Cli cli;
	auto opts = cli.parse(2, args);
	SCOPE_ASSERT_EQUAL("version", opts->Command);
}

SCOPE_TEST(testCLIHelp) {
	const char* args[] = {"llama", "--help"};
	Cli cli;
	auto opts = cli.parse(2, args);
	SCOPE_ASSERT_EQUAL("help", opts->Command);
}

SCOPE_TEST(testCLICommandPrecedence) {
	// help has precedence over version
	const char* args1[] = {"llama", "--version", "--help"};
	const char* args2[] = {"llama", "--help", "--version"};
	Cli cli;
	auto opts = cli.parse(3, args1);
	SCOPE_ASSERT_EQUAL("help", opts->Command);
	opts = cli.parse(3, args2);
	SCOPE_ASSERT_EQUAL("help", opts->Command);
}

SCOPE_TEST(testPrintVersion) {
	Cli cli;
	std::stringstream output;
	cli.printVersion(output);
	auto outStr = output.str();
	std::regex re("pre-alpha.+20\\d\\d");
	// SCOPE_ASSERT_EQUAL("20191019", outStr);
	SCOPE_ASSERT(std::regex_search(outStr, re));
}

SCOPE_TEST(testPrintHelp) {
	Cli cli;
	std::stringstream output;
	cli.printHelp(output);
	auto outStr = output.str();
	SCOPE_ASSERT(outStr.find("Usage: llama") != std::string::npos);
}
