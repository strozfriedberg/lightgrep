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

void Graph::_add(AdjacentList& l, vertex v, size_t i) {
  switch (l.Flags) {
  case ZERO:
    l.Flags = ONE;
    l.What = v;
    break;
  case ONE:
    if (v != l.What) {
      l.Flags = MANY;

      vertex tmp[2];
      if (i == 0) {
        tmp[0] = v;
        tmp[1] = l.What;
      }
      else {
        tmp[0] = l.What;
        tmp[1] = v;
      }

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
    std::vector<vertex>::iterator it(AdjLists[l.What].begin() + i);
    AdjLists[l.What].insert(it, v);
    break;
  }
}
void Graph::_add_no_dupe_check(AdjacentList& l, vertex v) {
  switch (l.Flags) {
  case ZERO:
    l.Flags = ONE;
    l.What = v;
    break;
  case ONE:
    { 
      l.Flags = MANY;
      const vertex tmp[2] = { l.What, v };
      AdjLists.push_back(std::vector<vertex>(&tmp[0], &tmp[2]));
      l.What = AdjLists.size() - 1;
    }
    break;
  case MANY:
    AdjLists[l.What].push_back(v);
    break;
  }
}

void Graph::_add_no_dupe_check(AdjacentList& l, vertex v, size_t i) {
  switch (l.Flags) {
  case ZERO:
    l.Flags = ONE;
    l.What = v;
    break;
  case ONE:
    {
      l.Flags = MANY;

      vertex tmp[2];
      if (i == 0) {
        tmp[0] = v;
        tmp[1] = l.What;
      }
      else {
        tmp[0] = l.What;
        tmp[1] = v;
      }

      AdjLists.push_back(std::vector<vertex>(&tmp[0], &tmp[2]));
      l.What = AdjLists.size() - 1;
    }
    break;
  case MANY:
    std::vector<vertex>::iterator it(AdjLists[l.What].begin() + i);
    AdjLists[l.What].insert(it, v);
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

Graph::~Graph() {
  clear();
}

Graph::vertex Graph::addVertex(Transition* t) {
  Vertices.push_back(Vertex(t));
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

void Graph::addEdgeAt(const vertex source, const vertex target, size_t i) {
  if (source >= Vertices.size() || target >= Vertices.size()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("out of bounds, source = " << source << ", target = " << target << ", but size = " << Vertices.size());
  }
  _add(Vertices[source].Out, target, i);
  _add(Vertices[target].In, source);
}

void Graph::addEdgeND(const vertex source, const vertex target) {
  if (source >= Vertices.size() || target >= Vertices.size()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("out of bounds, source = " << source << ", target = " << target << ", but size = " << Vertices.size());
  }
  _add_no_dupe_check(Vertices[source].Out, target);
  _add_no_dupe_check(Vertices[target].In, source);
}

void Graph::addEdgeAtND(const vertex source, const vertex target, size_t i) {
  if (source >= Vertices.size() || target >= Vertices.size()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("out of bounds, source = " << source << ", target = " << target << ", but size = " << Vertices.size());
  }
  _add_no_dupe_check(Vertices[source].Out, target, i);
  _add_no_dupe_check(Vertices[target].In, source);
}

void Graph::clear() {
  for (std::vector<Vertex>::iterator it(Vertices.begin()); it != Vertices.end(); ++it) {
    if (it->Tran) {
      delete it->Tran;
    }
  }
  Vertices.clear();
  AdjLists.clear();
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
