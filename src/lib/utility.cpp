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

#include "utility.h"

#include <algorithm>
#include <set>

std::pair<uint32_t,std::bitset<256*256>> bestPair(const NFA& graph) {
  std::set<std::pair<uint32_t,NFA::VertexDescriptor>> next;
  next.emplace(0, 0);

  std::vector<std::bitset<256*256>> b;

  uint32_t lmin = std::numeric_limits<uint32_t>::max()-1;

  uint32_t depth;
  NFA::VertexDescriptor h;

  while (!next.empty()) {
    std::tie(depth, h) = *next.begin();
    next.erase(next.begin());

    // lmin + 1 still gets us one transition followed by any byte;
    // > lmin + 1 would have to accept everytyhing, so is useless
    if (depth > lmin + 1) {
      break;
    }

    if (graph[h].IsMatch && depth < lmin) {
      lmin = depth;
    }

    // put successors in the queue if they're at lmin + 1 or less
    if (depth < lmin + 1) {
      for (const NFA::VertexDescriptor t : graph.outVertices(h)) {
        next.emplace(depth+1, t);
      }
    }

    // ensure that b[depth] exists
    if (b.size() <= depth) {
      b.resize(depth+1);
    }
  
    // we use this pointer for getting sub-bitsets 
    uint8_t* const bb = reinterpret_cast<uint8_t* const>(&b[depth]);
 
    for (const NFA::VertexDescriptor t0 : graph.outVertices(h)) {
      ByteSet first;
      graph[t0].Trans->orBytes(first);

      if (graph[t0].IsMatch) {
        // match; record each first byte followed by any byte
        for (uint32_t s = 0; s < 256; ++s) {
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
