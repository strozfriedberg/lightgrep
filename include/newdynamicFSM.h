#pragma once

#include "dynamicFSM.h"

// new hotness
class NewDynamicFSM {
public:
  typedef uint32 vertex_descriptor;

#pragma pack(1)
  struct AdjacentList {
    enum {
      ZERO = 0,
      ONE  = 1,
      MANY = ONE << 1
    };
    
    union {
      vertex_descriptor Single;
      std::vector< vertex_descriptor >* List;
    } V;
    byte Flags;

    AdjacentList(): Flags(ZERO) { V.Single = 0xFFFFFFFF; }
    ~AdjacentList() { if (Flags & MANY) delete V.List; }

    size_t size() const {
      switch (Flags) {
        case ZERO:
          return 0;
        case ONE:
          return 1;
        case MANY:
          return V.List->size();
      }
    }

    void add(vertex_descriptor v) {
      switch (Flags) {
        case ZERO:
          Flags = ONE;
          V.Single = v;
          break;
        case ONE:
          if (v != V.Single) {
            vertex_descriptor tempArray[2];
            tempArray[0] = V.Single;
            tempArray[1] = v;
            Flags = MANY;
            V.List = new std::vector<vertex_descriptor>(&tempArray[0], &tempArray[2]);
          }
          break;
        case MANY:
          for (std::vector<vertex_descriptor>::const_iterator it(V.List->begin()); it != V.List->end(); ++it) {
            if (*it == v) {
              return;
            }
          }
          V.List->push_back(v);
          break;
      }
    }
  };

  struct Vertex {
    TransitionPtr Tran;
    AdjacentList In,
                  Out;
  };
#pragma pack()

  NewDynamicFSM(uint32 numVs, uint32 reserveSize);
  NewDynamicFSM(uint32 numVs = 0);

  uint32 numVertices() const { return Vertices.size(); }
  uint32 capacity() const { return Vertices.capacity(); }

  NewDynamicFSM::vertex_descriptor addVertex();

  const AdjacentList& inVertices(const vertex_descriptor v) const { return Vertices[v].In; }
  const AdjacentList& outVertices(const vertex_descriptor v) const { return Vertices[v].Out; }


  const TransitionPtr operator[](vertex_descriptor v) const { return Vertices[v].Tran; }

private:
  std::vector< Vertex > Vertices;
};

namespace boost {
  uint32 num_vertices(const NewDynamicFSM& g);

  NewDynamicFSM::vertex_descriptor add_vertex(NewDynamicFSM& g);
}

