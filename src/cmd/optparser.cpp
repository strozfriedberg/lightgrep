#include <fstream>

#include "optparser.h"

#include <lightgrep/encodings.h>

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
    ("command,c", po::value<std::string>(&command)->value_name("CMD")->default_value("search"), "command to perform [search|graph|prog|samp|validate]")
    ("help", "display this help message")
    ("list-encodings", "list known encodings")
    ("version,V", "print version information and exit")
    ;

  // Pattern options
  po::options_description pats("Pattern selection and interpretation");
  pats.add_options()
    ("keywords,k", po::value<std::vector<std::string>>(&opts.KeyFiles)->composing()->value_name("FILE"), "path to keywords file")
    ("pattern,p", po::value<std::vector<std::string>>(&opts.CmdLinePatterns)->composing()->value_name("PATTERN"), "a keyword on the command-line")
    ("encoding,e", po::value<std::vector<std::string>>(&opts.Encodings)->default_value(std::vector<std::string>{"ASCII"}, "ASCII")->composing()->value_name("ENCODING"), "encoding to use (e.g., ASCII, UTF-8)")
    ("ignore-case,i", "ignore case distinctions")
    ("fixed-strings,F", "interpret patterns as fixed strings")
    ;

  // I/O options
  po::options_description io("Input and output");
  io.add_options()
    ("output,o", po::value<std::string>(&opts.Output)->value_name("FILE")->default_value("-"), "output file (stdout default)")
    ("arg-file,a", po::value<std::vector<std::string>>(&opts.InputLists)->composing()->value_name("FILE"), "read input paths from file")
    ("recursive,r", "traverse directories recursively")
    ("with-filename,H", "print the filename for each match")
    ("no-filename,h", "suppress the filename for each match")
    ("after-context,A", po::value<int32_t>(&opts.AfterContext)->value_name("NUM"), "print NUM lines of trailing context")
    ("before-context,B", po::value<int32_t>(&opts.BeforeContext)->value_name("NUM"), "print NUM lines of leading context")
    ("context,C", po::value<int32_t>(&opts.BeforeContext)->value_name("NUM"), "print NUM lines of context")
    ("group-separator", po::value<std::string>(&opts.GroupSeparator)->value_name("SEP")->default_value("--"), "use SEP as the group separator")
    ("no-output", "do not output hits (good for profiling)")
    ("block-size", po::value<uint32_t>(&opts.BlockSize)->default_value(8 * 1024 * 1024)->value_name("BYTES"), "block size to use for buffering, in bytes")
    ("mmap", "memory-map input file(s)")
    ;

  // Other options
  po::options_description misc("Miscellaneous");
  misc.add_options()
    ("determinize-depth", po::value<uint32_t>(&opts.DeterminizeDepth)->value_name("NUM")->default_value(std::numeric_limits<uint32_t>::max()), "determinze NFA to NUM depth")
    ("binary", "output program as binary")
    ("program-file", po::value<std::string>(&opts.ProgramFile)->value_name("FILE"), "read search program from file")
    #ifdef LBT_TRACE_ENABLED
    ("begin-debug", po::value<uint64_t>(&opts.DebugBegin)->default_value(std::numeric_limits<uint64_t>::max()), "offset for beginning of debug logging")
    ("end-debug", po::value<uint64_t>(&opts.DebugEnd)->default_value(std::numeric_limits<uint64_t>::max()), "offset for end of debug logging")
    #endif
    ;

  // desc collects all of the options in case of --help
  desc.add(general)
      .add(pats)
      .add(io)
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

  // convert some options to commands
  if (optsMap.count("help")) {
    opts.Command = Options::SHOW_HELP;
  }
  else if (optsMap.count("version")) {
    opts.Command = Options::SHOW_VERSION;
  }
  else if (optsMap.count("list-encodings")) {
    opts.Command = Options::LIST_ENCODINGS;
  }

  if (opts.Command == Options::BOGUS) {
    std::map<std::string,Options::CommandTypes> cmds;
    cmds.insert(std::make_pair("search",   Options::SEARCH));
    cmds.insert(std::make_pair("graph",    Options::GRAPH));
    cmds.insert(std::make_pair("prog",     Options::PROGRAM));
    cmds.insert(std::make_pair("samp",     Options::SAMPLES));
    cmds.insert(std::make_pair("validate", Options::VALIDATE));

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
    opts.Recursive = optsMap.count("recursive") > 0;
    opts.MemoryMapped = optsMap.count("mmap") > 0;

    if (optsMap.count("context") > 0) {
      // "-C N" is equivalent to "-B N -A N"
      opts.AfterContext = opts.BeforeContext;
    }

    if (opts.BeforeContext != -1 || opts.AfterContext != -1) {
      // -C N, -B N, -A N imply --mmap
      opts.MemoryMapped = true;
    }

    // uppercase encoding names
    for (std::string& e : opts.Encodings) {
      std::transform(e.begin(), e.end(), e.begin(), toupper);
    }

    if (optsMap.count("with-filename") && optsMap.count("no-filename")) {
      throw po::error("--with-filename and --no-filename are incompatible options");
    }

    if (opts.Command == Options::SEARCH) {
      // filename printing defaults off for single files, on for multiple files
      opts.PrintPath = optsMap.count("with-filename") > 0;

      // determine the source of our input
      if (optsMap.count("arg-file") > 0) {
        opts.PrintPath = optsMap.count("no-filename") == 0;
      }

      if (!pargs.empty()) {
        // input from pargs
        opts.Inputs = pargs;
        pargs.clear();
        opts.PrintPath = optsMap.count("no-filename") == 0;
      }
      else if (opts.InputLists.empty()) {
        // input from stdin
        opts.Inputs.push_back("-");
      }

      if (opts.MemoryMapped && std::find(opts.Inputs.begin(), opts.Inputs.end(), "-") != opts.Inputs.end()) {
        throw po::error("--mmap is incompatible with reading from stdin");
      }
    }
    else if (opts.Command == Options::SAMPLES) {
      opts.SampleLimit =
        std::numeric_limits<std::set<std::string>::size_type>::max();
      opts.LoopLimit = 1;

      if (!pargs.empty()) {
        opts.SampleLimit = boost::lexical_cast<uint32_t>(pargs.front());
        pargs.erase(pargs.begin());

        if (!pargs.empty()) {
          opts.LoopLimit = boost::lexical_cast<uint32_t>(pargs.front());
          pargs.erase(pargs.begin());
        }
      }
    }

    // there should be no unused positional arguments now
    if (!pargs.empty()) {
      throw po::too_many_positional_options_error();
    }

    break;

  case Options::SHOW_VERSION:
  case Options::SHOW_HELP:
  case Options::LIST_ENCODINGS:
    // nothing else to do
    break;

  default:
    throw po::invalid_option_value(command);
  }
}
