#pragma once

#include <string>
#include <vector>

struct Options {
  enum Codecs {
    CODEC_NONE,
    CODEC_GZIP,
    CODEC_LZ4
  };

  std::string Command;

  std::string Input;

  std::string TarPath;

  std::string MatchSet;

  std::vector<std::string> KeyFiles;

  unsigned int NumThreads;

  Codecs Codec;
};
