#include "basic.h"
#include "matchgen.h"
#include "unparser.h"

#include <stack>

struct Info { 
  NFA::VertexDescriptor v;
  std::vector<uint32> seen;
  std::string m;
};

void matchgen(const NFA& g, std::set<std::string>& matches, uint32 max_matches, uint32 max_loops) {
  if (max_matches == 0) {
    return;
  }

  std::stack<Info> stack;
  Info i;
  i.v = 0;
  i.seen.assign(g.verticesSize(), 0);
  stack.push(i);

  ByteSet bs;

  while (!stack.empty()) {
    Info pi = stack.top();
    stack.pop();    
    NFA::VertexDescriptor v = pi.v;
    std::string& m(pi.m);
    std::vector<uint32>& seen(pi.seen);

    if (g[v].Trans && g[v].Trans->IsMatch) {
      matches.insert(m);
      if (matches.size() >= max_matches) {
        return;
      }
    }

    const uint32 odeg = g.outDegree(v);
    for (uint32 i = 0; i < odeg; ++i) {
      NFA::VertexDescriptor c = g.outVertex(v, odeg - i - 1);

      if (pi.seen[c] > max_loops) {
        continue;
      }

      bs.reset();
      g[c].Trans->getBits(bs);

      for (uint32 b = 0; b < 256; ++b) {
        if (bs[b]) {
          Info ci;
          ci.v = c;
          ci.m = m + byteToLiteralString(b);
          ci.seen = seen;
          ++ci.seen[c];
          stack.push(ci);
          break;
        }
      }
    }
  }
}
