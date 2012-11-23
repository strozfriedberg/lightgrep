/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "basic.h"
#include "matchgen.h"
#include "automata.h"

#include <random>
#include <vector>

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

  std::uniform_int_distribution<uint32_t> uout(0, bytes.size() - 1);
  return bytes[uout(rng)];
}

void matchgen(const NFA& g, std::set<std::string>& matches,
              const uint32_t maxMatches, const uint32_t maxLoops) {
  if (maxMatches == 0) {
    return;
  }

  std::default_random_engine rng;
  std::bernoulli_distribution extend(0.75);

  std::vector<NFA::VertexDescriptor> seen, path;

  const ByteSet alnum{{'0', '9'+1}, {'A', 'Z'+1}, {'a', 'z'+1}},
                punct{{'!', '/'+1}, {':', '@'+1}, {'[', '`'+1}, {'{', '~'+1}};
  ByteSet allowed;

  for (uint32_t i = 0; i < maxMatches; ++i) {
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
          const NFA::NeighborList outs(g.outVertices(v));
          if (outs.end() == std::find_if(outs.begin(), outs.end(),
            [&](const NFA::VertexDescriptor w) {
              return seen[w] < maxLoops;
            })
          ) {
            break;
          }
        }
        else {
          break;
        }
      }

      // find a successor
      uint32_t scount = 0;
      NFA::VertexDescriptor s = 0;
      for (const NFA::VertexDescriptor w : g.outVertices(v)) {
        if (seen[w] < maxLoops) {
          // Successively replacing the chosen element with the nth
          // element in a series with probability 1/n is the same as
          // choosing uniformly over the whole series, but permits it
          // to be done in one pass when the maximum n is unknown
          // beforehand.
          //
          // This is a modification of that, where we reduce the
          // probability of replacement for edges which have no
          // (ASCII) alphanumeric or printable bytes.
          double p = 1.0/++scount;

          if (scount > 1) {
            g[w].Trans->getBytes(allowed);
            if ((alnum & allowed).none()) {
              p /= 2.0;

              if ((punct & allowed).none()) {
                p /= 8.0;
              }
            }
          }

          std::bernoulli_distribution change(p);
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
