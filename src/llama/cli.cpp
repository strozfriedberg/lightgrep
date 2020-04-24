#include "cli.h"

#include <ostream>
#include <stdexcept>
#include <thread>

namespace po = boost::program_options;

Cli::Cli() : All(), Opts(new Options) {
  // Command selection options
  po::options_description commands("Command selection -- in precedence order");
  commands.add_options()("help,h", "Display this help message")(
      "version,V", "Print version information and exit");

  po::options_description ioOpts("Input/Output Options");
  ioOpts.add_options()
    ("output", po::value<std::string>(&Opts->TarPath), "Tar file to create for output, extension will be added")
    ("codec", po::value<std::string>(&CodecSelect)->default_value("lz4"), "Output tar compression method (none|gzip|lz4)")
    ("input", po::value<std::string>(&Opts->Input), "Evidence file or directory to process")
  ;

  po::options_description configOpts("Configuration Options");
  configOpts.add_options()(
      "file,f",
      po::value<std::vector<std::string>>(&Opts->KeyFiles)
          ->composing()
          ->value_name("FILE"),
      "Read one or more newline separated patterns from file")(
      "num_threads,j",
      po::value<unsigned int>(&Opts->NumThreads)
          ->default_value(std::thread::hardware_concurrency())
          ->value_name("THREADS"),
      "Number of worker threads to use");

  All.add(commands).add(ioOpts).add(configOpts);

  PosOpts.add("output", 1).add("input", -1);
}

std::shared_ptr<Options> Cli::parse(int argc, const char *const argv[]) const {
  po::variables_map optsMap;
  po::store(po::command_line_parser(argc, argv)
                .options(All)
                .positional(PosOpts)
                .run(),
            optsMap);
  po::notify(optsMap);

  Opts->Command = figureOutCommand(optsMap);
  Opts->Codec = figureOutCodec();

  return Opts;
}

void Cli::printVersion(std::ostream &out) const {
  out << "llama - lightgrep's amazing media analyzer, pre-alpha " << __DATE__
      << std::endl;
}

void Cli::printHelp(std::ostream &out) const {
  printVersion(out);
  out << "\nUsage: llama [OPTIONS] OUTPUT_FILE INPUT_FILE\n"
      << All << std::endl;
}

std::string Cli::figureOutCommand(
    const boost::program_options::variables_map &optsMap) const {
  // convert some options to commands
  if (optsMap.count("help")) {
    return "help";
  }
  if (optsMap.count("version")) {
    return "version";
  }
  return "search";
}

Options::Codecs Cli::figureOutCodec() const {
  if (0 == CodecSelect.compare("none")) {
    return Options::CODEC_NONE;
  }
  else if (0 == CodecSelect.compare("gzip")) {
    return Options::CODEC_GZIP;
  }
  else if (0 == CodecSelect.compare("lz4")) {
    return Options::CODEC_LZ4;
  }
  throw std::invalid_argument("'" + CodecSelect + "' is not a valid option for --codec");
}
