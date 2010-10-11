#pragma once

#include <fstream>

struct Options {
  uint64  DebugBegin,
          DebugEnd;
          
  std::string KeyFile,
              Command,
              Input,
              Output,
              Encoding;
  bool    CaseSensitive;

  mutable std::ofstream OutputFile;

  uint32 getEncoding() const {
    uint32 value = 0;
    if (Encoding == "ucs16") {
      value |= CP_UCS16;
    }
    else if (Encoding == "both") {
      value |= CP_UCS16;
      value |= CP_ASCII;
    }
    else if (Encoding == "ascii") {
      value |= CP_ASCII;
    }
    return value;
  }

  std::ostream& openOutput() const {
    if (Output == "-") {
      return std::cout;
    }
    else {
      OutputFile.clear();
      OutputFile.open(Output.c_str(), std::ios::out);
      if (!OutputFile) {
        THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file " << Output);
      }
      return OutputFile;
    }
  }
};
