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
#include "nfabuilder.h"
#include "nfaoptimizer.h"
#include "encoders/encoderfactory.h"

#include <memory>

class FSMThingy {
public:
  FSMThingy(uint32_t sizeHint);

  EncoderFactory EncFac;
  NFABuilder Nfab;
  NFAOptimizer Comp;
  NFAPtr Fsm;

  void addPattern(const ParseTree& tree, const char* chain, uint32_t label);

  void finalizeGraph(uint32_t determinizeDepth);
};
