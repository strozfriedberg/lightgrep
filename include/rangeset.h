#pragma once

#include <algorithm>
#include <bitset>
#include <iterator>
#include <initializer_list>
#include <vector>

// TODO: ensure T is unsigned
// TODO: ensure N is appropriate

template <typename T, T N>
class RangeSet {

public:
  typedef typename std::vector<T>::size_type size_type; 

  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;
  typedef typename std::vector<T>::reverse_iterator reverse_iterator;
  typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;

  RangeSet() {}

// TODO: ensure init.size() is even
  RangeSet(std::initializer_list<T> init): vec(init) {}

  RangeSet(const std::bitset<N>& b) {
    for (uint32 i = 0; i < N; ++i) {
      if (b[i]) {
        uint32 j = i + 1;
        for ( ; j < N; ++j) {
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
    for (uint32 i = 0; i < N; ++i) {
      if (test(i) != b.test(i)) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const std::bitset<N>& b) const {
    return !(*this == b);
  }

  // provides operator== and operator!= for std::bitset on the left
  friend bool ::operator==(const std::bitset<N>& b, const RangeSet<T,N>& r) {
    return r == b;
  }
  
  friend bool ::operator!=(const std::bitset<N>& b, const RangeSet<T,N>& r) {
    return r != b;
  }

  bool test(size_type pos) const {
    const const_iterator i = std::lower_bound(vec.begin(), vec.end(), pos);
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

/*
private:
  class ElementReference {
  public:
    ElementReference(RangeSet<T,N>& r, size_type i): rs(r), pos(i) {}

    ElementReference& operator=(bool value) {
      rs.set(pos, value);
      return *this;
    }

  private:
    RangeSet<T,N>& rs;
    size_type pos;
  };

public:
  typedef ElementReference reference;

  reference operator[](size_type pos) {
    return ElementReference(*this, pos); 
  }
*/

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
    const const_iterator end(vec.end());
    for (const_iterator i(vec.begin()); i != end; i += 2) {
      c += *(i+1) - *i;
    } 
    return c;
  }

  iterator begin() {
    return vec.begin();
  }

  const_iterator begin() const {
    return vec.begin();
  }

  const_iterator cbegin() const {
    return vec.cbegin();
  }

  iterator end() {
    return vec.end();
  }

  const_iterator end() const {
    return vec.end();
  }

  const_iterator cend() const {
    return vec.cend();
  }

  reverse_iterator rbegin() {
    return vec.rbegin();
  }

  const_reverse_iterator rbegin() const {
    return vec.rbegin();
  }

  const_reverse_iterator crbegin() const {
    return vec.crbegin();
  }

  reverse_iterator rend() {
    return vec.rend();
  }

  const_reverse_iterator rend() const {
    return vec.rend();
  }

  const_reverse_iterator crend() const {
    return vec.crend();
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

  void insert(const std::pair<T,T>& range) {
    insert(range.first, range.second);
  }

  void insert(const T& first, const T& last) {
    if (first == last) {
      return;
    }

    iterator l(std::lower_bound(vec.begin(), vec.end(), first));
    iterator u(std::upper_bound(l, vec.end(), last));

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

      u = vec.erase(l, u);

      if (insertLast) {
        vec.insert(u, last);
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
