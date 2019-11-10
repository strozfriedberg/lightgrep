/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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
  typedef typename std::vector<T> List;

  typename List::size_type size(const List& l) const {
    return l.size();
  }

  void add(List& l, T e) {
    l.push_back(e);
  }

  void insert(List& l, typename List::size_type i, T e) {
    l.insert(i < l.size() ? l.begin() + i : l.end(), e);
  }

  void remove(List& l, T e) {
    const typename List::iterator i(std::find(l.begin(), l.end(), e));
    if (i == l.end()) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(e << " not in list");
    }

    l.erase(i);
  }

  void clear(List& l) {
    l.clear();
  }

  T& at(List& l, typename List::size_type i) {
    if (i >= l.size()) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(i << " out of bounds");
    }

    return l[i];
  }

  const T& at(const List& l, typename List::size_type i) const {
    if (i >= l.size()) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(i << " out of bounds");
    }

    return l[i];
  }

  typename List::iterator find(List& l, T e) {
    return std::find(l.begin(), l.end(), e);
  }

  typename List::const_iterator find(const List& l, T e) const {
    return std::find(l.begin(), l.end(), e);
  }

  typename List::iterator begin(List& l) {
    return l.begin();
  }

  typename List::const_iterator begin(const List& l) const {
    return l.begin();
  }

  typename List::iterator end(List& l) {
    return l.end();
  }

  typename List::const_iterator end(const List& l) const {
    return l.end();
  }
};

