#include <scope/test.h>

#include "cli.h"

#include <regex>
#include <sstream>
#include <thread>

SCOPE_TEST(testCLIVersion) {
  const char *args[] = {"llama", "--version"};
  Cli cli;
  auto opts = cli.parse(2, args);
  SCOPE_ASSERT_EQUAL("version", opts->Command);
}

SCOPE_TEST(testCLIHelp) {
  const char *args[] = {"llama", "--help"};
  Cli cli;
  auto opts = cli.parse(2, args);
  SCOPE_ASSERT_EQUAL("help", opts->Command);
}

SCOPE_TEST(testCLICommandPrecedence) {
  // help has precedence over version
  const char *args1[] = {"llama", "--version", "--help"};
  const char *args2[] = {"llama", "--help", "--version"};
  Cli cli;
  auto opts = cli.parse(3, args1);
  SCOPE_ASSERT_EQUAL("help", opts->Command);
  opts = cli.parse(3, args2);
  SCOPE_ASSERT_EQUAL("help", opts->Command);
}

SCOPE_TEST(testCLIDefaultCommand) {
  const char *args[] = {"llama"};
  Cli cli;
  auto opts = cli.parse(1, args);
  SCOPE_ASSERT_EQUAL("search", opts->Command);
}

SCOPE_TEST(testCLIKeywordsFiles) {
  const char *args[] = {"llama", "-f", "mypatterns.txt", "--file",
                        "morepatterns.txt"};
  std::vector<std::string> expected{"mypatterns.txt", "morepatterns.txt"};
  Cli cli;
  auto opts = cli.parse(5, args);
  SCOPE_ASSERT_EQUAL(expected, opts->KeyFiles);
}

SCOPE_TEST(testCLIReal) {
  const char *args[] = {"llama", "-f", "patterns.txt", "output.tar",
                        "nosnits_workstation.E01"};
  Cli cli;
  auto opts = cli.parse(5, args);
  SCOPE_ASSERT_EQUAL("nosnits_workstation.E01", opts->Input);
}

SCOPE_TEST(testCLInumThreads) {
  const char *args[] = {"llama", "-j", "17"};
  Cli cli;
  auto opts = cli.parse(3, args);
  SCOPE_ASSERT_EQUAL(17u, opts->NumThreads);

  opts = cli.parse(1, args); // test default
  SCOPE_ASSERT_EQUAL(std::thread::hardware_concurrency(), opts->NumThreads);
}

SCOPE_TEST(testCLICodec) {
  Cli cli;

  const char* gzipArgs[] = {"llama", "-f", "patterns.txt", "--codec=gzip", "output.tar", "nosnits_workstation.E01"};
  auto opts = cli.parse(6, gzipArgs);
  SCOPE_ASSERT_EQUAL(Options::CODEC_GZIP, opts->Codec);

  const char* lz4Args[] = {"llama", "-f", "patterns.txt", "--codec=lz4", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(6, lz4Args);
  SCOPE_ASSERT_EQUAL(Options::CODEC_LZ4, opts->Codec);

  const char* noneArgs[] = {"llama", "-f", "patterns.txt", "--codec=none", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(6, noneArgs);
  SCOPE_ASSERT_EQUAL(Options::CODEC_NONE, opts->Codec);

  const char* badArgs[] = {"llama", "-f", "patterns.txt", "--codec=bad", "output.tar", "nosnits_workstation.E01"};
  SCOPE_EXPECT(opts = cli.parse(6, badArgs), std::invalid_argument);

  const char* defaultArgs[] = {"llama", "-f", "patterns.txt", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(5, defaultArgs);
  SCOPE_ASSERT_EQUAL(Options::CODEC_LZ4, opts->Codec);
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
  // The mantra is to test everything that could possibly fail. It's unlikely
  // that boost::program_options will fail, so we just need to do a smoke test.
  Cli cli;
  std::stringstream output;
  cli.printHelp(output);
  auto outStr = output.str();
  SCOPE_ASSERT(outStr.find("Usage: llama") != std::string::npos);
}
