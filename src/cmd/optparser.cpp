#include <fstream>

#include "basic.h"
#include "optparser.h"
#include "encodings.h"

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <string>

#include <boost/lexical_cast.hpp>

namespace po = boost::program_options;

// This is a special parser which puts all options after '--' into "pargs"
std::vector<po::option> end_of_opts_parser(std::vector<std::string>& args) {
  std::vector<po::option> result;

  std::vector<std::string>::const_iterator i(args.begin());
  if (i != args.end() && *i == "--") {
    po::option opt;
    opt.string_key = "pargs";

    for (++i; i != args.end(); ++i) {
      opt.value.push_back(*i);
      opt.original_tokens.push_back(*i);
    }

    result.push_back(opt);
    args.clear();
  }

  return result;
}

void parse_opts(int argc, char** argv,
                po::options_description& desc, Options& opts) {

  //
  // set up argument parsing
  //

  std::string command;

  po::positional_options_description posOpts;
  posOpts.add("pargs", -1);

  // NB: Would be more appropriate to use a std::queue for pargs, but
  // boost::options_description throws a fit if we do.
  std::vector<std::string> pargs;

  po::options_description hidden;
  hidden.add_options()
    ("pargs", po::value<std::vector<std::string>>(&pargs)->multitoken(), "positional arguments");

  // Command selection options
  po::options_description general("Command selection");
  general.add_options()
    ("command,c", po::value<std::string>(&command)->default_value("search"), "command to perform [search|graph|prog|samp|validate|server]")
    ("help", "display this help message")
    ("list-encodings", "list known encodings")
    ;

  // Pattern options
  po::options_description pats("Pattern selection and interpretation");
  pats.add_options()
    ("keywords,k", po::value<std::vector<std::string>>(&opts.KeyFiles), "path to file containing keywords")
    ("pattern,p", po::value<std::vector<std::string>>(&opts.CmdLinePatterns), "a keyword on the command-line")
    ("encoding,e", po::value<std::string>(&opts.Encoding)->default_value("ASCII"), "encodings to use (e.g., ASCII, UTF-8)")
    ("ignore-case,i", "ignore case distinctions")
    ("fixed-strings,F", "interpret patterns as fixed strings")
    ;

  // I/O options
  po::options_description io("Input and output");
  io.add_options()
    ("input", po::value<std::string>(&opts.Input)->default_value("-"), "file to search")
    ("output,o", po::value<std::string>(&opts.Output)->default_value("-"), "output file (stdout default)")
    ("recursive,r", "traverse directories recursively")
    ("with-filename,H", "print the filename for each match")
    ("no-filename,h", "suppress the filename for each match")
    ("no-output", "do not output hits (good for profiling)")
    ("block-size", po::value<uint32>(&opts.BlockSize)->default_value(8 * 1024 * 1024), "Block size to use for buffering, in bytes")
    ;

  // Server options
  po::options_description server("Server");
  server.add_options()
    ("address", po::value<std::string>(&opts.ServerAddr)->default_value("localhost"), "specify address")
    ("port", po::value<unsigned short>(&opts.ServerPort)->default_value(12777), "specify port number")
    ("server-log", po::value<std::string>(&opts.ServerLog), "file for server logging");

  // Other options
  po::options_description misc("Miscellaneous");
  misc.add_options()
    ("no-det", "do not determinize NFAs")
    ("binary", "Output program as binary")
    ("program-file", po::value<std::string>(&opts.ProgramFile), "read search program from file")
    #ifdef LBT_TRACE_ENABLED
    ("begin-debug", po::value<uint64>(&opts.DebugBegin)->default_value(std::numeric_limits<uint64>::max()), "offset for beginning of debug logging")
    ("end-debug", po::value<uint64>(&opts.DebugEnd)->default_value(std::numeric_limits<uint64>::max()), "offset for end of debug logging")
    #endif
    ;

  // desc collects all of the options in case of --help
  desc.add(general)
      .add(pats)
      .add(io)
      .add(server)
      .add(misc);

  po::options_description allOpts;
  allOpts.add(desc).add(hidden);

  //
  // do option parsing
  //

  po::variables_map optsMap;
  po::store(
    po::command_line_parser(argc, argv).options(allOpts)
                                       .positional(posOpts)
                                       .extra_style_parser(&end_of_opts_parser)
                                       .run(),
    optsMap
  );
  po::notify(optsMap);

  //
  // determine which command we got
  //

// FIXME: do something to exclude multiple command specfications
// FIXME: do something to complain about inapplicable options

  opts.Command = Options::BOGUS;

  // convert help option to command
  if (optsMap.count("help")) {
    opts.Command = Options::HELP;
  }

  // convert list-encodings option to command
  if (optsMap.count("list-encodings")) {
    opts.Command =  Options::ENCODINGS;
  }

  if (opts.Command == Options::BOGUS) {
    std::map<std::string,Options::CommandTypes> cmds;
    cmds.insert(std::make_pair("search",   Options::SEARCH));
    cmds.insert(std::make_pair("graph",    Options::GRAPH));
    cmds.insert(std::make_pair("prog",     Options::PROGRAM));
    cmds.insert(std::make_pair("samp",     Options::SAMPLES));
    cmds.insert(std::make_pair("validate", Options::VALIDATE));
    cmds.insert(std::make_pair("server",   Options::SERVER));

    auto i = cmds.find(command);
    if (i != cmds.end()) {
      opts.Command = i->second;
    }
  }

  //
  // sort out the other options based on our command
  //

  switch (opts.Command) {
  case Options::SEARCH:
  case Options::GRAPH:
  case Options::PROGRAM:
  case Options::SAMPLES:
  case Options::VALIDATE:
  case Options::SERVER:
    // determine the source of our patterns
    if (!optsMap["pattern"].empty()) {
      // keywords from --pattern
      if (!optsMap["keywords"].empty()) {
        throw po::error("--pattern and --keywords are incompatible options");
      }
    }
    else {
      if (!optsMap["keywords"].empty()) {
        // keywords from --keywords
      }
      else {
        // keywords from parg
        if (pargs.empty()) {
          throw po::required_option("keywords");
        }

        opts.KeyFiles.push_back(pargs.front());
        pargs.erase(pargs.begin());
      }
    }

    opts.CaseInsensitive = optsMap.count("ignore-case") > 0;
    opts.LiteralMode = optsMap.count("fixed-strings") > 0;
    opts.Binary = optsMap.count("binary") > 0;
    opts.NoOutput = optsMap.count("no-output") > 0;
    opts.Determinize = optsMap.count("no-det") == 0;
    opts.Recursive = optsMap.count("recursive") > 0;

    // uppercase the encoding name
    std::transform(opts.Encoding.begin(), opts.Encoding.end(),
                   opts.Encoding.begin(), toupper);

    if (optsMap.count("with-filename") && optsMap.count("no-filename")) {
      throw po::error("--with-filename and --no-filename are incompatible options");
    }

    if (opts.Command == Options::SEARCH) {
      // filename printing defaults off for single files, on for multiple files
      opts.PrintPath = optsMap.count("with-filename") > 0;

      // determine the source of our input
      if (!optsMap["input"].defaulted()) {
        // input from --input
        opts.Inputs.push_back(optsMap["input"].as<std::string>());
      }
      else if (!pargs.empty()) {
        // input from pargs
        opts.Inputs = pargs;
        pargs.clear();
        opts.PrintPath = optsMap.count("no-filename") == 0;
      }
      else {
        // input from stdin
        opts.Inputs.push_back("-");
      }
    }
    else if (opts.Command == Options::SAMPLES) {
      opts.SampleLimit =
        std::numeric_limits<std::set<std::string>::size_type>::max();
      opts.LoopLimit = 1;

      if (!pargs.empty()) {
        opts.SampleLimit = boost::lexical_cast<uint32>(pargs.front());
        pargs.erase(pargs.begin());

        if (!pargs.empty()) {
          opts.LoopLimit = boost::lexical_cast<uint32>(pargs.front());
          pargs.erase(pargs.begin());
        }
      }
    }

    // there should be no unused positional arguments now
    if (!pargs.empty()) {
      throw po::too_many_positional_options_error();
    }

    break;

  case Options::HELP:
  case Options::ENCODINGS:
    // nothing else to do
    break;

  default:
    throw po::invalid_option_value(command);
  }
}
