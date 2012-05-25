#include "basic.h"
#include "matchgen.h"

#include <iostream>
#include <random>

bool checkForRoadLessTaken(const NFA& g, const std::vector<uint32>& seen,
                          const uint32 maxLoops, const NFA::VertexDescriptor v) {
  for (uint32 j = 0; j < g.outDegree(v); ++j) {
    if (seen[g.outVertex(v, j)] < maxLoops) {
      return true;
    }
  }
  return false;
}

void addRange(std::vector<byte>& bytes, byte begin, byte end, const ByteSet& allowed) {
  for (byte b = begin; b <= end; ++b) {
    if (allowed.test(b)) {
      bytes.push_back(b);
    }
  }
}

void matchgen(const NFA& g, std::set<std::string>& matches, uint32 maxMatches, uint32 maxLoops) {
  if (maxMatches == 0) {
    return;
  }

  std::default_random_engine rng;
  ByteSet bs;
  std::vector<uint32> seen;
  std::vector<byte> bytes;

  for (uint32 i = 0; i < maxMatches; ++i) {
    NFA::VertexDescriptor v = 0;
    std::string match;

    seen.assign(g.verticesSize(), 0);

    bool done = true;

    do {
      // check that there is at least one out vertex not seen too often
      if (!checkForRoadLessTaken(g, seen, maxLoops, v)) {
        break;
      }
      // select a random out vertex
      std::uniform_int_distribution<uint32> uout(0, g.outDegree(v) - 1);

      NFA::VertexDescriptor w;
      do {
        w = g.outVertex(v, uout(rng));
      } while (seen[w] > maxLoops);

      v = w; 
      ++seen[v];

      // select a random transition to that vertex
      bs.reset(); 
      g[v].Trans->getBytes(bs);
      bytes.clear();

      // can we select alphanumeric?
      addRange(bytes, '0', '9', bs);
      addRange(bytes, 'A', 'Z', bs);
      addRange(bytes, 'a', 'z', bs);

      if (!bytes.empty()) {
        std::uniform_int_distribution<std::vector<byte>::size_type> ubyte(0, bytes.size() - 1);
        match += bytes[ubyte(rng)];
      }
      else {
        bytes.clear();

        // can we select other printable characters?
        addRange(bytes, '!', '/', bs);
        addRange(bytes, ':', '@', bs);
        addRange(bytes, '[', '`', bs);
        addRange(bytes, '{', '~', bs);

        if (!bytes.empty()) {
          std::uniform_int_distribution<std::vector<byte>::size_type> ubyte(0, bytes.size() - 1);
          match += bytes[ubyte(rng)];
        }
        else {
          bytes.clear();

          // no printable characters in this range
          for (byte j = 0x00; j <= ' '; ++j) {
            if (bs.test(j)) {
              bytes.push_back(j);
            }
          }

          for (uint32 j = 0x7F; j <= 0xFF; ++j) {
            if (bs.test(j)) {
              bytes.push_back(j);
            }
          }

          std::uniform_int_distribution<std::vector<byte>::size_type> ubyte(0, bytes.size() - 1);
          match += bytes[ubyte(rng)];
        }
      }

      if (g[v].IsMatch) {
        done = true;

        // check whether we could extend this match
        for (uint32 j = 0; j < g.outDegree(v); ++j) {
          if (seen[g.outVertex(v, j)] < maxLoops) {
            done = false;
            break;
          }
        }

        if (done) {
          // we can't extend the match, report it
          matches.insert(match);
        }
        else {
          std::bernoulli_distribution umatch(0.25);
          if (umatch(rng)) {
            // we can extend the match, but don't want to
            matches.insert(match);
            done = true;
          }
        }
      }
      else {
        // no match, keep going
        done = false;
      }
    } while (!done);
  }
}
