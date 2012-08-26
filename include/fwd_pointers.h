#pragma once

#include "basic.h"

template <class GraphType,
          class VertexType,
          class EdgeType,
          template <typename> class EdgeDescriptorStorage>
class Graph;

struct Properties;
struct Glushkov;
struct Empty;
template <typename T> class VectorFamily;

typedef Graph<Properties, Glushkov, Empty, VectorFamily> NFA;

typedef std::shared_ptr<NFA> NFAPtr;

class Program;

typedef std::shared_ptr<Program> ProgramPtr;
