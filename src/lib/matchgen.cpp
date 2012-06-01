#include "basic.h"
#include "matchgen.h"

#include <iostream>
#include <random>
#include <tuple>

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

template <class RNG>
std::tuple<NFA::VertexDescriptor,byte> chooseRandomTarget(
  const NFA& g, const std::vector<uint32>& seen,
  const NFA::VertexDescriptor v, const uint32 maxLoops, RNG& rng)
{
  ByteSet bs;

  // collect all of the bytes from undervisited edges leaving v
  NFA::VertexDescriptor w;
  const uint32 odeg = g.outDegree(v);
  for (uint32 i = 0; i < odeg; ++i) {
    w = g.outVertex(v, i);
    if (seen[w] <= maxLoops) {
      g[w].Trans->orBytes(bs);
    }
  }

  // pick a byte
  const byte b = chooseByte(bs, rng);

  // then return the first undervisited neighbor of v reachable on that byte
  bs.reset();
  for (uint32 i = 0; i < odeg; ++i) {
    w = g.outVertex(v, i);
    if (seen[w] <= maxLoops && g[w].Trans->getBytes(bs).test(b)) {
      return std::make_tuple(w, b);
    }
  }

  // this cannot happen
  THROW_WITH_OUTPUT(
    std::logic_error,
    "byte value " << std::hex << (int) b << " not found!"
  );
}

void matchgen(const NFA& g, std::set<std::string>& matches,
              const uint32 maxMatches, const uint32 maxLoops) {
  if (maxMatches == 0) {
    return;
  }

  std::default_random_engine rng;
  std::bernoulli_distribution umatch(0.25);
  ByteSet allowed;
  std::vector<uint32> seen;

  for (uint32 i = 0; i < maxMatches; ++i) {
    NFA::VertexDescriptor v = 0;
    std::string match;

    seen.assign(g.verticesSize(), 0);

    for (;;) {
      // check that there is at least one out vertex not seen too often
      if (!checkForRoadLessTaken(g, seen, maxLoops, v)) {
        break;
      }

      // select a random neighbor and byte
      byte b;
      std::tie(v, b) = chooseRandomTarget(g, seen, v, maxLoops, rng);
      ++seen[v];
      match += b;

      if (g[v].IsMatch) {
        // check whether we could extend this match
        if (!checkForRoadLessTaken(g, seen, maxLoops, v)
            || umatch(rng)) // or can, but don't want to
        {
          // we can't extend the match, report it
          matches.insert(match);
          break;
        }
      }
    }
  }
}
