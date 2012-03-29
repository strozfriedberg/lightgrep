#include <fstream>

#include "basic.h"
#include "optparser.h"
#include "encodings.h"

#include <vector>
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

  po::positional_options_description posOpts;
  posOpts.add("pargs", -1);

  // NB: Would be more appropriate to use a std::queue for pargs, but
  // boost::options_description throws a fit if we do.
  std::vector<std::string> pargs;

  po::options_description hidden;
  hidden.add_options()
    ("pargs", po::value<std::vector<std::string>>(&pargs)->multitoken(), "positional arguments");

  desc.add_options()
    ("help", "produce help message")
    ("encoding,e", po::value<std::string>(&opts.Encoding)->default_value("ascii"), "encodings to use [ascii|ucs16|both]")
    ("command,c", po::value<std::string>(&opts.Command)->default_value("search"), "command to perform [search|graph|prog|samp|validate|server]")
    ("keywords,k", po::value<std::vector<std::string>>(&opts.KeyFiles), "path to file containing keywords")
    ("input", po::value<std::string>(&opts.Input)->default_value("-"), "file to search")
    ("output,o", po::value<std::string>(&opts.Output)->default_value("-"), "output file (stdout default)")
    ("no-output", "do not output hits (good for profiling)")
    ("no-det", "do not determinize NFAs")
    ("ignore-case,i", "ignore case distinctions")
    ("fixed-strings,F", "interpret patterns as fixed strings")
    ("binary", "Output program as binary")
    ("pattern,p", po::value<std::vector<std::string>>(&opts.CmdLinePatterns), "a keyword on the command-line")
    ("recursive,r", "traverse directories recursively")
    ("block-size", po::value<unsigned int >(&opts.BlockSize)->default_value(8 * 1024 * 1024), "Block size to use for buffering, in bytes")
    ("with-filename,H", "print the filename for each match")
    ("no-filename,h", "suppress the filename for each match")
    ("server-log", po::value<std::string>(&opts.ServerLog), "Server output to file")
    ("program-file", po::value<std::string>(&opts.ProgramFile), "Read search program from file")
    #ifdef LBT_TRACE_ENABLED
    ("begin-debug", po::value<uint64>(&opts.DebugBegin)->default_value(std::numeric_limits<uint64>::max()), "offset for beginning of debug logging")
    ("end-debug", po::value<uint64>(&opts.DebugEnd)->default_value(std::numeric_limits<uint64>::max()), "offset for end of debug logging")
    #endif
    ;

  po::options_description allOpts;
  allOpts.add(desc).add(hidden);

  po::variables_map optsMap;
  po::store(
    po::command_line_parser(argc, argv).options(allOpts)
                                       .positional(posOpts)
                                       .extra_style_parser(&end_of_opts_parser)
                                       .run(),
    optsMap
  );
  po::notify(optsMap);

  // convert test and help options to commands
  if (optsMap.count("help")) {
    opts.Command = "help";
  }
  else if (optsMap.count("test")) {
    opts.Command = "test";
  }
  else if (optsMap.count("long-test")) {
    opts.Command = "long-test";
  }

  if (opts.Command == "search" || opts.Command == "graph" ||
      opts.Command == "prog"   || opts.Command == "samp"  ||
      opts.Command == "validate" ||
      opts.Command == "server")
  {
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
    if (opts.Encoding == "ascii") {
      opts.Encoding = LG_SUPPORTED_ENCODINGS[LG_ENC_ASCII];
    }
    else if (opts.Encoding == "ucs16") {
      opts.Encoding = LG_SUPPORTED_ENCODINGS[LG_ENC_UTF_16];
    }
    else if (opts.Encoding == "both") {
      std::stringstream buf;
      buf << LG_SUPPORTED_ENCODINGS[LG_ENC_ASCII] << "," << LG_SUPPORTED_ENCODINGS[LG_ENC_UTF_16];
      opts.Encoding = buf.str();
    }
    else {
      THROW_WITH_OUTPUT(po::error, "did not recognize encoding '" << opts.Encoding << "'");
    }

    if (optsMap.count("with-filename") && optsMap.count("no-filename")) {
      throw po::error("--with-filename and --no-filename are incompatible options");
    }

    if (opts.Command == "search") {
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
    else if (opts.Command == "samp") {
      opts.SampleLimit = std::numeric_limits<std::set<std::string>::size_type>::max();
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
  }
  else if (opts.Command == "help") {
    // nothing else to do
  }
  else {
    throw po::invalid_option_value(opts.Command);
  }
}

