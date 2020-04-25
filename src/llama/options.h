#pragma once

#include <string>
#include <vector>

struct Options {
  enum Codecs {
    CODEC_NONE,
    CODEC_GZIP,
    CODEC_LZ4,
    CODEC_LZMA,
    CODEC_BZIP2,
    CODEC_LZOP,
    CODEC_XZ
  };

  std::string Command;

  std::string Input;

  std::string TarPath;

  std::string MatchSet;

  std::vector<std::string> KeyFiles;

  unsigned int NumThreads;

  Codecs Codec;
};
