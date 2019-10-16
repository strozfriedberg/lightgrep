#include "cli.h"

namespace po = boost::program_options;

Cli::Cli():
  All()
{
  // Command selection options
  po::options_description commands("Command selection -- in precedence order");
  commands.add_options()
    ("help", "display this help message")
    ("version,V", "print version information and exit")
    ;

   All.add(commands);
}

std::unique_ptr<Options> Cli::parse(int argc, const char* argv[]) const {
  auto opts = std::unique_ptr<Options>(new Options);

  po::variables_map optsMap;
  po::store(
    po::command_line_parser(argc, argv).options(All)
                                       .run(),
    optsMap
  );
  po::notify(optsMap);

  opts->Command = figureOutCommand(optsMap);

  return opts;
}

std::string Cli::figureOutCommand(const boost::program_options::variables_map& optsMap) const {
  // convert some options to commands
  if (optsMap.count("help")) {
    return "help";
  }
  if (optsMap.count("version")) {
    return "version";
  }
  return "";
}
