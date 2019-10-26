#pragma once

#include <string>
#include <vector>

struct Options {
  std::string Command;

  std::string Input;

  std::string TarPath;

  std::vector<std::string> KeyFiles;

  unsigned int NumThreads;
};
