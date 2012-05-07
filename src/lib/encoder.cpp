#include "encoder.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include <boost/iterator/filter_iterator.hpp>

uint32 findInitialSegment(NFA::VertexDescriptor& head, const byte* buf, const size_t blen, const NFA& g, const Fragment& frag) {
  ByteSet bs;

  // find a match for byte 0
  const auto ii = std::find_if(
    frag.InList.begin(),
    frag.InList.end(),
    [&](NFA::VertexDescriptor v) {
      bs.reset();
      g[v].Trans->getBits(bs);
      return bs.test(buf[0]) && bs.count() == 1;
    }
  );

  if (ii == frag.InList.end()) {
    // matching intial segment is empty
    return 0;
  }

  head = *ii;

  // find a match for subsequent bytes
  NFA::VertexDescriptor tail = 0;
  for (size_t b = 1; b < blen; ++b) {
    const uint32 odeg = g.outDegree(head);
    for (uint32 e = 0; e < odeg; ++e) {
      tail = g.outVertex(head, e);
      bs.reset();
      g[tail].Trans->getBits(bs);
      if (bs.test(buf[b]) && bs.count() == 1) {
        break;
      }
      tail = 0;
    }

    if (tail) {
      head = tail;
    }
    else {
      return b;
    }
  }

  return blen;
}

uint32 findTerminalSegment(NFA::VertexDescriptor& tail, const byte* buf, const size_t blen, const NFA& g, const Fragment& frag) {
  ByteSet bs;

  // find a match for the last byte
  const auto oi = std::find_if(
    frag.OutList.begin(), frag.OutList.end(),
    [&](const std::pair<NFA::VertexDescriptor,uint32>& p) {
      bs.reset();
      g[p.first].Trans->getBits(bs);
      return bs.test(buf[blen-1]) && bs.count() == 1;
    }
  );

  if (oi == frag.OutList.end()) {
    // matching final segment is empty
    return blen;
  }

  tail = oi->first;

  // find a match for previous bytes
  NFA::VertexDescriptor head = 0;

  for (size_t b = 1; b < blen + 1; ++b) {
    const uint32 ideg = g.inDegree(tail);
    for (uint32 e = 0; e < ideg; ++e) {
      head = g.inVertex(tail, e);
      bs.reset();
      g[head].Trans->getBits(bs);
      if (bs.test(buf[blen-b]) && bs.count() == 1) {
        break;
      }
      head = 0;
    }

    if (head) {
      tail = head;
    }
    else {
      return blen-b;
    }
  }

  return 0;
}

std::ostream& operator<<(std::ostream& out, const ByteSet& bs) {
  out << '[';
  uint32 low = 256;
  bool first = true;
  for (uint32 i = 0; i < 256; ++i) {
    if (bs.test(i)) {
      if (low > 255) {
        if (!first) {
          out << ',';
        }
        out << std::setfill('0') << std::setw(2) << i;
        low = i;
        first = false;
      }
    }
    else if (low < 256) {
      if ((i-1) > low) {
        out << '-' << std::setfill('0') << std::setw(2) << (i-1);
      }
      low = 256;
    }
  }
  out << ']';
  return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<ByteSet>& v) {
  std::copy(v.begin(), v.end(), std::ostream_iterator<ByteSet>(out, " "));
  return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<ByteSet>>& v) {
  out << std::hex;
  std::copy(
    v.begin(), v.end(), std::ostream_iterator<std::vector<ByteSet>>(out, "\n")
  );
  out << std::dec;
  return out;
}

bool mismatch_except_at(std::vector<ByteSet>::size_type n,
                        const std::vector<ByteSet>& a,
                        const std::vector<ByteSet>& b)
{
  // a mismatches b (except at position n) if:
  //  * a and b are different lengths, or
  //  * the leading segments of a and b (if any) before n differ, or
  //  * the trailing segments of a and b (if any) after n differ
  return
    a.size() != b.size() ||
    (a.size() > n+1 && !std::equal(a.begin(), a.end()-n-1, b.begin())) ||
    (n > 0 && !std::equal(a.end()-n, a.end(), b.end()-n));
}

struct Skip {
  Skip(): count(0), skip(0) {}

  Skip(uint32 s): count(0), skip(s) {}

  template <typename T>
  bool operator()(const T&) { return count++ != skip; }

  uint32 count, skip;
};

