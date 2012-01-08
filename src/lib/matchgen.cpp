#include "basic.h"
#include "matchgen.h"

#include <iostream>
#include <set>
#include <stack>

struct Info { 
  Graph::vertex v;
  std::set<Graph::vertex> seen;
  std::string m;
};

void matchgen(const Graph& g, std::vector<std::string>& matches) {
  std::stack<Info> stack;
  Info i;
  i.v = 0;
  i.seen.insert(0);
  stack.push(i);

  ByteSet bs;

  while (!stack.empty()) {
    Info pi = stack.top();
    stack.pop();    
    Graph::vertex v = pi.v;
    std::string m(pi.m);
    std::set<Graph::vertex> seen(pi.seen);

    if (g[v] && g[v]->IsMatch) {
      std::cout << m << std::endl;
    }

    for (uint32 i = 0; i < g.outDegree(v); ++i) {
      Graph::vertex c = g.outVertex(v, i);

      if (pi.seen.find(c) != pi.seen.end()) {
        continue;
      }

      bs.reset();
      g[c]->getBits(bs);

      for (uint32 b = 0; b < 256; ++b) {
        if (bs[b]) {
          Info ci;
          ci.v = c;
          ci.m = m + (char) b;
          ci.seen = seen;
          ci.seen.insert(c);
          stack.push(ci);
          break;
        }
      }
    }
  }
}
