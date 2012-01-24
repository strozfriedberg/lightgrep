#pragma once

#include "basic.h"

#include <string>
#include <vector>

#include "compiler.h"
#include "graph.h"
#include "nfabuilder.h"
#include "vm_interface.h"
#include "patterninfo.h"

struct SearchInfo {};

uint32 totalCharacters(const std::vector<Pattern>& keywords);

GraphPtr createGraph(const std::vector<Pattern>& keywords,
                    bool determinize = true,
                    bool ignoreBadParse = false);

class Visitor {
public:
  virtual void discoverVertex(Graph::vertex,
                              const Graph&) const {}

  virtual void treeEdge(Graph::vertex,
                        Graph::vertex,
                        const Graph&) const {}
};

void bfs(const Graph& graph, Graph::vertex start, Visitor& visitor);

ProgramPtr createProgram(const Graph& graph);

ByteSet firstBytes(const Graph& graph);
void nextBytes(ByteSet& set, Graph::vertex v, const Graph& graph);

boost::shared_ptr<VmInterface> initVM(const std::vector<Pattern>& keywords, SearchInfo& info);

std::vector< std::vector< Graph::vertex > > pivotStates(Graph::vertex source, const Graph& graph);

uint32 maxOutbound(const std::vector< std::vector< Graph::vertex > >& tranTable);

void writeGraphviz(std::ostream& out, const Graph& graph);
