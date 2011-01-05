#pragma once

#include <iostream>

#include "transition.h"

typedef boost::shared_ptr<Transition> TransitionPtr;

// new hotness
class DynamicFSM {
public:
  typedef uint32 vertex_descriptor;

  static const vertex_descriptor BAD;

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
    
    class ItrBase {
    public:
      virtual ~ItrBase() {}
      virtual bool isEqual(const ItrBase& x) const = 0;
      virtual void advance() = 0;
      virtual const vertex_descriptor& get() const = 0;
      virtual ItrBase* clone() const = 0;
    };

    struct Itr {
      boost::shared_ptr<ItrBase> Base;

      Itr(const boost::shared_ptr<ItrBase>& base): Base(base) {}

      bool operator==(const Itr& x) const { return x.Base->isEqual(*Base); }
      bool operator!=(const Itr& x) const { return !x.Base->isEqual(*Base); }
      
      Itr& operator++() {
        Base->advance();
        return *this;
      }

      Itr operator++(int) {
        Itr copy(boost::shared_ptr<ItrBase>(Base->clone()));
        Base->advance();
        return copy;
      }
  
      const vertex_descriptor& operator*() const { return Base->get(); } 
    };

    typedef Itr iterator;
    typedef Itr const_iterator; // so, so evil

    AdjacentList(): Flags(ZERO) { What = 0xFFFFFFFF; }
  };

  struct Vertex {
    TransitionPtr Tran;
    AdjacentList In, Out;
  };
#pragma pack()

  typedef AdjacentList::iterator iterator;
  typedef AdjacentList::const_iterator const_iterator;

  DynamicFSM(uint32 numVs, uint32 reserveSize);
  DynamicFSM(uint32 numVs = 0);

  uint32 numVertices() const { return Vertices.size(); }
  uint32 capacity() const { return Vertices.capacity(); }

  vertex_descriptor addVertex();

  bool edgeExists(const vertex_descriptor source, const vertex_descriptor target) const;

  void addEdge(const vertex_descriptor source, const vertex_descriptor target);

  const AdjacentList& inVertices(const vertex_descriptor v) const {
    return Vertices[v].In;
  }
  
  const AdjacentList& outVertices(const vertex_descriptor v) const {
    return Vertices[v].Out;
  }

  iterator inVerticesBegin(vertex_descriptor v) const {
    return _adjbegin(Vertices[v].In);
  }
  
  iterator inVerticesEnd(vertex_descriptor v) const {
    return _adjend(Vertices[v].In);
  }

  iterator outVerticesBegin(vertex_descriptor v) const {
    return _adjbegin(Vertices[v].Out);
  }

  iterator outVerticesEnd(vertex_descriptor v) const {
    return _adjend(Vertices[v].Out);
  }

  uint32 inDegree(const vertex_descriptor v) const {
    return _degree(Vertices[v].In);
  }

  uint32 outDegree(const vertex_descriptor v) const {
    return _degree(Vertices[v].Out);
  }

  const TransitionPtr operator[](vertex_descriptor v) const {
    return Vertices[v].Tran; 
  }
  
  TransitionPtr& operator[](vertex_descriptor v) { return Vertices[v].Tran; }
  
  iterator begin() const;
  iterator end() const;

  void clear() {
    Vertices.clear();
    AdjLists.clear();
  }

private:
  void _add(AdjacentList& l, vertex_descriptor v);

  uint32 _degree(const AdjacentList& l) const;

  AdjacentList::Itr _adjbegin(const AdjacentList& l) const;
  AdjacentList::Itr _adjend(const AdjacentList& l) const;

  std::vector< Vertex > Vertices;
  std::vector< std::vector< vertex_descriptor > > AdjLists;
};

typedef boost::shared_ptr<DynamicFSM> DynamicFSMPtr;
