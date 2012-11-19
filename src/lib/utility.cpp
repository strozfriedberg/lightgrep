/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

/*
void addKeys(const std::vector<Pattern>& keywords, bool ignoreBad, FSMThingy& f, uint32& keyIdx) {
  ParseTree tree;

  for (uint32 i = 0; i < keywords.size(); ++i, ++keyIdx) {
    try {
      parse_and_reduce(
        keywords[i].Expression,
        keywords[i].FixedString,
        keywords[i].CaseInsensitive,
        tree
      );

      f.addPattern(tree, keywords[i].Encoding.front().c_str(), keyIdx);
    }
    catch (const std::runtime_error&) {
      if (!ignoreBad) {
        throw;
      }
    }
  }
}
*/

uint32 estimateGraphSize(const std::vector<Pattern>& keywords) {
  uint32 ret = 0;
  for (const auto& p : keywords) {
    uint32 pSize = p.Expression.size();
    const std::string& enc = p.Encoding.back();
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
  uint32 fudgeFactor = ret;
  fudgeFactor >>= 2;
  ret += fudgeFactor;
  return ret;
}

/*
NFAPtr createGraph(const std::vector<Pattern>& keywords, bool determinize, bool ignoreBadParse) {

  FSMThingy f(estimateGraphSize(keywords));
  uint32 keyIdx = 0;

  addKeys(keywords, ignoreBadParse, f, keyIdx);

  for (uint32 i = 0; i < keywords.size(); ++i) {
    int32 encIdx = -1;
    std::vector<uint32> encs;

    for (const std::string& e : keywords[i].Encoding) {
      encIdx = lg_get_encoding_id(e.c_str());

      if (encIdx == -1) {
        break;
      }
      else {
        encs.push_back(encIdx);
      }
    }

//    if (encIdx != -1) {
//      keyInfo.Table.emplace_back(i, encs);
//    }
  }

  if (f.Fsm) {
    if (determinize) {
      NFAPtr dfa(new NFA(1));
      dfa->TransFac = f.Fsm->TransFac;
      f.Comp.subsetDFA(*dfa, *f.Fsm);
      f.Fsm = dfa;
    }
    f.Comp.labelGuardStates(*f.Fsm);
  }

  return f.Fsm;
}
*/

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
    for (uint32 i = 0; i < 256; ++i) {
      if (permitted[i] && std::find(ret[i].begin(), ret[i].end(), ov) == ret[i].end()) {
        ret[i].push_back(ov);
      }
    }
  }
  return ret;
}

uint32 maxOutbound(const std::vector<std::vector<NFA::VertexDescriptor>>& tranTable) {
  uint32 ret = 0;
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

void writeEdge(std::ostream& out, NFA::VertexDescriptor v, NFA::VertexDescriptor u, uint32 priority, const NFA& graph) {
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
    for (uint32 j = 0; j < graph.outDegree(head); ++j) {
      writeEdge(out, head, graph.outVertex(head, j), j, graph);
    }
  }

  out << "}" << std::endl;
}
