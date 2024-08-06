/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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

