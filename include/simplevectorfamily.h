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

  typename Holder::iterator find(Holder& l, T e) {
    return std::find(l.begin(), l.end(), e);
  }

  typename Holder::const_iterator find(const Holder& l, T e) const {
    return std::find(l.begin(), l.end(), e);
  }

  typename Holder::iterator begin(Holder& l) {
    return l.begin();
  }

  typename Holder::const_iterator begin(const Holder& l) const {
    return l.begin();
  }

  typename Holder::iterator end(Holder& l) {
    return l.end();
  }

  typename Holder::const_iterator end(const Holder& l) const {
    return l.end();
  }
};

