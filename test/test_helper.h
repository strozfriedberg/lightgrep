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

#include "automata.h"
#include "fwd_pointers.h"
#include "pattern.h"

#include <deque>
#include <initializer_list>
#include <stack>
#include <vector>

void edge(NFA::VertexDescriptor source, NFA::VertexDescriptor target, NFA& fsm, Transition* trans);

bool edgeExists(const NFA& g, const NFA::VertexDescriptor source, const NFA::VertexDescriptor target);

void ASSERT_SUPERGRAPH(const NFA& a, const NFA& b);

void ASSERT_EQUAL_GRAPHS(const NFA& a, const NFA& b);

void ASSERT_EQUAL_LABELS(const NFA& a, const NFA& b);

void ASSERT_EQUAL_MATCHES(const NFA& a, const NFA& b);

NFAPtr createGraph(const std::vector<Pattern>& pats, bool determinize);

template <class T, class C = std::deque<T>>
std::vector<T> unstack(std::stack<T, C>& s) {
  std::vector<T> v;
  while (!s.empty()) {
    v.push_back(s.top());
    s.pop();
  }
  return v;
}
