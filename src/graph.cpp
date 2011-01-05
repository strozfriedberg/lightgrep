#include "graph.h"

#include <algorithm>

typedef Graph::vertex vertex;

const Graph::vertex Graph::BAD = 0xFFFFFFFF;

class ZeroItr: public Graph::AdjacentList::ItrBase {
public:
  virtual ~ZeroItr() {}

  virtual bool isEqual(const ItrBase&) const { return true; }
  virtual void advance() {}
  virtual const vertex& get() const { return Graph::BAD; }
  virtual ZeroItr* clone() const { return new ZeroItr; }
};

class OneItr: public Graph::AdjacentList::ItrBase {
public:
  OneItr(const vertex* vPtr): VPtr(vPtr) {}

  virtual ~OneItr() {}
  
  virtual bool isEqual(const ItrBase& x) const {
    const OneItr* xPtr = dynamic_cast<const OneItr*>(&x);
    return xPtr && xPtr->VPtr == VPtr;
  }

  virtual void advance() { VPtr = 0; }
  
  virtual const vertex& get() const { return *VPtr; }
  
  virtual OneItr* clone() const { return new OneItr(VPtr); }

private:
  const vertex* VPtr;
};

class ManyItr: public Graph::AdjacentList::ItrBase {
public:
  ManyItr(const std::vector<vertex>::const_iterator &it): It(it) {}

  virtual ~ManyItr() {}

  virtual bool isEqual(const ItrBase& x) const {
    const ManyItr* xPtr = dynamic_cast<const ManyItr*>(&x);
    return xPtr && xPtr->It == It;
  }

  virtual void advance() { ++It; }

  virtual const vertex& get() const { return *It; } // ugh
  
  virtual ManyItr* clone() const { return new ManyItr(It); }

private:
  std::vector<vertex>::const_iterator It;
};

class VertexItr: public Graph::AdjacentList::ItrBase {
public:
  VertexItr(vertex v): V(v) {}

  virtual ~VertexItr() {}

  virtual bool isEqual(const ItrBase& x) const {
    const VertexItr* xPtr = dynamic_cast<const VertexItr*>(&x);
    return xPtr && xPtr->V == V;
  }

  virtual void advance() { ++V; }

  virtual const vertex& get() const { return V; }
  
  virtual VertexItr* clone() const { return new VertexItr(V); }

private:
  vertex V;
};

Graph::AdjacentList::Itr Graph::_adjbegin(const AdjacentList& l) const
{
  using namespace boost;

  switch (l.Flags) {
    case ZERO:
      return iterator(shared_ptr<AdjacentList::ItrBase>(new ZeroItr));
    case ONE:
      return iterator(shared_ptr<AdjacentList::ItrBase>(new OneItr(&l.What)));
    default:
      return iterator(shared_ptr<AdjacentList::ItrBase>(new ManyItr(AdjLists[l.What].begin())));
  }
}

Graph::AdjacentList::Itr Graph::_adjend(const AdjacentList& l) const {
  using namespace boost;

  switch (l.Flags) {
    case ZERO:
      return iterator(shared_ptr<AdjacentList::ItrBase>(new ZeroItr));
    case ONE:
      return iterator(shared_ptr<AdjacentList::ItrBase>(new OneItr(0)));
    default:
      return iterator(shared_ptr<AdjacentList::ItrBase>(new ManyItr(AdjLists[l.What].end())));
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
  Graph::const_iterator ov(outVerticesBegin(source)),
                             ov_end(outVerticesEnd(source));

  for (; ov != ov_end; ++ov) {
    if (*ov == target) {
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

Graph::iterator Graph::begin() const {
  return iterator(boost::shared_ptr<Graph::AdjacentList::ItrBase>(new VertexItr(0)));
}

Graph::iterator Graph::end() const {
  return iterator(boost::shared_ptr<Graph::AdjacentList::ItrBase>(new VertexItr(numVertices())));
}
