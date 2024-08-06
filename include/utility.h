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

#include <string>
#include <vector>

#include "automata.h"
#include "pattern.h"

struct SearchInfo {};

template <typename T>
uint32_t estimateGraphSize(const std::vector<T>& keywords) {
  uint32_t ret = 0;
  for (const auto& p : keywords) {
    uint32_t pSize = p.Expression.size();
    const std::string& enc = p.Encoding;
// FIXME: Shouldn't we use something from the Encoders for this?
    if (enc == "UTF-16LE" || enc == "UTF-16BE") {
      pSize <<= 1;
    }
    else if (enc == "UTF-8") {
      pSize *= 3;
      pSize >>= 1;
    }
    else if (enc == "UTF-32LE" || enc == "UTF-32BE") {
      pSize <<= 2;
    }
    ret += pSize;
  }
  uint32_t fudgeFactor = ret;
  fudgeFactor >>= 2;
  ret += fudgeFactor;
  return ret;
}

std::pair<uint32_t,std::bitset<256*256>> bestPair(const NFA& graph);

std::vector<std::vector<NFA::VertexDescriptor>> pivotStates(NFA::VertexDescriptor source, const NFA& graph);

uint32_t maxOutbound(const std::vector<std::vector<NFA::VertexDescriptor>>& tranTable);

void writeGraphviz(std::ostream& out, const NFA& graph);
