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

#include "lg_app.h"

#include "options.h"
#include "program.h"
#include <iostream>

namespace {
  // the lifetime of the input vec must exceed that of the returned array
  // because loop creates shallow copies of elements of vec
  std::unique_ptr<const char*[]> c_str_arr(const std::vector<std::string>& vec) {
    const size_t size = vec.size();
    std::unique_ptr<const char*[]> arr(new const char*[size]);
    for (uint32_t i = 0; i < size; ++i) {
        arr[i] = vec[i].c_str();
    }
    return arr;
  }

  LG_KeyOptions patOpts(const Options& opts) {
    return { opts.LiteralMode, opts.CaseInsensitive, opts.UnicodeMode };
  }

  LG_ProgramOptions progOpts(const Options& opts) {
    return { opts.DeterminizeDepth };
  }
}
  
LgAppCollection parsePatterns(const Options& opts)
{
  // read the patterns and parse them

  const std::vector<std::pair<std::string, std::string>>& patLines(opts.getPatternLines());
  const std::vector<std::string>& defaultEncodings(opts.Encodings);
  const LG_KeyOptions& defaultKOpts(patOpts(opts));
  const LG_ProgramOptions& defaultProgOpts(progOpts(opts));

  // FIXME: estimate NFA size here?
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0, 0),
    lg_destroy_fsm
  );

  if (!fsm) {
    throw std::runtime_error("failed to create fsm");
  }

  // set default encoding(s) of patterns which have none specified
  const std::unique_ptr<const char*[]> defEncs(c_str_arr(defaultEncodings));

  std::unique_ptr<Errors> errors(new Errors());

  for (const std::pair<std::string, std::string>& pf : patLines) {
    // parse a complete pattern file
    LG_Error* local_err = nullptr;

    lg_add_pattern_list(
      fsm.get(),
      pf.second.c_str(), pf.first.c_str(),
      defEncs.get(), defaultEncodings.size(), &defaultKOpts, &local_err
    );

    if (local_err) {
      errors->extend(local_err);
    }
  }

  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog(
    lg_create_program(fsm.get(), &defaultProgOpts),
    lg_destroy_program
  );

  if (prog && opts.Verbose) {
    std::cerr << fsm->Impl->Fsm->verticesSize() << " vertices\n"
              << prog->Prog->size() << " instructions\n";
  }

  return LgAppCollection(std::move(fsm), std::move(prog), std::move(errors));
}

void writeProgram(const Options& opts, std::ostream& out) {
  // get the patterns and parse them

  LgAppCollection col = parsePatterns(opts);
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog(std::move(col.prog));

  const bool printFilename = opts.CmdLinePatterns.empty()
                          && opts.KeyFiles.size() > 1;

  col.errors->outputErrors(std::cerr, printFilename);

  if (!prog) {
    throw std::runtime_error("failed to create program");
  }

  // break on through the C API to print the program
  ProgramPtr p(prog->Prog);
  if (opts.Verbose) {
    std::cerr << p->size() << " program size in bytes" << std::endl;
  }

  if (opts.Binary) {
    std::string buf(lg_program_size(prog.get()), '\0');
    lg_write_program(prog.get(), buf.data());
    out.write(buf.data(), buf.size());
  }
  else {
    out << *p << std::endl;
  }
}