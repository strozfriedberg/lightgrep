#include <scope/testrunner.h>

#include <iostream>

#include "llama.h"

int main(int argc, const char *const argv[]) {
  if (1 == argc) {
    std::cout << "Use 'llama --help' for command-line option help.\nRunning unit tests...\n";
    return scope::DefaultRun(std::cout, argc, const_cast<char**>(argv)) ? 0: 1;
  }
  else {
    Llama app;
    return app.run(argc, argv);
  }
}
