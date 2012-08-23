#pragma once

#include "basic.h"

#include <string>
#include <vector>

#include "automata.h"
#include "nfaoptimizer.h"
#include "nfabuilder.h"
#include "vm_interface.h"
#include "patterninfo.h"

struct SearchInfo {};

uint32 estimateGraphSize(const std::vector<Pattern>& keywords);

NFAPtr createGraph(const std::vector<Pattern>& keywords,
                   bool determinize = true,
                   bool ignoreBadParse = false);

class Visitor {
public:
  virtual ~Visitor() {}

  virtual void discoverVertex(NFA::VertexDescriptor,
                              const NFA&) const {}

  virtual void treeEdge(NFA::VertexDescriptor,
                        NFA::VertexDescriptor,
                        const NFA&) const {}
};

void bfs(const NFA& graph, NFA::VertexDescriptor start, Visitor& visitor);

ProgramPtr createProgram(const NFA& graph);

ByteSet firstBytes(const NFA& graph);
void nextBytes(ByteSet& set, NFA::VertexDescriptor v, const NFA& graph);

std::shared_ptr<VmInterface> initVM(const std::vector<Pattern>& keywords, SearchInfo& info);

std::vector<std::vector<NFA::VertexDescriptor>> pivotStates(NFA::VertexDescriptor source, const NFA& graph);

uint32 maxOutbound(const std::vector<std::vector<NFA::VertexDescriptor>>& tranTable);

void writeGraphviz(std::ostream& out, const NFA& graph);
