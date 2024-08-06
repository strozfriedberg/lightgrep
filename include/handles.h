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

#include <memory>

#include "lightgrep/api.h"
#include "lightgrep/util.h"

#include "basic.h"
#include "fsmthingy.h"
#include "fwd_pointers.h"
#include "parsetree.h"
#include "pattern_map.h"
#include "vm_interface.h"
#include "pattern.h"
#include "decoders/decoderfactory.h"

struct PatternHandle {
  Pattern   Pat;
  ParseTree Tree;
};

struct PatternMapHandle {
  std::unique_ptr<PatternMap> Impl;
};

struct FSMHandle {
  std::unique_ptr<FSMThingy> Impl;
  std::shared_ptr<PatternMap> PMap;
};

struct ProgramHandle {
  ProgramPtr Prog;
  std::shared_ptr<PatternMap> PMap;
};

struct ContextHandle {
  std::shared_ptr<VmInterface> Impl;
};

struct DecoderHandle {
  DecoderFactory Factory;
};
