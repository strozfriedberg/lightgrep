#include "graph.h"

typedef Graph::vertex vertex;

Graph::vertex Graph::_adjacent(const AdjacentList& l, size_t i) const {
  switch (l.Flags) {
  case ZERO:
  case ONE:
    return l.What;
  default:
    return AdjLists[l.What][i];
  }
}

Graph::vertex& Graph::_adjacent(AdjacentList& l, size_t i) {
  switch (l.Flags) {
  case ZERO:
  case ONE:
    return *static_cast<vertex*>(&l.What);
  default:
    return AdjLists[l.What][i];
  }
}

uint32 Graph::_degree(const AdjacentList& l) const {
  switch (l.Flags) {
  case ZERO:
    return 0;
  case ONE:
    return 1;
  default:
    return AdjLists[l.What].size();
  }
}

void Graph::_add(AdjacentList& l, vertex v) {
  switch (l.Flags) {
  case ZERO:
    l.Flags = ONE;
    l.What = v;
    break;
  case ONE:
    if (v != l.What) {
      l.Flags = MANY;
      const vertex tmp[2] = { l.What, v };
      AdjLists.push_back(std::vector<vertex>(&tmp[0], &tmp[2]));
      l.What = AdjLists.size() - 1;
    }
    break;
  case MANY:
    for (std::vector<vertex>::const_iterator it(AdjLists[l.What].begin()); it != AdjLists[l.What].end(); ++it) {
      if (*it == v) {
        return;
      }
    }
    AdjLists[l.What].push_back(v);
    break;
  }
}

Graph::Graph(uint32 numVs, uint32 reserveSize): Vertices(numVs, Vertex())
{
  Vertices.reserve(reserveSize);
}

Graph::Graph(uint32 numVs): Vertices(numVs, Vertex())
{
}

Graph::vertex Graph::addVertex() {
  Vertices.push_back(Vertex());
  return Vertices.size() - 1;
}

bool Graph::edgeExists(const vertex source, const vertex target) const {
  for (uint32 ov = 0; ov < outDegree(source); ++ov) {
    if (outVertex(source, ov) == target) {
      return true;
    }
  }
  return false;
}

void Graph::addEdge(const vertex source, const vertex target) {
  if (source >= Vertices.size() || target >= Vertices.size()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("out of bounds, source = " << source << ", target = " << target << ", but size = " << Vertices.size());
  }
  _add(Vertices[source].Out, target);
  _add(Vertices[target].In, source);
}

/*
Graph::iterator Graph::begin() const {
  return iterator(boost::shared_ptr<Graph::AdjacentList::ItrBase>(new VertexItr(0)));
}

Graph::iterator Graph::end() const {
  return iterator(boost::shared_ptr<Graph::AdjacentList::ItrBase>(new VertexItr(numVertices())));
}
*/

std::ostream& operator<<(std::ostream& out, const Graph& g) {
  // print graph size
  out << "|g| = " << g.numVertices() << '\n';

  // print out edges for each vertex
  for (uint32 v = 0; v < g.numVertices(); ++v) {
    for (uint32 i = 0; i < g.outDegree(v); ++i) {
      out << v << " -> " << g.outVertex(v, i) << '\n';
    }
  }

  return out;
}
