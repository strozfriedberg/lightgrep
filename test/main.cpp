#include <iostream>

#include <scope/testrunner.h>

int main(int argc, char** argv) {
  return scope::DefaultRun(std::cout, argc, argv) ? 0: 1;
}
