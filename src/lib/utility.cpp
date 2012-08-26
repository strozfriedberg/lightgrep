#include "codegen.h"
#include "concrete_encoders.h"
#include "nfaoptimizer.h"
#include "encodings.h"
#include "nfabuilder.h"
#include "parser.h"
#include "rewriter.h"
#include "compiler.h"
#include "program.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <queue>
#include <sstream>
#include <stdexcept>

#include <boost/graph/graphviz.hpp>

void addKeys(const std::vector<Pattern>& keywords, bool ignoreBad, Parser& p, uint32& keyIdx) {
  for (uint32 i = 0; i < keywords.size(); ++i, ++keyIdx) {
    try {
      p.addPattern(keywords[i], keyIdx);
    }
    catch (const std::runtime_error&) {
      if (!ignoreBad) {
        throw;
      }
    }
  }
}

uint32 estimateGraphSize(const std::vector<Pattern>& keywords) {
  uint32 ret = 0;
  for (auto& p : keywords) {
    uint32 pSize = p.Expression.size();
    if (p.Encoding == "UTF-16LE" || p.Encoding == "UTF-16BE") {
      pSize <<= 1;
    }
    else if (p.Encoding == "UTF-8") {
      pSize *= 3;
      pSize >>= 1;
    }
    else if (p.Encoding == "UTF-32LE" || p.Encoding == "UTF-32BE") {
      pSize <<= 2;
    }
    ret += pSize;
  }
  uint32 fudgeFactor = ret;
  fudgeFactor >>= 2;
  ret += fudgeFactor;
  return ret;
}

// FIXME: this duplicates a lot of parsePatterns() in main.cpp
void addKeys(PatternInfo& keyInfo, bool ignoreBad, Parser& p, uint32& keyIdx) {
  addKeys(keyInfo.Patterns, ignoreBad, p, keyIdx);

  for (uint32 i = 0; i < keyInfo.Patterns.size(); ++i) {
    int32 encIdx = lg_get_encoding_id(keyInfo.Patterns[i].Encoding.c_str());

    if (encIdx == -1) {
      continue;
    }

    keyInfo.Table.emplace_back(i, encIdx);
  }
}

NFAPtr createGraph(PatternInfo& keyInfo, bool determinize, bool ignoreBadParse) {
  Parser p(estimateGraphSize(keyInfo.Patterns));
  uint32 keyIdx = 0;

  addKeys(keyInfo, ignoreBadParse, p, keyIdx);
  if (p.Fsm) {

    if (determinize) {
      NFAPtr dfa(new NFA(1));
      dfa->TransFac = p.Fsm->TransFac;
      p.Comp.subsetDFA(*dfa, *p.Fsm);
      p.Fsm = dfa;
    }
    p.Comp.labelGuardStates(*p.Fsm);
  }
  return p.Fsm;
}

NFAPtr createGraph(const std::vector<Pattern>& keywords, bool determinize, bool ignoreBadParse) {
  PatternInfo keyInfo;
  keyInfo.Patterns = keywords;
  return createGraph(keyInfo, determinize, ignoreBadParse);
}

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

std::shared_ptr<VmInterface> initVM(const std::vector<Pattern>& keywords, SearchInfo&) {
  std::shared_ptr<VmInterface> vm = VmInterface::create();
  NFAPtr fsm = createGraph(keywords);
  ProgramPtr prog = Compiler::createProgram(*fsm);
  prog->First = firstBytes(*fsm);
  vm->init(prog);
  return vm;
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
