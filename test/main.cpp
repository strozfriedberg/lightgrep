#include <iostream>

#include <scope/testrunner.h>

int main(int argc, char** argv) {
  if (argc > 1) {
    std::string first(argv[1]);
    if (first == "test") {
      return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
    }
  }
  return 0;
}
