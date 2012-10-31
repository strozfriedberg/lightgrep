#include <iostream>
#include <boost/program_options.hpp>
#include <scope/testrunner.h>

namespace po = boost::program_options;

int main(int argc, char** argv) {
  po::options_description desc("Allowed Options");

  desc.add_options()
    ("help,h", "print help")
    ("test", "run unit tests (same as test command)")
    ("debug", "print debuging info")
    ;

  po::options_description opts;
  opts.add(desc);

  po::variables_map optsMap;
  po::store(po::command_line_parser(argc, argv).options(opts).run(), optsMap);
  po::notify(optsMap);

  try {
    if (optsMap.count("help")) {
      std::cerr << desc << std::endl;
    }
    else if (optsMap.count("test")) {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
    else {
      // this should be impossible
      std::cerr << "Unrecognized command. Use --help for list of options."
                << std::endl;
      return 1;
    }
  }
  catch (const std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n\n";
    return 1;
  }
  return 0;
}
