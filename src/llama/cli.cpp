#include "cli.h"

#include <ostream>

namespace po = boost::program_options;

Cli::Cli():
  All()
{
  // Command selection options
  po::options_description commands("Command selection");
  commands.add_options()
    ("help", "display this help message")
    ("version,V", "print version information and exit")
    ;

   All.add(commands);
}

std::unique_ptr<Options> Cli::parse(std::ostream& out, int argc, const char* argv[]) {
  auto opts = std::unique_ptr<Options>(new Options);

  po::variables_map optsMap;
  po::store(
    po::command_line_parser(argc, argv).options(All)
                                       .run(),
    optsMap
  );
  po::notify(optsMap);

  // convert some options to commands
  if (optsMap.count("version")) {
    opts->Command = "version";
  }
  return opts;
}
