#pragma once

// must include <fstream> before this header, because of <iosfwd> usage

#include "basic.h"
#include <iosfwd>

class Options {
public:
  uint64  DebugBegin,
          DebugEnd;

  std::string KeyFile,
              Command,
              Input,
              Output,
              Encoding,
              Pattern,
              ServerLog;

  unsigned int BlockSize;

  bool    CaseSensitive,
          LiteralMode,
          NoOutput,
          Determinize,
          PrintPath;

  mutable std::ofstream OutputFile;

  uint32 getEncoding() const;

  std::ostream& openOutput() const;

  std::vector< std::string > getKeys() const;
};
