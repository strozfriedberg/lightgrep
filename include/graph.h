#pragma once

#include "basic.h"
#include "smallvector.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include <boost/bind.hpp>

template <class GraphType,
          class VertexType,
          class EdgeType,
          class EdgeDescriptorStorageFactory>
class Graph : public GraphType
{
private:
  struct VertexData;
  struct EdgeData;

  typedef typename std::vector<VertexData> VList;
  typedef typename std::vector<EdgeData> EList;

public:
  typedef uint32 VertexDescriptor;
  typedef uint32 EdgeDescriptor;

  typedef typename VList::size_type VertexSizeType;
  typedef typename EList::size_type EdgeSizeType;

  typedef VertexType Vertex;
  typedef EdgeType Edge;

private:
  typedef typename EdgeDescriptorStorageFactory::ListType EDList;

  struct VertexData : public VertexType {
    VertexData(EdgeDescriptorStorageFactory& fac): VertexType(), In(fac.create()), Out(fac.create()) {}

    VertexData(const VertexType& v, EdgeDescriptorStorageFactory& fac): VertexType(v), In(fac.create()), Out(fac.create()) {}

    EDList In, Out;
  };

  struct EdgeData : public EdgeType {
    EdgeData(VertexDescriptor head, VertexDescriptor tail, const EdgeType& e): EdgeType(e), Head(head), Tail(tail) {}

    VertexDescriptor Head, Tail;
  };

public:

  Graph(VertexSizeType vActual = 0): Vertices(vActual, VertexData(EDSFactory)) {}

  Graph(VertexSizeType vActual, VertexSizeType vReserve, EdgeSizeType eReserve = 0) {
    if (vReserve > vActual) {
      Vertices.reserve(vReserve);
    }

    Vertices.resize(vActual, VertexData(EDSFactory));

    if (eReserve > 0) {
      Edges.reserve(eReserve);
    }
  }

  //
  // lookup & access
  //

  VertexDescriptor inVertex(VertexDescriptor tail, EdgeSizeType i) const {
    return Edges[Vertices[tail].In[i]].Head;
  }

  VertexDescriptor outVertex(VertexDescriptor head, EdgeSizeType i) const {
    return Edges[Vertices[head].Out[i]].Tail;
  }

  EdgeDescriptor inEdge(VertexDescriptor tail, EdgeSizeType i) const {
    return Vertices[tail].In[i];
  }

  EdgeDescriptor outEdge(VertexDescriptor head, EdgeSizeType i) const {
    return Vertices[head].Out[i];
  }

  EdgeSizeType inDegree(VertexDescriptor tail) const {
    return Vertices[tail].In.size();
  }

  EdgeSizeType outDegree(VertexDescriptor head) const {
    return Vertices[head].Out.size();
  }

  VertexType& operator[](VertexDescriptor vd) {
    return Vertices[vd];
  }

  const VertexType& operator[](VertexDescriptor vd) const {
    return Vertices[vd];
  }

  EdgeType& operator()(EdgeDescriptor ed) {
    return Edges[ed];
  }

  const EdgeType& operator()(EdgeDescriptor ed) const {
    return Edges[ed];
  }

  //
  // modifiers
  //

  void clear() {
    clearVertices();
  }

  void clearEdges() {
    Edges.clear();

    const typename VList::iterator iend(Vertices.end());
    for (typename VList::iterator i(Vertices.begin()); i != iend; ++i) {
      i->In.clear();
      i->Out.clear();
    }
  }

  void clearVertices() {
    Vertices.clear();
    Edges.clear();
  }

  VertexDescriptor addVertex(const VertexType& v = VertexType()) {
    Vertices.push_back(VertexData(v, EDSFactory));
    return Vertices.size() - 1;
  }

  void removeVertex(VertexDescriptor vd) {
    const VertexData& v(Vertices[vd]);
    std::for_each(v.In.begin(), v.In.end(), boost::bind(&Graph::removeEdge, this, _1));
    std::for_each(v.Out.begin(), v.Out.end(), boost::bind(&Graph::removeEdge, this, _1));

    compact_vertex(vd);
  }