void Encoder::write(const UnicodeSet& uset, NFA& g, Fragment& frag) const {
  frag.InList.clear();
  frag.OutList.clear();

  std::unique_ptr<byte[]> buf(new byte[maxByteLength()]);

  std::vector<std::vector<ByteSet>> va, vb, vo;

  // collect the encodings
  for (const UnicodeSet::range& r : uset) {
    const uint32 l = r.first, h = r.second;
    for (uint32 cp = l; cp < h; ++cp) {
      const uint32 len = write(cp, buf.get());
      if (len == 0) {
        // cp is invalid, skip it
        continue;
      }

      va.emplace_back(len);
      for (uint32 i = 0; i < len; ++i) {
        va.back()[i].set(buf[i]);
      }
    }
  }

  // collapse ranges
  const uint32 mlen = maxByteLength();
  for (uint32 n = 0; n < mlen; ++n) {
    // sort encodings by length, then lexicographically, skipping position n
    std::sort(va.begin(), va.end(),
      [=](const std::vector<ByteSet>& a, const std::vector<ByteSet>& b) {
        return a.size() < b.size() || (a.size() == b.size() &&
          std::lexicographical_compare(
            boost::make_filter_iterator(Skip(a.size()-n-1), a.begin(), a.end()),
            boost::make_filter_iterator(Skip(a.size()-n-1), a.end(), a.end()),
            boost::make_filter_iterator(Skip(a.size()-n-1), b.begin(), b.end()),
            boost::make_filter_iterator(Skip(a.size()-n-1), b.end(), b.end())
          )
        );
      }
    );

    for (auto i = va.begin(); i != va.end(); ) {
      // find the limit of encodings matching i everywhere except position n
      auto j = std::find_if(i, va.end(),
        [=](const std::vector<ByteSet>& b) {
          return mismatch_except_at(n, *i, b);
        }
      );

      // collapse the range from i to j
      std::vector<ByteSet>& v = *i;
      for (++i; i != j; ++i) {
        v[v.size()-n-1] |= (*i)[i->size()-n-1];
      }

      (n == v.size() - 1 ? vo : vb).push_back(std::move(v));
    }

    va.swap(vb);
    vb.clear();
  }

//std::cerr << vo << std::endl;

  ByteSet bs;

  // create a graph from the collapsed ranges
  for (const std::vector<ByteSet>& enc : vo) {
    NFA::VertexDescriptor head, tail;

    // leading vertex
    tail = g.addVertex();
    g[tail].Trans = g.TransFac->getSmallest(enc[0]);
    frag.InList.push_back(tail);

    const uint32 elen = enc.size();
    if (elen > 1) {
      // middle vertices
      for (uint32 i = 1; i < elen-1; ++i) {
        head = tail;
        tail = g.addVertex();
        g[tail].Trans = g.TransFac->getSmallest(enc[i]);
        g.addEdge(head, tail);
      }

      // trailing vertex
      head = tail;

      // find a match for the last byte
      const auto oi = std::find_if(
        frag.OutList.begin(), frag.OutList.end(),
        [&](const std::pair<NFA::VertexDescriptor,uint32>& p) {
          bs.reset();
          g[p.first].Trans->getBits(bs);
          return bs == enc[elen-1];
        }
      );

      if (oi == frag.OutList.end()) {
        // no match
        tail = g.addVertex();
        g[tail].Trans = g.TransFac->getSmallest(enc[elen-1]);
        frag.OutList.emplace_back(tail, 0);
      }
      else {
        tail = oi->first;
      }

      g.addEdge(head, tail);
    }
    else {
      frag.OutList.emplace_back(tail, 0);
    }
  }

/*
  std::unique_ptr<byte[]> buf(new byte[maxByteLength() + 20]);
  ByteSet bs;

  for (const UnicodeSet::range& r : uset) {
    const uint32 l = r.first, h = r.second;
    for (uint32 cp = l; cp < h; ++cp) {
      const uint32 len = write(cp, buf.get());
      if (len == 0) {
        // cp is invalid, skip it
        continue;
      }

      NFA::VertexDescriptor iend = 0;

      // find a matching leading segment
      uint32 ipos = findInitialSegment(iend, buf.get(), len, g, frag);

      NFA::VertexDescriptor head = iend, tail;

      if (ipos == len - 1) {
        if (iend) {
          if (g.outDegree(head) > 0) {
            tail = g.outVertex(head, 0);
            bs.reset();
            g[tail].Trans->getBits(bs);
            bs.set(buf[ipos]);

            ByteSet obs;
            const auto oi = std::find_if(
              frag.OutList.begin(),
              frag.OutList.end(),
              [&](const std::pair<NFA::VertexDescriptor,uint32>& p) {
                obs.reset();
                g[p.first].Trans->getBits(obs);
                return bs == obs;
              }
            );

            if (oi == frag.OutList.end()) {
              g[tail].Trans = g.TransFac->getByteSet(bs);
            }
            else {
              tail = oi->first;
              g.addEdge(head, tail);

              tail = g.outVertex(head, 0);
              if (g.inDegree(tail) > 1) {
                g.removeEdge(g.outEdge(head, 0));
              }
              else {
                std::pair<NFA::VertexDescriptor,uint32> p(tail, 0);
                frag.OutList.erase(
                  std::remove(frag.OutList.begin(), frag.OutList.end(), p)
                );
                g.removeVertex(tail);
              }
            }
          }
          else {
            tail = g.addVertex();
            g[tail].Trans = g.TransFac->getLit(buf[ipos]);
            g.addEdge(head, tail);
            frag.OutList.emplace_back(tail, 0);
          }
        }
        else {
          const auto ii = std::find_if(
            frag.InList.begin(),
            frag.InList.end(),
            [&](NFA::VertexDescriptor v) {
              return g.outDegree(v) == 0;
            }
          );

          if (ii == frag.InList.end()) {
            tail = g.addVertex();
            g[tail].Trans = g.TransFac->getLit(buf[ipos]);
            frag.InList.push_back(tail);
            frag.OutList.emplace_back(tail, 0);
          }
          else {
            tail = *ii;
            bs.reset();
            g[tail].Trans->getBits(bs);
            bs.set(buf[ipos]);
            g[tail].Trans = g.TransFac->getByteSet(bs);
          }
        }
      }
      else {
        // find a matching trailing segment
        NFA::VertexDescriptor tbeg = 0;
        const uint32 tpos = findTerminalSegment(tbeg, buf.get(), len, g, frag);

        for ( ; ipos < tpos; ++ipos) {
          tail = g.addVertex();
          g[tail].Trans = g.TransFac->getLit(buf[ipos]);

          if (ipos == 0) {
            frag.InList.push_back(tail);
          }

          if (ipos == len - 1) {
            frag.OutList.emplace_back(tail, 0);
          }

          if (head) {
            g.addEdge(head, tail);
          }

          head = tail;
        }

        if (tpos < len) {
          g.addEdge(head, tbeg);
        }
      }
    }
  }
*/
}
