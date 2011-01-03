#include "newdynamicFSM.h"

NewDynamicFSM::NewDynamicFSM(uint32 numVs, uint32 reserveSize): Vertices(numVs, Vertex())
{
  Vertices.reserve(reserveSize);
}

NewDynamicFSM::NewDynamicFSM(uint32 numVs): Vertices(numVs, Vertex())
{
}

NewDynamicFSM::vertex_descriptor NewDynamicFSM::addVertex() {
  Vertices.push_back(Vertex());
  return Vertices.size() - 1;
}

namespace boost {
  uint32 num_vertices(const NewDynamicFSM& g) {
    return g.numVertices();
  }

  NewDynamicFSM::vertex_descriptor add_vertex(NewDynamicFSM& g) {
    return g.addVertex();
  }
}
