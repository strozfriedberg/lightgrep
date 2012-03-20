#pragma once

// must include <fstream> before this header, because of <iosfwd> usage

#include "automata.h"
#include "basic.h"
#include "patterninfo.h"

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

  enum CommandTypes {
    SEARCH,
    GRAPH,
    PROGRAM,
    SAMPLES,
    VALIDATE,
    SERVER,
    HELP,
    ENCODINGS,
    BOGUS
  } Command;

  std::string Input,
              Output,
              Encoding,
              ServerLog,
              ProgramFile;

  std::vector<std::string> Inputs,
                           CmdLinePatterns,
                           KeyFiles;

  uint32 BlockSize;

  bool CaseInsensitive,
       LiteralMode,
       NoOutput,
       Determinize,
       PrintPath,
       Recursive,
       Binary;

  mutable std::ofstream OutputFile;

  std::ostream& openOutput() const;

  PatternInfo getKeys() const;

  bool readKeyFile(const std::string& keyFilePath, PatternInfo& keys) const;
  bool parseLine(uint32 keyIndex, const std::string& line, PatternInfo& keys) const;
};
