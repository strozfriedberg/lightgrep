#pragma once

#include "basic.h"

#include <algorithm>
#include <vector>

template <typename T>
struct SimpleVectorFamily {
  typedef typename std::vector<T> ListType;
  typedef typename std::vector<T> Holder;

  typename Holder::size_type size(const Holder& l) const {
    return l.size();
  }
  
  void add(Holder& l, T e) {
    l.push_back(e);
  }

  void insert(Holder& l, typename Holder::size_type i, T e) {
    l.insert(i < l.size() ? l.begin() + i : l.end(), e);
  }

  void remove(Holder& l, T e) {
    const typename Holder::iterator i(std::find(l.begin(), l.end(), e));
    if (i == l.end()) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(e << " not in list");
    }

    l.erase(i);
  }

  void clear(Holder& l) {
    l.clear();
  }

  T& at(Holder& l, typename Holder::size_type i) {
    if (i >= l.size()) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(i << " out of bounds");
    }

    return l[i];
  }

  const T& at(const Holder& l, typename Holder::size_type i) const {
    if (i >= l.size()) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(i << " out of bounds");
    }

    return l[i];
  }

  T* find(Holder& l, T e) {
    return &*std::find(l.begin(), l.end(), e);
  }

  T const* find(const Holder& l, T e) const {
    return &*std::find(l.begin(), l.end(), e);
  }

  T* begin(Holder& l) {
    return &*l.begin();
  }

  T const* begin(const Holder& l) const {
    return &*l.begin();
  }

  T* end(Holder& l) {
    return &*l.end();
  }

  T const* end(const Holder& l) const {
    return &*l.end();
  }
};

