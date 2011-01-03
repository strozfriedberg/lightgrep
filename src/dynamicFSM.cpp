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

DynamicFSM::AdjacentList::Itr DynamicFSM::AdjacentList::begin() const {
  switch (Flags) {
    case ZERO:
      return Itr(boost::shared_ptr<ItrBase>(new ZeroItr));
    case ONE:
      return Itr(boost::shared_ptr<ItrBase>(new OneItr(&V.Single)));
    default:
      return Itr(boost::shared_ptr<ItrBase>(new ManyItr(V.List.begin())));
  }
}

DynamicFSM::AdjacentList::Itr DynamicFSM::AdjacentList::end() const {
  switch (Flags) {
    case ZERO:
      return Itr(boost::shared_ptr<ItrBase>(new ZeroItr));
    case ONE:
      return Itr(boost::shared_ptr<ItrBase>(new OneItr(0)));
    default:
      return Itr(boost::shared_ptr<ItrBase>(new ManyItr(V.List.end())));
  }
}

void DynamicFSM::AdjacentList::add(vertex_descriptor v) {
  switch (Flags) {
    case ZERO:
      Flags = ONE;
      V.Single = v;
      break;
    case ONE:
      if (v != V.Single) {
        Flags = MANY;
        vertex_descriptor temp = V.Single;
        // V.List = new std::vector<vertex_descriptor>();
        V.List.push_back(temp);
        V.List.push_back(v);
        // vertex_descriptor tempArray[2];
        // tempArray[0] = V.Single;
        // tempArray[1] = v;
        // V.List = new std::vector<vertex_descriptor>(&tempArray[0], &tempArray[2]);
      }
      break;
    case MANY:
      for (std::vector<vertex_descriptor>::const_iterator it(V.List.begin()); it != V.List.end(); ++it) {
        if (*it == v) {
          return;
        }
      }
      V.List.push_back(v);
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
  DynamicFSM::const_iterator ov(outVertices(source).begin()),
                             ov_end(outVertices(source).end());

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
  Vertices[source].Out.add(target);
  Vertices[target].In.add(source);
}

DynamicFSM::iterator DynamicFSM::begin() const {
  return iterator(boost::shared_ptr<DynamicFSM::AdjacentList::ItrBase>(new VertexItr(0)));
}

DynamicFSM::iterator DynamicFSM::end() const {
  return iterator(boost::shared_ptr<DynamicFSM::AdjacentList::ItrBase>(new VertexItr(numVertices())));
}
