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

template<class ArrayType>
void addRange(std::vector<byte>& bytes, const ArrayType& ranges, const ByteSet& allowed) {
  for (auto range: ranges) {
    for (byte b = range.first; b <= range.second; ++b) {
      if (allowed.test(b)) {
        bytes.push_back(b);
      }
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

template <class Element>
const Element& chooseRandom(const std::vector<Element>& c, std::default_random_engine& rng) {
  std::uniform_int_distribution<uint32> uout(0, c.size() - 1);
  return c[uout(rng)];
}

byte chooseByte(const ByteSet& allowed, std::default_random_engine& rng) {
  std::vector<byte> bytes;

  // can we select alphanumeric?
  addRange(bytes, {std::make_pair('0', '9'), std::make_pair('A', 'Z'),
                   std::make_pair('a', 'z')}, allowed);

  if (!bytes.empty()) {
    return chooseRandom(bytes, rng);
  }
  else {
    // can we select other printable characters?
    addRange(bytes, {std::make_pair('!', '/'), std::make_pair(':', '@'),
                    std::make_pair('[', '`'), std::make_pair('{', '~')}, allowed);

    if (!bytes.empty()) {
      return chooseRandom(bytes, rng);
    }
    else {
      // no printable characters in this range
      addRange(bytes, {std::make_pair(0, ' ')}, allowed);

      // FIXME: oddly, if I replace the below loop with
      // addRange(bytes, 0x7f, 0xff, allowed) then
      // ./lightgrep.exe -c samp -i -e UTF-8 -p "[a-z\d]{3,5}" 10
      // hangs.
      for (uint32 j = 0x7F; j <= 0xFF; ++j) {
        if (allowed.test(j)) {
          bytes.push_back(j);
        }
      }
      return chooseRandom(bytes, rng);
    }
  }
}

void matchgen(const NFA& g, std::set<std::string>& matches, uint32 maxMatches, uint32 maxLoops) {
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

    bool done = false;
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

      match += chooseByte(allowed, rng);

      if (g[v].IsMatch) {
        // check whether we could extend this match
        if (!checkForRoadLessTaken(g, seen, maxLoops, v)
          || umatch(rng)) // or can, but don't want to
        {
          // we can't extend the match, report it
          matches.insert(match);
          done = true;
        }
      }
    } while (!done);
  }
}
