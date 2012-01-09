#pragma once

// must include <fstream> before this header, because of <iosfwd> usage

#include "basic.h"
#include "graph.h"

#include <iosfwd>
#include <set>
#include <string>

class Options {
public:
  uint64 DebugBegin,
         DebugEnd;

  std::set<std::string>::size_type SampleLimit;
  std::multiset<Graph::vertex>::size_type LoopLimit;

  std::string KeyFile,
              Command,
              Input,
              Output,
              Encoding,
              Pattern,
              ServerLog;

  unsigned int BlockSize;

  bool CaseSensitive,
       LiteralMode,
       NoOutput,
       Determinize,
       PrintPath,
       Recursive;

  mutable std::ofstream OutputFile;

  uint32 getEncoding() const;

  std::ostream& openOutput() const;

  std::vector< std::string > getKeys() const;
};
