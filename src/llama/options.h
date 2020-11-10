#pragma once

#include <string>
#include <vector>

#include "codec.h"

struct Options {
  std::string Command;
  std::string Input;
  std::string Output;
  std::string MatchSet;
  std::vector<std::string> KeyFiles;
  unsigned int NumThreads;
  Codec OutputCodec;
};
