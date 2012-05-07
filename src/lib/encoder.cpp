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
        bs.reset();
        g[p.first].Trans->getBits(bs);
        return bs == enc[b];
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
        bs.reset();
        g[head].Trans->getBits(bs);
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
