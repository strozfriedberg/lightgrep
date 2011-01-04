#pragma once

#include "transition.h"

typedef boost::shared_ptr<Transition> TransitionPtr;

// new hotness
class DynamicFSM {
public:
  typedef uint32 vertex_descriptor;

// #pragma pack(1)
  class AdjacentList {
  private:
    // union {
    struct {
      vertex_descriptor Single;
      std::vector< vertex_descriptor > List;
    } V;
    byte Flags;
    
  public:
    enum {
      ZERO = 0,
      ONE  = 1,
      MANY = ONE << 1
    };
    
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

    AdjacentList(): Flags(ZERO) { V.Single = 0xFFFFFFFF; }
//    ~AdjacentList() { if (Flags & MANY) delete V.List; }

    size_t size() const {
      switch (Flags) {
        case ZERO:
          return 0;
        case ONE:
          return 1;
        default:
          return V.List.size();
      }
    }

    vertex_descriptor operator[](size_t i) const { return Flags & ONE ? V.Single: (V.List)[i]; }

    Itr begin() const;
    Itr end() const;

    void add(vertex_descriptor v);
  };

  struct Vertex {
    TransitionPtr Tran;
    AdjacentList In,
                  Out;
  };
// #pragma pack()

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

  uint32 inDegree(const vertex_descriptor v) const {
    return Vertices[v].In.size();
  }

  uint32 outDegree(const vertex_descriptor v) const {
    return Vertices[v].Out.size();
  }

  const TransitionPtr operator[](vertex_descriptor v) const {
    return Vertices[v].Tran; 
  }
  
  TransitionPtr& operator[](vertex_descriptor v) { return Vertices[v].Tran; }
  
  iterator begin() const;
  iterator end() const;

  void clear() { Vertices.clear(); }

private:
  std::vector< Vertex > Vertices;
};

typedef boost::shared_ptr<DynamicFSM> DynamicFSMPtr;
