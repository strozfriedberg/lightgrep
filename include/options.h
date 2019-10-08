#pragma once

#include "basic.h"
#include "automata.h"

#include <fstream>
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
    SHOW_VERSION,
    SHOW_HELP,
    LIST_ENCODINGS,
    BOGUS
  } Command;

  std::string Output,
              ProgramFile,
              GroupSeparator;

  std::vector<std::string> Inputs,
                           InputLists,
                           CmdLinePatterns,
                           KeyFiles,
                           Encodings;

  uint32_t BlockSize;

  int32_t BeforeContext = -1,
          AfterContext = -1;

  bool CaseInsensitive,
       LiteralMode,
       AsciiMode,
       NoOutput,
       Determinize,
       PrintPath,
       Recursive,
       Binary,
       MemoryMapped;

  mutable std::ofstream OutputFile;

  std::ostream& openOutput() const;

  std::vector<std::pair<std::string,std::string>> getPatternLines() const;
};
