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

bool equal_except_at(std::vector<ByteSet>::size_type n,
                     const std::vector<ByteSet>& a,
                     const std::vector<ByteSet>& b)
{
  // a and b are equal everwhere, disregarding position n
  return
    (a.size() <= n+1 || std::equal(a.begin(), a.end()-n-1, b.begin())) &&
    (n == 0 || std::equal(a.end()-n, a.end(), b.end()-n));
}

template <typename Itr>
class skip_iterator:
  public std::iterator<std::forward_iterator_tag, typename Itr::value_type>
{
public:
  skip_iterator(): inner(), count(1), skip(0) { ++inner; }

  skip_iterator(Itr i, uint32 c, uint32 s): inner(i), count(c), skip(s) {
    if (skip == count) { ++inner; ++count; }
  }

  skip_iterator(const skip_iterator& i):
    inner(i.inner), count(i.count), skip(i.skip) {}

  bool operator==(const skip_iterator& i) const {
    return inner == i.inner;
  }

  bool operator!=(const skip_iterator& i) const {
    return inner != i.inner;
  }

  typename Itr::reference operator*() const {
    return *inner;
  }

  skip_iterator& operator++() {
    inner += 1 + ((++count == skip));
    return *this;
  }

  skip_iterator operator++(int) {
    skip_iterator ret(*this);
    operator++();
    return ret;
  }

private:
  Itr inner;
  uint32 count, skip;
};

template <typename Itr>
skip_iterator<Itr> make_skip_iterator(Itr i, uint32 count, uint32 skip) {
  return skip_iterator<Itr>(i, count, skip);
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
      const uint32 spos = elen-n-1;

      // sort encodings lexicographically, skipping position n from the end
      std::sort(vi, sb,
        [=](const std::vector<ByteSet>& a, const std::vector<ByteSet>& b) {
          return std::lexicographical_compare(
            make_skip_iterator(a.begin(),  0, spos),
            make_skip_iterator(a.end(), elen, spos),
            make_skip_iterator(b.begin(),  0, spos),
            make_skip_iterator(b.end(), elen, spos)
          );
        }
      );

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
