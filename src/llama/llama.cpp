#include "llama.h"

#include <functional>
#include <iostream>
#include <unordered_map>

int Llama::run(int argc, const char* const argv[]) {
  std::unordered_map<std::string, std::function<void(const Options&)>> commands{
    {"help", [&](const Options&) { CliParser.printHelp(std::cout); }},
    {"version", [&](const Options&) { CliParser.printVersion(std::cout); }}
  };
  auto opts = CliParser.parse(argc, argv);
  if (opts && commands.find(opts->Command) != commands.end()) {
    commands[opts->Command](*opts);
  }
  return 0;
}
