#include <fstream>

#include "basic.h"
#include "optparser.h"

#include <iostream>
#include <string>
#include <vector>

namespace po = boost::program_options;

void parse_opts(int argc, char** argv,
                po::options_description& desc, Options& opts) {

  //  std::vector<std::string> final_args;

  po::positional_options_description posOpts;
  posOpts.add("pargs", -1);

  // NB: Would be more appropriate to use a std::queue for pargs, but
  // boost::options_description throws a fit if we do.
  std::vector<std::string> pargs;
  
  po::options_description hidden;
  hidden.add_options()
    ("pargs", po::value< std::vector<std::string> >(&pargs), "positional arguments"); 
  
  desc.add_options()
    ("help", "produce help message")
    ("test", "run unit tests (same as test command)")
    ("encoding,e", po::value< std::string >(&opts.Encoding)->default_value("ascii"), "encodings to use [ascii|ucs16|both]")
    ("command,c", po::value< std::string >(&opts.Command)->default_value("search"), "command to perform [search|graph|prog|test|server]")
    ("keywords,k", po::value< std::string >(&opts.KeyFile), "path to file containing keywords")
    ("input", po::value< std::string >(&opts.Input)->default_value("-"), "file to search")
    ("output,o", po::value< std::string >(&opts.Output)->default_value("-"), "output file (stdout default)")
    ("no-output", "do not output hits (good for profiling)")
    ("ignore-case,i", "file to search")
    ("fixed-strings,F", "interpret patterns as fixed strings")
    ("pattern,p", po::value< std::string >(&opts.Pattern), "a single keyword on the command-line")
//    (",-", po::value< std::vector<std::string> >(&final_args)->multitoken(), "end of options")
    #ifdef LBT_TRACE_ENABLED
    ("begin-debug", po::value< uint64 >(&opts.DebugBegin)->default_value(std::numeric_limits<uint64>::max()), "offset for beginning of debug logging")
    ("end-debug", po::value< uint64 >(&opts.DebugEnd)->default_value(std::numeric_limits<uint64>::max()), "offset for end of debug logging")
    #endif
    ;
  
  po::options_description allOpts;
  allOpts.add(desc).add(hidden);

  po::variables_map optsMap;
  po::store(
    po::command_line_parser(argc, argv).options(allOpts)
                                       .positional(posOpts)
                                       .run(),
    optsMap
  );
  po::notify(optsMap);

/*
std::cout << "final_args.size() == " << final_args.size() << std::endl;

    // Handle arguments trailing the end-of-options option '--'
    switch (final_args.size()) {
    case 0:
      // no args trailing the --, nothing to do
      break;
    case 2:
      if (opts.Input != "-" || !opts.Pattern.empty()) {
        throw po::too_many_positional_options_error();
      }
      opts.Input = final_args[1];
    case 1:
      if (!opts.KeyFile.empty()) {
        throw po::too_many_positional_options_error();
      }
      opts.KeyFile = final_args[0];
      break;  
    default:
      throw po::too_many_positional_options_error();
    }
*/

  // convert test and help options to commands
  if (optsMap.count("help")) {
    opts.Command = "help";
  }
  else if (optsMap.count("test")) {
    opts.Command = "test";
  }
 
  if (opts.Command == "search" ||
      opts.Command == "graph" || opts.Command == "prog") {
    // determine the source of our patterns
    if (!optsMap["pattern"].empty()) {
      if (!optsMap["keywords"].empty()) {
        throw po::error("--pattern and --keywords are incompatible options");
      }

      // keywords from --pattern
      opts.Pattern = optsMap["pattern"].as<std::string>();
    }
    else {
      if (!optsMap["keywords"].empty()) {
        // keywords from --keywords
        opts.KeyFile = optsMap["keywords"].as<std::string>();
      }
      else {
        // keywords from parg
        if (pargs.empty()) {
          throw po::required_option("keywords");
        }

        opts.KeyFile = pargs.front();
        pargs.erase(pargs.begin());
      }
    }  

    opts.CaseSensitive = optsMap.count("ignore-case") == 0;
    opts.LiteralMode = optsMap.count("fixed-strings") > 0;

    if (opts.Command == "search") {
      // determine the source of our input
      if (!optsMap["input"].defaulted()) {
        // input from --input
        opts.Input = optsMap["input"].as<std::string>();
      }
      else if (!pargs.empty()) {
        // input from parg
        opts.Input = pargs.front();
        pargs.erase(pargs.begin());
      }
      else {
        // input from stdin
        opts.Input = "";
      }
    }
    
    // there should be no positional arguments unused now
    if (!pargs.empty()) {
      throw po::too_many_positional_options_error();
    }
  }
  else if (opts.Command == "test" ||
           opts.Command == "help" || opts.Command == "server") {
    // nothing else to do
  }
  else {
    throw po::invalid_option_value(opts.Command);
  }
}

