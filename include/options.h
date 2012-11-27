#pragma once

// must include <fstream> before this header, because of <iosfwd> usage

#include "basic.h"
#include "automata.h"
#include "pattern.h"

#include <iosfwd>
#include <set>
#include <string>
#include <vector>

class Options {
public:
  uint64_t DebugBegin,
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
              ServerAddr,
              ServerLog,
              ProgramFile,
              StatsFileName;

  std::vector<std::string> Inputs,
                           CmdLinePatterns,
                           KeyFiles,
                           Encodings;

  uint32_t BlockSize;

  unsigned short ServerPort;

  bool CaseInsensitive,
       LiteralMode,
       NoOutput,
       Determinize,
       PrintPath,
       Recursive,
       Binary;

  mutable std::ofstream OutputFile;

  std::ostream& openOutput() const;

  std::vector<Pattern> getKeys() const;

  bool readKeyFile(const std::string& keyFilePath, std::vector<Pattern>& keys) const;

  bool parseLine(uint32_t keyIndex, const std::string& line, std::vector<Pattern>& keys) const;
};
