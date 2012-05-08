#include "encoder.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include <boost/iterator/filter_iterator.hpp>

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

/*
struct EqualExceptAt {
  EqualExceptAt(uint32 i): n(i) {}

  template <typename T>
  bool operator()(const T& a, const T& b) {
    a.size() == b.size() &&
    (a.size() <= n+1 && !std::equal(a.begin(), a.end()-n-1, b.begin())) ||
    (n > 0 && !std::equal(a.end()-n, a.end(), b.end()-n));
  }
};
*/

bool mismatch_except_at(std::vector<ByteSet>::size_type n,
                        const std::vector<ByteSet>& a,
                        const std::vector<ByteSet>& b)
{
  // a mismatches b (except at position n) if:
  //  * a and b are different lengths, or
  //  * the prefixes of a and b before n differ, or
  //  * the suffixes of a and b after n differ
  return
    a.size() != b.size() ||
    (a.size() > n+1 && !std::equal(a.begin(), a.end()-n-1, b.begin())) ||
    (n > 0 && !std::equal(a.end()-n, a.end(), b.end()-n));
}

struct Skip {
  Skip(uint32 s): count(0), skip(s) {}

  template <typename T>
  bool operator()(const T&) { return count++ != skip; }

  uint32 count, skip;
};

void Encoder::write(const UnicodeSet& uset, NFA& g, Fragment& frag) const {
  frag.InList.clear();
  frag.OutList.clear();

  std::vector<std::vector<ByteSet>> va, vb, vo;

  // collect the encodings
  {
    std::unique_ptr<byte[]> cur(new byte[maxByteLength()]);
    std::unique_ptr<byte[]> prev(new byte[maxByteLength()]);

    uint32 clen, plen = 0;

    for (const UnicodeSet::range& r : uset) {
      const uint32 l = r.first, h = r.second;
      for (uint32 cp = l; cp < h; ++cp) {
        clen = write(cp, cur.get());
        if (clen == 0) {
          // cp is invalid, skip it
          continue;
        }

        if (clen == plen &&
            std::equal(cur.get(), cur.get()+clen-1, prev.get())) {
          // join the previous cp if we are the same up to the last byte
          va.back().back().set(cur[clen-1]);
        }
        else {
          // otherwise add a new encoding to the list
          va.emplace_back(clen);
          for (uint32 i = 0; i < clen; ++i) {
            va.back()[i].set(cur[i]);
          }

          prev.swap(cur);
          plen = clen;
        }
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

  ByteSet bs;

  // create a graph from the collapsed ranges
  for (const std::vector<ByteSet>& enc : vo) {
    NFA::VertexDescriptor head, tail;

    //
    // find a matching suffix
    //

    int32 b = enc.size()-1;

    // find a match for the last transition
    const auto oi = std::find_if(
      frag.OutList.begin(), frag.OutList.end(),
      [&](const std::pair<NFA::VertexDescriptor,uint32>& p) {
        return g[p.first].Trans->getBytes(bs) == enc[b];
      }
    );

    if (oi != frag.OutList.end()) {
      // match, use this tail
      tail = oi->first;
    }
    else {
      // build a new tail
      tail = g.addVertex();
      g[tail].Trans = g.TransFac->getSmallest(enc[b]);
      frag.OutList.emplace_back(tail, 0);
    }

    // walk backwards until a transition mismatch
    for (--b; b >= 0; --b) {
      head = 0;
      const uint32 ideg = g.inDegree(tail);
      for (uint32 i = 0; i < ideg; ++i) {
        head = g.inVertex(tail, i);
        g[head].Trans->getBytes(bs);
        if (bs == enc[b]) {
          tail = head;
          break;
        }
        head = 0;
      }

      if (!head) {
        // tail is as far back as we can go
        break;
      }
    }

    // build previous vertices
    for ( ; b >= 0; --b) {
      head = g.addVertex();
      g[head].Trans = g.TransFac->getSmallest(enc[b]);
      g.addEdge(head, tail);
      tail = head;
    }

    frag.InList.push_back(tail);
  }
}
