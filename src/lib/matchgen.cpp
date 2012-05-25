#include "basic.h"
#include "matchgen.h"

#include <iostream>
#include <random>

bool checkForRoadLessTaken(const NFA& g, const std::vector<uint32>& seen,
                          const uint32 maxLoops, const NFA::VertexDescriptor v)
{
  for (uint32 i = 0; i < g.outDegree(v); ++i) {
    if (seen[g.outVertex(v, i)] < maxLoops) {
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

NFA::VertexDescriptor chooseRandomTarget(const NFA& g, const std::vector<uint32>& seen,
                          NFA::VertexDescriptor v, uint32 maxLoops, std::default_random_engine& rng)
{
  std::uniform_int_distribution<uint32> uout(0, g.outDegree(v) - 1);
  NFA::VertexDescriptor w;
  do {
    w = g.outVertex(v, uout(rng));
  } while (seen[w] > maxLoops);
  return w;
}

void matchgen(const NFA& g, std::set<std::string>& matches, uint32 maxMatches, uint32 maxLoops) {
  if (maxMatches == 0) {
    return;
  }
  std::default_random_engine rng;
  ByteSet allowed;
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
      v = chooseRandomTarget(g, seen, v, maxLoops, rng);
      ++seen[v];

      // select a random transition to that vertex
      allowed.reset(); 
      g[v].Trans->getBytes(allowed);
      bytes.clear();

      // can we select alphanumeric?
      addRange(bytes, '0', '9', allowed);
      addRange(bytes, 'A', 'Z', allowed);
      addRange(bytes, 'a', 'z', allowed);

      if (!bytes.empty()) {
        std::uniform_int_distribution<std::vector<byte>::size_type> ubyte(0, bytes.size() - 1);
        match += bytes[ubyte(rng)];
      }
      else {
        bytes.clear();

        // can we select other printable characters?
        addRange(bytes, '!', '/', allowed);
        addRange(bytes, ':', '@', allowed);
        addRange(bytes, '[', '`', allowed);
        addRange(bytes, '{', '~', allowed);

        if (!bytes.empty()) {
          std::uniform_int_distribution<std::vector<byte>::size_type> ubyte(0, bytes.size() - 1);
          match += bytes[ubyte(rng)];
        }
        else {
          bytes.clear();

          // no printable characters in this range
          addRange(bytes, 0, ' ', allowed);
          // FIXME: oddly, if I replace the below loop with
          // addRange(bytes, 0x7f, 0xff, allowed) then
          // ./lightgrep.exe -c samp -i -e UTF-8 -p "[a-z\d]{3,5}" 10
          // hangs.
          for (uint32 j = 0x7F; j <= 0xFF; ++j) {
            if (allowed.test(j)) {
              bytes.push_back(j);
            }
          }
          std::uniform_int_distribution<std::vector<byte>::size_type> ubyte(0, bytes.size() - 1);
          match += bytes[ubyte(rng)];
        }
      }

      if (g[v].IsMatch) {
        // check whether we could extend this match
        if (!checkForRoadLessTaken(g, seen, maxLoops, v)) {
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
