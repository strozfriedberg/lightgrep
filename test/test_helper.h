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

#include "automata.h"
#include "fwd_pointers.h"
#include "pattern.h"

#include <initializer_list>
#include <vector>

void edge(NFA::VertexDescriptor source, NFA::VertexDescriptor target, NFA& fsm, Transition* trans);

bool edgeExists(const NFA& g, const NFA::VertexDescriptor source, const NFA::VertexDescriptor target);

void ASSERT_SUPERGRAPH(const NFA& a, const NFA& b);

void ASSERT_EQUAL_GRAPHS(const NFA& a, const NFA& b);

void ASSERT_EQUAL_LABELS(const NFA& a, const NFA& b);

void ASSERT_EQUAL_MATCHES(const NFA& a, const NFA& b);

NFAPtr createGraph(const std::vector<Pattern>& pats, bool determinize);

