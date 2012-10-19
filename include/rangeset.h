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

#pragma once

#include "basic.h"

#include <algorithm>
#include <bitset>
#include <iterator>
#include <initializer_list>
#include <vector>

#include <boost/iterator/iterator_facade.hpp>

// TODO: ensure T is unsigned
// TODO: ensure N is appropriate

template <typename T, T N>
class RangeSet {
private:
  typedef typename std::vector<T>::iterator internal_iterator;
  typedef typename std::vector<T>::const_iterator const_internal_iterator;

public:
  typedef typename std::vector<T>::size_type size_type;
  typedef std::pair<T,T> range;

  RangeSet() {}

  RangeSet(T first, T last): vec{first, last} {}

  RangeSet(T val): vec{val, val+1} {}

  RangeSet(std::initializer_list<T> init) {
    vec.reserve(2*init.size());
    for (const T& val : init) {
      insert(val, val+1);
    }
  }

  RangeSet(std::initializer_list<range> init) {
    vec.reserve(2*init.size());
    for (const range& r : init) {
      insert(r);
    }
  }

  template <size_t BN>
  RangeSet(const std::bitset<BN>& b) {
    static_assert(
      BN <= N,
      "std::bitset is larger than the RangeSet constructed from it"
    );

    for (unsigned int i = 0; i < BN; ++i) {
      if (b[i]) {
        unsigned int j = i + 1;
        for ( ; j < BN; ++j) {
          if (!b[j]) {
            vec.insert(vec.end(), { i, j });
            break;
          }
        }
        if (j == N) {
          vec.insert(vec.end(), { i, j });
        }

        i = j;
      }
    }
  }

  bool operator==(const RangeSet<T,N>& r) const {
    return vec == r.vec;
  }

  bool operator!=(const RangeSet<T,N>& r) const {
    return vec != r.vec;
  }

