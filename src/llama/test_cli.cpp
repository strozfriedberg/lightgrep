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

std::ostream& operator<<(std::ostream& out, Codec c) {
  return out << static_cast<int>(c); 
}

SCOPE_TEST(testCLICodec) {
  Cli cli;

  const char* gzipArgs[] = {"llama", "--codec=gzip", "output.tar", "nosnits_workstation.E01"};
  auto opts = cli.parse(4, gzipArgs);
  SCOPE_ASSERT_EQUAL(Codec::GZIP, opts->OutputCodec);

  const char* lz4Args[] = {"llama", "--codec=lz4", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(4, lz4Args);
  SCOPE_ASSERT_EQUAL(Codec::LZ4, opts->OutputCodec);

  const char* noneArgs[] = {"llama", "--codec=none", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(4, noneArgs);
  SCOPE_ASSERT_EQUAL(Codec::NONE, opts->OutputCodec);

  const char* lzmaArgs[] = {"llama", "--codec=lzma", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(4, lzmaArgs);
  SCOPE_ASSERT_EQUAL(Codec::LZMA, opts->OutputCodec);

  const char* bz2Args[] = {"llama", "--codec=bzip2", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(4, bz2Args);
  SCOPE_ASSERT_EQUAL(Codec::BZIP2, opts->OutputCodec);

  const char* lzoArgs[] = {"llama", "--codec=lzo", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(4, lzoArgs);
  SCOPE_ASSERT_EQUAL(Codec::LZOP, opts->OutputCodec);

  const char* xzArgs[] = {"llama", "--codec=xz", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(4, xzArgs);
  SCOPE_ASSERT_EQUAL(Codec::XZ, opts->OutputCodec);

  const char* badArgs[] = {"llama", "--codec=bad", "output.tar", "nosnits_workstation.E01"};
  SCOPE_EXPECT(opts = cli.parse(4, badArgs), std::invalid_argument);

  const char* defaultArgs[] = {"llama", "output.tar", "nosnits_workstation.E01"};
  opts = cli.parse(3, defaultArgs);
  SCOPE_ASSERT_EQUAL(Codec::LZ4, opts->OutputCodec);
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
