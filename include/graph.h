#pragma once

#include <iostream>

#include "transition.h"

typedef boost::shared_ptr<Transition> TransitionPtr;

class Graph {
public:
  friend std::ostream& operator<<(std::ostream& out, const Graph& g);

  typedef uint32 vertex;

private:
  enum FlagType {
    ZERO = 0,
    ONE  = 1,
    MANY = ONE << 1
  };

public:
#pragma pack(1)
  struct AdjacentList {
    uint32 What;
    byte Flags;

    AdjacentList(): Flags(ZERO) { What = 0xFFFFFFFF; }
  };

  struct Vertex {
    Transition* Tran;
    AdjacentList In, Out;

    Vertex(): Tran(0) {}
    Vertex(Transition* t): Tran(t) {}
  };
#pragma pack()

  Graph(uint32 numVs, uint32 reserveSize);
  Graph(uint32 numVs = 0);
  ~Graph();

  uint32 numVertices() const { return Vertices.size(); }
  uint32 capacity() const { return Vertices.capacity(); }

  vertex addVertex(Transition* t = 0);

  bool edgeExists(const vertex source, const vertex target) const;

  void addEdge(const vertex source, const vertex target);
  void addEdgeAt(const vertex source, const vertex target, size_t i);

  // these do not check for duplicate edges before adding them
  void addEdgeND(const vertex source, const vertex target);
  void addEdgeAtND(const vertex source, const vertex target, size_t i);

  vertex inVertex(vertex v, size_t i) const {
    return _adjacent(Vertices[v].In, i);
  }

  vertex outVertex(vertex v, size_t i) const {
    return _adjacent(Vertices[v].Out, i);
  }

  uint32 inDegree(const vertex v) const {
    return _degree(Vertices[v].In);
  }

  uint32 outDegree(const vertex v) const {
    return _degree(Vertices[v].Out);
  }

  Transition* operator[](vertex v) const {
    return Vertices[v].Tran;
  }

/*  Transition* & operator[](vertex v) {
    return Transitions[Vertices[v].TranIndex];
  }*/

  void setTran(const vertex& v, Transition* tran) {
    Vertices[v].Tran = tran;
  }

  void clear();

private:
  Graph(const Graph&);
  Graph& operator=(const Graph&);

  void _add(AdjacentList& l, vertex v);
  void _add(AdjacentList& l, vertex v, size_t i);

  void _add_no_dupe_check(AdjacentList& l, vertex v);
  void _add_no_dupe_check(AdjacentList& l, vertex v, size_t i);

  uint32 _degree(const AdjacentList& l) const;

  vertex _adjacent(const AdjacentList& l, size_t i) const;
  vertex& _adjacent(AdjacentList& l, size_t i);

  std::vector< Vertex > Vertices;
  std::vector< std::vector< vertex > > AdjLists;
};

typedef boost::shared_ptr<Graph> GraphPtr;
