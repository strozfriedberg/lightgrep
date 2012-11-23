/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "basic.h"

#include <algorithm>
#include <functional>
#include <iterator>
#include <limits>
#include <vector>

#include <boost/iterator/iterator_facade.hpp>

template <class GraphType,
          class VertexType,
          class EdgeType,
          template <typename> class EdgeDescriptorStorage>
class Graph: public GraphType
{
private:
  struct VertexData;
  struct EdgeData;

  typedef typename std::vector<VertexData> VList;
  typedef typename std::vector<EdgeData> EList;

public:
  typedef uint32_t VertexDescriptor;
  typedef uint32_t EdgeDescriptor;

  typedef typename VList::size_type VertexSizeType;
  typedef typename EList::size_type EdgeSizeType;

  typedef VertexType Vertex;
  typedef EdgeType Edge;

  typedef typename VList::iterator VertexIterator;
  typedef typename VList::const_iterator ConstVertexIterator;
  typedef typename EList::iterator EdgeIterator;
  typedef typename EList::const_iterator ConstEdgeIterator;

private:
#pragma pack(push, 1)
  struct VertexData: public VertexType {
    VertexData(): VertexType() {}

    VertexData(const VertexType& v): VertexType(v) {}

    typename EdgeDescriptorStorage<EdgeDescriptor>::ListType In, Out;
  };
#pragma pack(pop)

  struct EdgeData: public EdgeType {
    EdgeData(VertexDescriptor head, VertexDescriptor tail, const EdgeType& e): EdgeType(e), Head(head), Tail(tail) {}

    VertexDescriptor Head, Tail;
  };

  VList Vertices;
  EList Edges;

  EdgeDescriptorStorage<EdgeDescriptor> Store;

public:
  Graph(VertexSizeType vActual = 0): Vertices(vActual, VertexData()) {}

  Graph(VertexSizeType vActual, VertexSizeType vReserve, EdgeSizeType eReserve = 0) {
    if (vReserve > vActual) {
      Vertices.reserve(vReserve);
    }

    Vertices.resize(vActual, VertexData());
    Edges.reserve(eReserve);
  }

  //
  // lookup & access
  //

  VertexDescriptor inVertex(VertexDescriptor tail, EdgeSizeType i) const {
    return Edges[Store.at(Vertices[tail].In, i)].Head;
  }

  VertexDescriptor outVertex(VertexDescriptor head, EdgeSizeType i) const {
    return Edges[Store.at(Vertices[head].Out, i)].Tail;
  }

  EdgeDescriptor inEdge(VertexDescriptor tail, EdgeSizeType i) const {
    return Store.at(Vertices[tail].In, i);
  }

  EdgeDescriptor outEdge(VertexDescriptor head, EdgeSizeType i) const {
    return Store.at(Vertices[head].Out, i);
  }

  EdgeSizeType inDegree(VertexDescriptor tail) const {
    return Store.size(Vertices[tail].In);
  }

