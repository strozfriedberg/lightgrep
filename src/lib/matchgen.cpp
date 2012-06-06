#include "basic.h"
#include "matchgen.h"

#include <iostream>
#include <random>
#include <stack>

void addRange(std::vector<byte>& bytes, std::initializer_list<std::pair<byte,byte>> ranges, const ByteSet& allowed) {
  for (auto range : ranges) {
    for (int b = range.first; b <= range.second; ++b) {
      if (allowed.test(b)) {
        bytes.push_back(b);
      }
    }
  }
}

template <class RNG>
byte chooseByte(const ByteSet& allowed, RNG& rng) {
  std::vector<byte> bytes;
  std::bernoulli_distribution more(0.25);

  // can we select alphanumeric?
  addRange(bytes, {{'0', '9'}, {'A', 'Z'}, {'a', 'z'}}, allowed);

  if (bytes.empty() || more(rng)) {
    // can we select other printable characters?
    addRange(bytes, {{'!', '/'}, {':', '@'}, {'[', '`'}, {'{', '~'}}, allowed);

    if (bytes.empty() || more(rng)) {
      // no visible characters in this range
      addRange(bytes, {{0, ' '}, {0x7F, 0xFF}}, allowed);
    }
  }

  std::uniform_int_distribution<uint32> uout(0, bytes.size() - 1);
  return bytes[uout(rng)];
}

void matchgen(const NFA& g, std::set<std::string>& matches,
              const uint32 maxMatches, const uint32 maxLoops) {
  if (maxMatches == 0) {
    return;
  }

  std::default_random_engine rng;
  std::bernoulli_distribution extend(0.50);

  std::vector<NFA::VertexDescriptor> seen, path;

  ByteSet allowed;

  for (uint32 i = 0; i < maxMatches; ++i) {
    NFA::VertexDescriptor v = 0;

    seen.assign(g.verticesSize(), 0);
    path.clear();

    for (;;) {
      // visit state v
      path.push_back(v);
      ++seen[v];

      // if we've reached a match state, produce a match
      if (g[v].IsMatch) {
        std::string match;
        for (const NFA::VertexDescriptor w : path) {
          // follow the path, writing the match as we go
          if (g[w].Trans) {
            g[w].Trans->getBytes(allowed);
            match += chooseByte(allowed, rng);
          }          
        }

        // report the match
        matches.insert(match);

        // should we try to extend the match?
        if (extend(rng)) {
          // are there any eligible successors?
          bool found = false;
          for (uint32 j = 0; j < g.outDegree(v); ++j) {
            const NFA::VertexDescriptor w = g.outVertex(v, j);
            if (seen[w] < maxLoops) {
              found = true;
              break;
            }
          }

          if (!found) {
            break;
          }
        }
        else {
          break;
        }
      }      

      // find a successor
      uint32 scount = 0;
      NFA::VertexDescriptor s = 0;
      for (uint32 j = 0; j < g.outDegree(v); ++j) {
        const NFA::VertexDescriptor w = g.outVertex(v, j);
        if (seen[w] < maxLoops) {
          // We don't know how many eligible successors there will be,
          // so we let the nth one we see replace the previously
          // selected one with probability 1/n. This gives us a uniform
          // distribution over all eligible successors and produces a
          // successor in a single pass.
          std::bernoulli_distribution change(1.0/++scount);
          if (change(rng)) {
            s = w;
          }
        }
      }

      if (scount == 0) {
        // backtrack if all successors exhausted
        path.pop_back();
        v = path.back();
      }
      else {
        // otherwise move on to s
        v = s;
      }
    }
  }
}
