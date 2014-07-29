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
#include <cctype>
#include <functional>
#include <queue>

#include <boost/graph/graphviz.hpp>

void bfs(const NFA& graph, NFA::VertexDescriptor start, Visitor& visitor) {
  std::vector<bool> seen(graph.verticesSize());
  std::queue<NFA::VertexDescriptor> next;

  visitor.discoverVertex(start, graph);
  next.push(start);
  seen[start] = true;

  while (!next.empty()) {
    const NFA::VertexDescriptor h = next.front();
    next.pop();

    for (const NFA::VertexDescriptor t : graph.outVertices(h)) {
      if (!seen[t]) {
        // One might think that we discover a vertex at the tail of an
        // edge first, but one would be wrong...
        visitor.treeEdge(h, t, graph);
        visitor.discoverVertex(t, graph);
        next.push(t);
        seen[t] = true;
      }
    }
  }
}

std::pair<uint32_t,std::bitset<256*256>> bestPair(const NFA& graph) {
  std::queue<std::pair<uint32_t,NFA::VertexDescriptor>> next;
  next.push({0, 0});

  std::vector<std::bitset<256*256>> b;

  uint32_t lmin = std::numeric_limits<uint32_t>::max()-1;

  uint32_t depth;
  NFA::VertexDescriptor h;

  while (!next.empty()) {
    std::tie(depth, h) = next.front();
    next.pop();

    // lmin + 1 still gets us one transition followed by any byte;
    // > lmin + 1 would have to accept everytyhing, so is useless
    if (depth > lmin + 1) {
      continue;
    }
    
    if (graph[h].IsMatch && depth < lmin) {
      lmin = depth;
    }

    // put successors in the queue if they're at lmin + 1 or less
    if (depth < lmin + 1) {
      for (const NFA::VertexDescriptor t : graph.outVertices(h)) {
        next.push({depth+1, t});
      }
    }

    // ensure that b[depth] exists
    if (b.size() <= depth) {
      b.resize(depth+1);
    }
    
    for (const NFA::VertexDescriptor t0 : graph.outVertices(h)) {
      ByteSet first;
      graph[t0].Trans->orBytes(first);

      if (graph[t0].IsMatch) {
        // match; record each first byte followed by any byte
        for (uint32_t s = 0; s < 256; ++s) {
          for (uint32_t f = 0; f < 256; ++f) {
            if (first.test(f)) {
              b[depth].set(f | (s << 8));
            }
          }
        }
      }
      else {
        // no match; record each first byte followed by each second byte
        for (const NFA::VertexDescriptor t1 : graph.outVertices(t0)) {
          ByteSet second;
          graph[t1].Trans->orBytes(second);

          for (uint32_t s = 0; s < 256; ++s) {
            if (second.test(s)) {
              for (uint32_t f = 0; f < 256; ++f) {
                if (first.test(f)) {
                  b[depth].set(f | (s << 8));
                }
              }
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

  for (uint32_t i = 0; i < lmin; ++i) {
    std::cerr << i << ": " << b[i].count() << '\n';
  }
  std::cerr << std::endl;

  // Return the offset and bitset for the best two-byte window
  const auto i = std::min_element(b.begin(), b.end(),
    [](const std::bitset<256*256>& l, const std::bitset<256*256>& r) {
      return l.count() < r.count();
    }
  );

  return {i-b.begin(), *i};
}

std::pair<uint32_t,ByteSet> bestFirst(const NFA& graph, NFA::VertexDescriptor start, uint32_t maxdepth) {
  std::queue<std::pair<uint32_t,NFA::VertexDescriptor>> next;
  next.push({0, start});

  std::vector<ByteSet> b(maxdepth);

  uint32_t depth;
  NFA::VertexDescriptor h;

  while (!next.empty()) {
    std::tie(depth, h) = next.front();
    next.pop();

    if (depth >= maxdepth) {
      continue;
    }

    nextBytes(b[depth], h, graph);

    if (graph[h].IsMatch) {
      maxdepth = depth;
      b.resize(maxdepth);
    }
    else if (depth < maxdepth) {
      for (const NFA::VertexDescriptor t : graph.outVertices(h)) {
        next.push({depth+1, t});
      }
    }
  }

  for (uint32_t i = 0; i < b.size(); ++i) {
    std::cerr << i << ": " << b[i].count() << '\n';
  }
  std::cerr << std::endl;

  const auto i = std::min_element(b.begin(), b.end(), [](const ByteSet& l, const ByteSet& r) { return l.count() < r.count(); });
  return {i-b.begin(), *i};
}

void nextBytes(ByteSet& bset, NFA::VertexDescriptor head, const NFA& graph) {
  for (const NFA::VertexDescriptor tail : graph.outVertices(head)) {
    graph[tail].Trans->orBytes(bset);
  }
}

ByteSet firstBytes(const NFA& graph) {
  ByteSet ret;
  ret.reset();
  nextBytes(ret, 0, graph);
  return ret;
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
  uint32_t ret = 0;
  for (const std::vector<NFA::VertexDescriptor>& v : tranTable) {
    ret = v.size() > ret ? v.size() : ret;
  }
  return ret;
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
