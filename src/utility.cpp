#include "utility.h"

boost::shared_ptr<StaticFSM> convert_to_static(const DynamicFSM& graph) {
  boost::shared_ptr<StaticFSM> ret(new StaticFSM());
  ret->allocate(0, num_vertices(graph), 0);
  return ret;
}