  EdgeDescriptor addEdge(VertexDescriptor head, VertexDescriptor tail, const EdgeType& e = EdgeType()) {
    Edges.push_back(EdgeData(head, tail, e));
    const EdgeDescriptor ed = Edges.size() - 1;
    Vertices[head].Out.push_back(ed);
    Vertices[tail].In.push_back(ed);
    return ed;
  }

  EdgeDescriptor insertEdge(VertexDescriptor head, VertexDescriptor tail, EdgeSizeType hi = std::numeric_limits<EdgeSizeType>::max(), EdgeSizeType ti = std::numeric_limits<EdgeSizeType>::max(), const EdgeType& e = EdgeType()) {
    Edges.push_back(EdgeData(head, tail, e));
    const EdgeDescriptor ed = Edges.size() - 1;

    attach_edge(Vertices[head].Out, hi, ed);
    attach_edge(Vertices[tail].In, ti, ed);

    return ed;
  }

  void removeEdge(EdgeDescriptor ed) {
    detach_edge(Vertices[Edges[ed].Head].Out, ed);
    detach_edge(Vertices[Edges[ed].Tail].In, ed);

    compact_edge(ed);
  }

  //
  // capacity
  //

  VertexSizeType verticesSize() const {
    return Vertices.size();
  }

  EdgeSizeType edgesSize() const {
    return Edges.size();
  }

  VertexSizeType verticesCapacity() const {
    return Vertices.capacity();
  }

  EdgeSizeType edgesCapacity() const {
    return Edges.capacity();
  }

  void reserveVertices(VertexSizeType size) {
    return Vertices.reserve(size);
  }

  void reserveEdges(EdgeSizeType size) {
    return Edges.reserve(size);
  }

private:
  void attach_edge(EDList& elist, EdgeSizeType epos, EdgeDescriptor ed) {
    elist.insert(epos < elist.size() ? elist.begin() + epos : elist.end(), ed);
  }

  void detach_edge(EDList& elist, EdgeDescriptor ed) {
    elist.erase(std::find(elist.begin(), elist.end(), ed));
  }

  void compact_edge(EdgeDescriptor ed) {
    typename EList::iterator i(Edges.erase(Edges.begin() + ed));
    const typename EList::iterator iend(Edges.end());
    for ( ; i != iend; ++i) {
      EDList& out(Vertices[i->Head].Out);
      --*std::find(out.begin(), out.end(), i - Edges.begin() + 1);

      EDList& in(Vertices[i->Tail].In);
      --*std::find(in.begin(), in.end(), i - Edges.begin() + 1);
    }
  }

  void compact_vertex(VertexDescriptor vd) {
    Vertices.erase(Vertices.begin() + vd);

    const typename EList::iterator iend(Edges.end());
    for (typename EList::iterator i(Edges.begin()); i != iend; ++i) {
      if (i->Head > vd) {
        --i->Head;
      }

      if (i->Tail > vd) {
        --i->Tail;
      }
    }
  }

  VList Vertices;
  EList Edges;

  EdgeDescriptorStorageFactory EDSFactory;
};

template <class G, class V, class E, class S> std::ostream& operator<<(std::ostream& out, const Graph<G,V,E,S>& g) {
  const typename Graph<G,V,E,S>::VertexSizeType vnum = g.verticesSize();

  // print graph size
  out << "|g| = " << vnum << '\n';

  // print out edges for each vertex
  for (typename Graph<G,V,E,S>::VertexSizeType v = 0; v < vnum; ++v) {
    const typename Graph<G,V,E,S>::EdgeSizeType odeg = g.outDegree(v);
    for (typename Graph<G,V,E,S>::EdgeSizeType o = 0; o < odeg; ++o) {
      out << v << " -> " << g.outVertex(v, o) << '\n';
    }
  }

  return out;
}
