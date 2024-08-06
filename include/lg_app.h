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
 
 #include <iosfwd>
#include <memory>
#include <tuple>

#include "handles.h"
#include "errors.h"

class Options;

class LgAppCollection {
public:
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm;
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog;
  std::unique_ptr<Errors> errors;

  LgAppCollection(
    std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm,
    std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog,
    std::unique_ptr<Errors> errors
  ) : fsm(std::move(fsm)), prog(std::move(prog)), errors(std::move(errors)) {};

    LG_Error* getError() { return errors.get()->Err; }
};

LgAppCollection parsePatterns(const Options& opts);

void writeProgram(const Options& opts, std::ostream& out);