  EdgeSizeType outDegree(VertexDescriptor head) const {
    return Store.size(Vertices[head].Out);
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
  // iterators
  //

  class NeighborList {
  public:
    typedef typename EdgeDescriptorStorage<EdgeDescriptor>::ListType::const_iterator base_iterator;

    NeighborList(const EList& e, base_iterator eb, base_iterator ee, bool in):
      Edges(e), ebeg(eb), eend(ee), In(in) {}

    class ConstIterator:
      public boost::iterator_facade<
        ConstIterator,
        VertexDescriptor const,
        std::random_access_iterator_tag,
        VertexDescriptor const
      >
    {
    public:
      ConstIterator() {}

      ConstIterator(const ConstIterator& other):
        edges(other.edges), e(other.e), in(other.in) {}

      ConstIterator(const EList& ed, base_iterator ei, bool heads):
        edges(ed), e(ei), in(heads) {}

      typedef typename boost::iterator_facade<
        ConstIterator,
        VertexDescriptor const,
        std::random_access_iterator_tag,
        VertexDescriptor const
      >::difference_type difference_type;

    private:
      friend class boost::iterator_core_access;

      void increment() { ++e; }

      void decrement() { --e; }

      void advance(difference_type n) { e += n; }

      difference_type distance_to(const ConstIterator& o) const {
        return o.e - e;
      }

      bool equal(const ConstIterator& o) const { return e == o.e; }

      VertexDescriptor dereference() const {
        return in ? edges[*e].Head : edges[*e].Tail;
      }

      const EList& edges;
      base_iterator e;
      const bool in;
    };

    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    ConstIterator begin() const {
      return ConstIterator(Edges, ebeg, In);
    }

    ConstIterator end() const {
      return ConstIterator(Edges, eend, In);
    }

    ConstReverseIterator rbegin() const {
      return ConstReverseIterator(end());
    }

    ConstReverseIterator rend() const {
      return ConstReverseIterator(begin());
    }

  private:
    const EList& Edges;
    const base_iterator ebeg, eend;
    const bool In;
  };

  NeighborList inVertices(VertexDescriptor tail) const {
    return NeighborList(Edges, Store.begin(Vertices[tail].In), Store.end(Vertices[tail].In), true);
  }

  NeighborList outVertices(VertexDescriptor head) const {
    return NeighborList(Edges, Store.begin(Vertices[head].Out), Store.end(Vertices[head].Out), false);
  }

  class VertexList {
  public:
    VertexList(const VList& vertices): Vertices(vertices) {}

    class ConstIterator:
      public boost::iterator_facade<
        ConstIterator,
        VertexDescriptor const,
        std::random_access_iterator_tag
      >
    {
    public:
      ConstIterator(): v(0) {}

      ConstIterator(VertexDescriptor vd): v(vd) {}

      typedef typename boost::iterator_facade<
        ConstIterator,
        VertexDescriptor const,
        std::random_access_iterator_tag
      >::difference_type difference_type;

    private:
      friend class boost::iterator_core_access;

      void increment() { ++v; }

      void decrement() { --v; }

      void advance(difference_type n) { v += n; }

      difference_type distance_to(const ConstIterator& o) const {
        return o.v - v;
      }

      bool equal(const ConstIterator& o) const { return o.v == v; }

      const VertexDescriptor& dereference() const { return v; }

      VertexDescriptor v;
    };

    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    ConstIterator begin() const {
      return ConstIterator(0);
    }

    ConstIterator end() const {
      return ConstIterator(Vertices.size());
    }

    ConstReverseIterator rbegin() const {
      return ConstReverseIterator(end());
    }

    ConstReverseIterator rend() const {
      return ConstReverseIterator(begin());
    }

  private:
    const VList& Vertices;
  };

  VertexList vertices() const {
    return VertexList(Vertices);
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
      Store.clear(i->In);
      Store.clear(i->Out);
    }
  }

  void clearVertices() {
    Vertices.clear();
    Edges.clear();
  }

  VertexDescriptor addVertex(const VertexType& v = VertexType()) {
    Vertices.emplace_back(v);
    return Vertices.size() - 1;
  }

  void removeVertex(VertexDescriptor vd) {
    using namespace std::placeholders;

    const VertexData& v(Vertices[vd]);
    std::for_each(Store.begin(v.In), Store.end(v.In), std::bind(&Graph::removeEdge, this, _1));
    std::for_each(Store.begin(v.Out), Store.end(v.Out), std::bind(&Graph::removeEdge, this, _1));

    compact_after_vertex(vd);
  }

  EdgeDescriptor addEdge(VertexDescriptor head, VertexDescriptor tail, const EdgeType& e = EdgeType()) {
    Edges.emplace_back(head, tail, e);
    const EdgeDescriptor ed = Edges.size() - 1;
    Store.add(Vertices[head].Out, ed);
    Store.add(Vertices[tail].In, ed);
    return ed;
  }

  EdgeDescriptor insertEdge(VertexDescriptor head, VertexDescriptor tail, EdgeSizeType hi = std::numeric_limits<EdgeSizeType>::max(), EdgeSizeType ti = std::numeric_limits<EdgeSizeType>::max(), const EdgeType& e = EdgeType()) {
    Edges.emplace_back(head, tail, e);
    const EdgeDescriptor ed = Edges.size() - 1;
    Store.insert(Vertices[head].Out, hi, ed);
    Store.insert(Vertices[tail].In, ti, ed);
    return ed;
  }

  void removeEdge(EdgeDescriptor ed) {
    Store.remove(Vertices[Edges[ed].Head].Out, ed);
    Store.remove(Vertices[Edges[ed].Tail].In, ed);
    compact_after_edge(ed);
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
  void compact_after_edge(EdgeDescriptor ed) {
    typename EList::iterator i(Edges.erase(Edges.begin() + ed));
    const typename EList::iterator iend(Edges.end());
    for ( ; i != iend; ++i) {
      const EdgeDescriptor e = i - Edges.begin() + 1;
      --*Store.find(Vertices[i->Head].Out, e);
      --*Store.find(Vertices[i->Tail].In, e);
    }
  }

  void compact_after_vertex(VertexDescriptor vd) {
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
};

template <class G, class V, class E, template <typename> class S> std::ostream& operator<<(std::ostream& out, const Graph<G,V,E,S>& g) {
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
