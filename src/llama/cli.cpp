#include "cli.h"

#include <ostream>

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

std::unique_ptr<Options> Cli::parse(int argc, const char* const argv[]) const {
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

void Cli::printVersion(std::ostream& out) const {
  out << "llama - lightgrep's amazing media analyzer, pre-alpha " << __DATE__ << std::endl;
}

void Cli::printHelp(std::ostream& out) const {
  printVersion(out);
  out << "\nUsage: llama [OPTIONS] PATTERN_FILE [FILE...]\n"
    << All << std::endl;
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