  bool operator==(const std::bitset<N>& b) const {
    for (T i = 0; i < N; ++i) {
      if (test(i) != b.test(i)) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const std::bitset<N>& b) const {
    return !(*this == b);
  }

  bool operator<(const RangeSet<T,N>& r) const {
    return vec < r.vec;
  }

  bool operator>(const RangeSet<T,N>& r) const {
    return vec > r.vec;
  }

  bool operator<=(const RangeSet<T,N>& r) const {
    return vec <= r.vec;
  }

  bool operator>=(const RangeSet<T,N>& r) const {
    return vec >= r.vec;
  }

  RangeSet<T,N>& operator&=(const RangeSet<T,N>& r) {
    *this = ~*this | ~r;
    flip();
    return *this;
  }

  RangeSet<T,N>& operator|=(const RangeSet<T,N>& r) {
    const const_internal_iterator end(r.vec.end());
    for (const_internal_iterator i(r.vec.begin()); i != end; i += 2) {
      insert(*i, *(i+1));
    }
    return *this;
  }

  RangeSet<T,N>& operator^=(const RangeSet<T,N>& r) {
    *this = (*this & ~r) | (~*this & r);
    return *this;
  }

  RangeSet<T,N> operator~() const {
    RangeSet<T,N> r(*this);
    r.flip();
    return r;
  }

  RangeSet<T,N> operator&(const RangeSet<T,N>& r) const {
    RangeSet<T,N> s(*this);
    return s &= r;
  }

  RangeSet<T,N> operator|(const RangeSet<T,N>& r) const {
    RangeSet<T,N> s(*this);
    return s |= r;
  }

  RangeSet<T,N> operator^(const RangeSet<T,N>& r) const {
    RangeSet<T,N> s(*this);
    return s ^= r;
  }

  bool test(size_type pos) const {
    const const_internal_iterator i(std::lower_bound(vec.begin(), vec.end(), pos));
    if (i == vec.end()) {
      return false;
    }
    else if ((i - vec.begin()) & 1) {
      // [*(i-1),*i)
      return pos < *i;
    }
    else {
      // [*i,*(i+1))
      return pos == *i;
    }
  }

  class reference {
  public:
    reference(RangeSet<T,N>& r, size_type i): rs(r), pos(i) {}

    // for b[i] = value
    reference& operator=(bool value) {
      rs.set(pos, value);
      return *this;
    }

    // for b[i] = b[j]
    reference& operator=(const reference& other) {
      rs.set(pos, other.rs.test(other.pos));
      return *this;
    }

    bool operator~() const {
      return !rs.test(pos);
    }

    // for value = b[i]
    operator bool() const {
      return rs.test(pos);
    }

    // for b[i].flip()
    reference& flip() {
      rs.flip(pos);
    }

  private:
    RangeSet<T,N>& rs;
    size_type pos;
  };

  reference operator[](size_type pos) {
    return reference(*this, pos);
  }

  bool operator[](size_type pos) const {
    return test(pos);
  }

  bool any() const {
    return !vec.empty();
  }

  bool all() const {
    return vec.size() == 2 && vec.front() == 0 && vec.back() == N;
  }

  bool none() const {
    return vec.empty();
  }

  size_type count() const {
    size_type c = 0;
    const const_internal_iterator end(vec.end());
    for (const_internal_iterator i(vec.begin()); i != end; i += 2) {
      c += *(i+1) - *i;
    }
    return c;
  }

  class const_range_iterator:
    public boost::iterator_facade<
      const_range_iterator,
      range const,
      std::random_access_iterator_tag,
      range
    >
  {
  public:
    const_range_iterator(): i() {}

    const_range_iterator(const const_internal_iterator& vi): i(vi) {}

    typedef typename boost::iterator_facade<
      const_range_iterator,
      range const,
      std::random_access_iterator_tag,
      range
    >::difference_type difference_type;

  private:
    friend class boost::iterator_core_access;

    void increment() { i += 2; }

    void decrement() { i -= 2; }

    void advance(difference_type n) { i += 2*n; }

    difference_type distance_to(const const_range_iterator& o) const {
      return (o.i - i) / 2;
    }

    bool equal(const const_range_iterator& o) const { return o.i == i; }

    range dereference() const { return std::make_pair(*i, *(i+1)); }

    const_internal_iterator i;
  };

  typedef const_range_iterator const_iterator;
  typedef std::reverse_iterator<const_range_iterator> const_reverse_iterator;

  const_iterator begin() const {
    return const_iterator(vec.begin());
  }

  const_iterator cbegin() const {
    return const_iterator(vec.cbegin());
  }

  const_iterator end() const {
    return const_iterator(vec.end());
  }

  const_iterator cend() const {
    return const_iterator(vec.cend());
  }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(vec.rbegin());
  }

  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(vec.crbegin());
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(vec.rend());
  }

  const_reverse_iterator crend() const {
    return const_reverse_iterator(vec.crend());
  }

  size_type size() const {
    return N;
  }

  void set() {
    vec = { 0, N };
  }

  void set(size_type pos, bool value = true) {
    if (value) {
      insert(pos, pos + 1);
    }
    else {
      erase(pos, pos + 1);
    }
  }

  void reset() {
    vec.clear();
  }

  void reset(size_type pos) {
    set(pos, false);
  }

  void flip() {
    if (vec.empty()) {
      set();
    }
    else {
      if (vec.front() == 0) {
        vec.erase(vec.begin());
      }
      else {
        vec.insert(vec.begin(), 0);
      }

      if (vec.back() == N) {
        vec.pop_back();
      }
      else {
        vec.push_back(N);
      }
    }
  }

  void flip(size_type pos) {
    set(pos, !test(pos));
  }

  void insert(const range& r) {
    insert(r.first, r.second);
  }

  void insert(const T& first, const T& last) {
    if (first == last) {
      return;
    }

    internal_iterator l(std::lower_bound(vec.begin(), vec.end(), first));
    internal_iterator u(std::upper_bound(l, vec.end(), last));

    if (l == vec.end() || u == vec.begin()) {
      vec.insert(l, { first, last });
    }
    else {
      bool insertFirst = false, insertLast = false;

      if ((l - vec.begin()) & 1) {
        // the insertion point for first is an endpoint
      }
      else {
        // the insertion point for first is a startpoint
        // insert first at l
        insertFirst = true;
      }

      if ((u - vec.begin()) & 1) {
        // the insertion point for last is an endpoint
      }
      else {
        // the insertion point for last is a startpoint
        // insert last at u
        insertLast = true;
      }

      l = vec.erase(l, u);

      if (insertLast) {
        l = vec.insert(l, last);
      }

      if (insertFirst) {
        vec.insert(l, first);
      }
    }
  }

  void erase(const T& first, const T& last) {
    flip();
    insert(first, last);
    flip();
  }

private:
  std::vector<T> vec;
};

template <typename T, T N>
bool operator==(const std::bitset<N>& b, const RangeSet<T,N>& r) {
  return r == b;
}

template <typename T, T N>
bool operator!=(const std::bitset<N>& b, const RangeSet<T,N>& r) {
  return r != b;
}

template <typename T, T N>
std::ostream& operator<<(std::ostream& o, const RangeSet<T,N>& rs) {
  const typename RangeSet<T,N>::const_iterator end(rs.end());
  for (typename RangeSet<T,N>::const_iterator i(rs.begin()); i != end; ++i) {
    o << '[' << std::hex << i->first << ',' << i->second << std::dec << ") ";
  }
  return o;
}

typedef RangeSet<uint32,0x110000> UnicodeSet;
