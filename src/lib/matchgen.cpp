#include "basic.h"
#include "matchgen.h"
#include "unparser.h"

#include <stack>

struct Info { 
  Graph::vertex v;
  std::vector<uint32> seen;
  std::string m;
};

void matchgen(const Graph& g, std::set<std::string>& matches, uint32 max_loops, uint32 max_matches) {
  if (max_matches == 0) {
    return;
  }

  std::stack<Info> stack;
  Info i;
  i.v = 0;
  i.seen.assign(g.numVertices(), 0);
  stack.push(i);

  ByteSet bs;

  while (!stack.empty()) {
    Info pi = stack.top();
    stack.pop();    
    Graph::vertex v = pi.v;
    std::string& m(pi.m);
    std::vector<uint32>& seen(pi.seen);

    if (g[v] && g[v]->IsMatch) {
      matches.insert(m);
      if (matches.size() >= max_matches) {
        return;
      }
    }

    const uint32 odeg = g.outDegree(v);
    for (uint32 i = 0; i < odeg; ++i) {
      Graph::vertex c = g.outVertex(v, odeg - i - 1);

      if (pi.seen[c] > max_loops) {
        continue;
      }

      bs.reset();
      g[c]->getBits(bs);

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
