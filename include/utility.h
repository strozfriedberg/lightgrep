/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
