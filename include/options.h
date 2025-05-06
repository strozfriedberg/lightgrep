/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
 
 #pragma once

#include "basic.h"
#include "automata.h"

#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "boost_program_options.h"
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

  bool CaseInsensitive = false,
       LiteralMode = false,
       UnicodeMode = false,
       NoOutput = false,
       PrintPath = false,
       Recursive = false,
       Binary = false,
       MemoryMapped = false,
       Verbose = false;

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
