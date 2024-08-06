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

#include "utility.h"

#include <algorithm>
#include <set>

std::pair<uint32_t,std::bitset<256*256>> bestPair(const NFA& graph) {
  // pairs are (depth, vertex); we're using next as a min heap
  std::set<std::pair<uint32_t,NFA::VertexDescriptor>> next;
  next.emplace(0, 0);

  // b[i] stores flags for which byte pairs starting at offset i admit matches
  std::vector<std::bitset<256*256>> b;

  // lmin is the least match length seen so far
  uint32_t lmin = std::numeric_limits<uint32_t>::max()-1;

  uint32_t depth;
  NFA::VertexDescriptor h;  // head

  while (!next.empty()) {
    // pop the top of the min heap
    std::tie(depth, h) = *next.begin();
    next.erase(next.begin());

    // lmin + 1 still gets us one transition followed by any byte;
    // > lmin + 1 would have to accept everytyhing, so is useless
    if (depth > lmin + 1) {
      break;
    }

    // check if this vertex lowers lmin
    if (graph[h].IsMatch && depth < lmin) {
      // this vertex has the least match length we've seen so far
      lmin = depth;
    }

    // put successors in the heap if they're at lmin + 1 or less
    if (depth < lmin + 1) {
      for (const NFA::VertexDescriptor t : graph.outVertices(h)) {
        next.emplace(depth + 1, t);
      }
    }

    // ensure that b[depth] exists
    if (b.size() <= depth) {
      b.resize(depth + 1);
    }

    // we use this pointer for getting sub-bitsets; bb = bytes bits
    uint8_t* const bb = reinterpret_cast<uint8_t* const>(&b[depth]);

    for (const NFA::VertexDescriptor t0 : graph.outVertices(h)) {
      ByteSet first;
      graph[t0].Trans->orBytes(first);

      if (graph[t0].IsMatch) {
        // match; record each first byte followed by any byte
        for (uint32_t s = 0; s < 256; ++s) {
          // first is a std::bitset<256>, so is 256 bits = 32 bytes long,
          // and bb is a byte pointer into a std::bitset<256*256>, which
          // has the same layout as an array of 256 std::bitset<256>s.
          // Thus if we want to OR first into each of 256-bit chunk of bb,
          // 32 bytes is the correct stride for advancing to the next index
          // into which to do that.
          *reinterpret_cast<std::bitset<256>*>(bb + (s << 5)) |= first;
        }
      }
      else {
        // no match; record each first byte followed by each second byte
        for (const NFA::VertexDescriptor t1 : graph.outVertices(t0)) {
          ByteSet second;
          graph[t1].Trans->orBytes(second);

          for (uint32_t s = 0; s < 256; ++s) {
            if (second.test(s)) {
              *reinterpret_cast<std::bitset<256>*>(bb + (s << 5)) |= first;
            }
          }
        }
      }
    }
  }

  if (b.size() < lmin) {
    // Don't go beyond the end of the vector. This can happen with some
    // tests where we have no match states.
    lmin = b.size();
  }
  else if (lmin < b.size()) {
    // Don't start pairs after offset lmin-1, as [lmin,lmin+2) is
    // guaranteed to be informationless.
    b.resize(lmin);
  }

  // Return the offset and bitset for the best two-byte window
  const auto i = std::min_element(b.begin(), b.end(),
    [](const std::bitset<256*256>& l, const std::bitset<256*256>& r) {
      return l.count() < r.count();
    }
  );

  return {i-b.begin(), *i};
}

std::vector<std::vector<NFA::VertexDescriptor>> pivotStates(NFA::VertexDescriptor source, const NFA& graph) {
  std::vector<std::vector<NFA::VertexDescriptor>> ret(256);
  ByteSet permitted;

  for (const NFA::VertexDescriptor ov : graph.outVertices(source)) {
    graph[ov].Trans->getBytes(permitted);
    for (uint32_t i = 0; i < 256; ++i) {
      if (permitted[i] && std::find(ret[i].begin(), ret[i].end(), ov) == ret[i].end()) {
        ret[i].push_back(ov);
      }
    }
  }
  return ret;
}

uint32_t maxOutbound(const std::vector<std::vector<NFA::VertexDescriptor>>& tranTable) {
  return std::max_element(tranTable.begin(), tranTable.end(),
    [](const std::vector<NFA::VertexDescriptor>& l,
       const std::vector<NFA::VertexDescriptor>& r) {
      return l.size() < r.size();
    }
  )->size();
}

void writeVertex(std::ostream& out, NFA::VertexDescriptor v, const NFA& graph) {
  out << "  " << v << " [label=\"" << v << "\"";

  if (graph[v].IsMatch) {
    // double ring for match states
    out << ", peripheries=2";
  }

  out << "];\n";
}

std::string escape(char c, const std::string& text) {
  // escape a character in the given string
  std::string repl(text);
  for (std::string::size_type next = repl.find(c);
       next != std::string::npos; next = repl.find(c, next)) {
    repl.insert(next, 1, '\\');
    next += 2;
  }
  return repl;
}

void writeEdge(std::ostream& out, NFA::VertexDescriptor v, NFA::VertexDescriptor u, uint32_t priority, const NFA& graph) {
  const std::string esclabel = escape('"', escape('\\', graph[u].label()));

  out << "  " << v << " -> " << u << " ["
      << "label=\"" << esclabel << "\", "
      << "taillabel=\"" << priority << "\"];\n";
}

void writeGraphviz(std::ostream& out, const NFA& graph) {
  out << "digraph G {\n  rankdir=LR;\n  ranksep=equally;\n  node [shape=\"circle\"];" << std::endl;

  for (const NFA::VertexDescriptor v : graph.vertices()) {
    writeVertex(out, v, graph);
  }

  for (const NFA::VertexDescriptor head : graph.vertices()) {
    for (uint32_t j = 0; j < graph.outDegree(head); ++j) {
      writeEdge(out, head, graph.outVertex(head, j), j, graph);
    }
  }

  out << "}" << std::endl;
}
