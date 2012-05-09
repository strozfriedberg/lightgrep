#include "ascii.h"

uint32 ASCII::write(int cp, byte buf[]) const {
  if (cp < 0) {
    return 0;
  }
  else if (cp < 0x100) {
    buf[0] = cp;
    return 1;
  }
  else {
    return 0;
  }
}

void ASCII::write(const UnicodeSet& uset, NFA& g, Fragment& frag) const {
  const NFA::VertexDescriptor v = g.addVertex();
  g[v].Trans = g.TransFac->getSmallest(uset); // & [0x00,0xFF]
  frag.InList.push_back(v);
  frag.OutList.emplace_back(v, 0);
}
