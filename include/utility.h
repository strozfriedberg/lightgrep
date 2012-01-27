#pragma once

#include "basic.h"

#include <string>
#include <vector>

#include "automata.h"
#include "compiler.h"
#include "nfabuilder.h"
#include "vm_interface.h"

struct SearchInfo {};

enum Encodings {
  CP_ASCII = 1,
  CP_UCS16 = 2
};

NFAPtr createGraph(const std::vector<std::string>& keywords,
                    uint32 enc = CP_ASCII, 
                    bool caseSensitive = true, 
                    bool litMode = false, 
                    bool determinize = true,
                    bool ignoreBadParse = false);

class Visitor {
public:
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

boost::shared_ptr<VmInterface> initVM(const std::vector<std::string>& keywords, SearchInfo& info);

std::vector< std::vector< NFA::VertexDescriptor > > pivotStates(NFA::VertexDescriptor source, const NFA& graph);

uint32 maxOutbound(const std::vector< std::vector< NFA::VertexDescriptor > >& tranTable);

void writeGraphviz(std::ostream& out, const NFA& graph);
