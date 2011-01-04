#include "dynamicFSM.h"

#include <algorithm>

typedef DynamicFSM::vertex_descriptor vertex_descriptor;

namespace {
  static const vertex_descriptor BAD = 0xffffffff;
}

class ZeroItr: public DynamicFSM::AdjacentList::ItrBase {
public:
  virtual ~ZeroItr() {}

  virtual bool isEqual(const ItrBase&) const { return true; }
  virtual void advance() {}
  virtual const vertex_descriptor& get() const { return BAD; }
  virtual ZeroItr* clone() const { return new ZeroItr; }
};

class OneItr: public DynamicFSM::AdjacentList::ItrBase {
public:
  OneItr(const vertex_descriptor* vPtr): VPtr(vPtr) {}

  virtual ~OneItr() {}
  
  virtual bool isEqual(const ItrBase& x) const {
    const OneItr* xPtr = dynamic_cast<const OneItr*>(&x);
    return xPtr && xPtr->VPtr == VPtr;
  }

  virtual void advance() { VPtr = 0; }
  
  virtual const vertex_descriptor& get() const { return *VPtr; }
  
  virtual OneItr* clone() const { return new OneItr(VPtr); }

private:
  const vertex_descriptor* VPtr;
};

class ManyItr: public DynamicFSM::AdjacentList::ItrBase {
public:
  ManyItr(const std::vector<vertex_descriptor>::const_iterator &it): It(it) {}

  virtual ~ManyItr() {}

  virtual bool isEqual(const ItrBase& x) const {
    const ManyItr* xPtr = dynamic_cast<const ManyItr*>(&x);
    return xPtr && xPtr->It == It;
  }

  virtual void advance() { ++It; }

  virtual const vertex_descriptor& get() const { return *It; } // ugh
  
  virtual ManyItr* clone() const { return new ManyItr(It); }

private:
  std::vector<vertex_descriptor>::const_iterator It;
};

class VertexItr: public DynamicFSM::AdjacentList::ItrBase {
public:
  VertexItr(vertex_descriptor v): V(v) {}

  virtual ~VertexItr() {}

  virtual bool isEqual(const ItrBase& x) const {
    const VertexItr* xPtr = dynamic_cast<const VertexItr*>(&x);
    return xPtr && xPtr->V == V;
  }

  virtual void advance() { ++V; }

  virtual const vertex_descriptor& get() const { return V; }
  
  virtual VertexItr* clone() const { return new VertexItr(V); }

private:
  vertex_descriptor V;
};

DynamicFSM::AdjacentList::Itr DynamicFSM::_adjbegin(const AdjacentList& l) const
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

DynamicFSM::AdjacentList::Itr DynamicFSM::_adjend(const AdjacentList& l) const {
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

uint32 DynamicFSM::_degree(const AdjacentList& l) const {
  switch (l.Flags) {
  case ZERO:
    return 0;
  case ONE:
    return 1;
  default:
    return AdjLists[l.What].size();
  }
}

void DynamicFSM::_add(AdjacentList& l, vertex_descriptor v) {
  switch (l.Flags) {
    case ZERO:
      l.Flags = ONE;
      l.What = v;
      break;
    case ONE:
      if (v != l.What) {
        l.Flags = MANY;
        vertex_descriptor tmp[2] = { l.What, v };
        AdjLists.push_back(std::vector<vertex_descriptor>(&tmp[0], &tmp[2]));
        l.What = AdjLists.size() - 1;
      }
      break;
    case MANY:
      for (std::vector<vertex_descriptor>::const_iterator it(AdjLists[l.What].begin()); it != AdjLists[l.What].end(); ++it) {
        if (*it == v) {
          return;
        }
      }
      AdjLists[l.What].push_back(v);
      break;
  }
}

DynamicFSM::DynamicFSM(uint32 numVs, uint32 reserveSize): Vertices(numVs, Vertex())
{
  Vertices.reserve(reserveSize);
}

DynamicFSM::DynamicFSM(uint32 numVs): Vertices(numVs, Vertex())
{
}

DynamicFSM::vertex_descriptor DynamicFSM::addVertex() {
  Vertices.push_back(Vertex());
  return Vertices.size() - 1;
}

bool DynamicFSM::edgeExists(const vertex_descriptor source, const vertex_descriptor target) const {
  DynamicFSM::const_iterator ov(outVerticesBegin(source)),
                             ov_end(outVerticesEnd(source));

  for (; ov != ov_end; ++ov) {
    if (*ov == target) {
      return true;
    }
  }
  return false;
}

void DynamicFSM::addEdge(const vertex_descriptor source, const vertex_descriptor target) {
  if (source >= Vertices.size() || target >= Vertices.size()) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("out of bounds, source = " << source << ", target = " << target << ", but size = " << Vertices.size());
  }
  _add(Vertices[source].Out, target);
  _add(Vertices[target].In, source);
}

DynamicFSM::iterator DynamicFSM::begin() const {
  return iterator(boost::shared_ptr<DynamicFSM::AdjacentList::ItrBase>(new VertexItr(0)));
}

DynamicFSM::iterator DynamicFSM::end() const {
  return iterator(boost::shared_ptr<DynamicFSM::AdjacentList::ItrBase>(new VertexItr(numVertices())));
}
