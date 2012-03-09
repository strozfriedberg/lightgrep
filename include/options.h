#pragma once

// must include <fstream> before this header, because of <iosfwd> usage

#include "automata.h"
#include "basic.h"
#include "pattern.h"

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

class Options {
public:
  uint64 DebugBegin,
         DebugEnd;

  std::set<std::string>::size_type SampleLimit;
  std::multiset<NFA::VertexDescriptor>::size_type LoopLimit;

  std::string Command,
              Input,
              Output,
              Encoding,
              ServerLog;

  std::vector<std::string> Inputs,
                           CmdLinePatterns,
                           KeyFiles;

  uint32 BlockSize;

  bool CaseInsensitive,
       LiteralMode,
       NoOutput,
       Determinize,
       PrintPath,
       Recursive;

  mutable std::ofstream OutputFile;

  std::ostream& openOutput() const;

  std::vector<Pattern> getKeys() const;

  bool readKeyFile(const std::string& keyFilePath, std::vector<Pattern>& keys) const;
  bool parseLine(uint32 keyIndex, const std::string& line, std::vector<Pattern>& keys) const;
};
