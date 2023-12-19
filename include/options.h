#pragma once

#include "basic.h"
#include "automata.h"

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

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
    ANALYZE,
    SHOW_VERSION,
    SHOW_HELP,
    LIST_ENCODINGS,
    BOGUS
  } Command;

  std::string Output,
              ProgramFile,
              GroupSeparator,
              HistogramFile;

  std::vector<std::string> Inputs,
                           InputLists,
                           CmdLinePatterns,
                           KeyFiles,
                           Encodings;

  uint32_t BlockSize,
           DeterminizeDepth;

  int32_t BeforeContext = -1,
          AfterContext = -1;

  bool CaseInsensitive,
       LiteralMode,
       UnicodeMode,
       NoOutput,
       PrintPath,
       Recursive,
       Binary,
       MemoryMapped,
       Verbose;

  mutable std::ofstream OutputFile;

  std::ostream& openOutput() const;

  std::vector<std::pair<std::string, std::string>> getPatternLines() const;

  void validateAndPopulateOptions(const po::variables_map& optsMap, std::vector<std::string>& pargs);

private:
  void validateAndPopulateKeyFiles(const po::variables_map& optsMap, std::vector<std::string>& pargs);
  void populateContextOptions(const po::variables_map& optsMap, std::vector<std::string>& pargs);
  void validateAndPopulateSearchOptions(const po::variables_map& optsMap, std::vector<std::string>& pargs);
  void populateSampleOptions(const po::variables_map& optsMap, std::vector<std::string>& pargs);
};
