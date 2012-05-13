#include "encoder.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

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

void Encoder::collectRanges(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& va) const {
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

  // sort encoding ranges by size
  std::sort(va.begin(), va.end(),
    [](const std::vector<ByteSet>& a, const std::vector<ByteSet>& b) {
      return a.size() < b.size();
    }
  );
}

struct EncodingRangeComparator {
  EncodingRangeComparator(uint32 l, uint32 s): len(l), skip(s) {}

  bool operator()(const std::vector<ByteSet>& a,
                  const std::vector<ByteSet>& b) const
  {
    // This is evil. We're taking advantage of the fact that std::vector
    // is laid out in a contiguous block, that ByteSet is just a block of
    // 32 bytes.
    const int pre = memcmp(a.data(), b.data(), skip*sizeof(ByteSet));
    return
      pre < 0 ? true :
      (pre > 0 ? false :
      memcmp(a.data()+skip+1, b.data()+skip+1, (len-skip)*sizeof(ByteSet)) < 0);
  }

  const uint32 len, skip;
};

bool equal_except_at(std::vector<ByteSet>::size_type n,
                     const std::vector<ByteSet>& a,
                     const std::vector<ByteSet>& b)
{
  // a and b are equal everwhere, disregarding position n
  return
    (a.size() <= n+1 || std::equal(a.begin(), a.end()-n-1, b.begin())) &&
    (n == 0 || std::equal(a.end()-n, a.end(), b.end()-n));
}

void Encoder::write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& vo) const {
  std::vector<std::vector<ByteSet>> va, vb;

  // collect the encodings
  collectRanges(uset, va);

  // collapse encodings
  const uint32 mlen = maxByteLength();
  for (uint32 n = 0; n < mlen; ++n) {
    for (auto vi = va.begin(); vi != va.end(); ) {
      // find next size boundary
      auto sb = std::adjacent_find(vi, va.end(),
        [](const std::vector<ByteSet>& a, const std::vector<ByteSet>& b) {
          return a.size() != b.size();
        }
      );
      if (sb != va.end()) {
        ++sb;
      }

      const uint32 elen = vi->size();

      // sort encodings lexicographically, skipping position n from the end
      std::sort(vi, sb, EncodingRangeComparator(elen, elen-n-1));

      // try collapsing each successive encoding, up to the size boundary
      while (vi != sb) {
        std::vector<ByteSet>& e = *vi;
        // collapse all the encodings matching v everywhere except position n
        for (++vi; vi != sb && equal_except_at(n, e, *vi); ++vi) {
          e[elen-n-1] |= (*vi)[elen-n-1];
        }

        // put this collapsed encoding in the output, if we've reached the
        // front, or in the work vector for the next round
        (n == elen - 1 ? vo : vb).push_back(std::move(e));
      }
    }

    va.swap(vb);
    vb.clear();
  }
}
