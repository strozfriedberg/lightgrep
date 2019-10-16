#include <scope/test.h>

#include "cli.h"

#include <regex>

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
