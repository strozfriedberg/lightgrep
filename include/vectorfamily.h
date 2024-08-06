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
#include <initializer_list>
#include <limits>
#include <type_traits>
#include <utility>

template <typename T>
class VectorFamily {
private:
  typedef typename std::vector<T> Vec;

  enum WhichType {
    ZERO = 0,
    ONE  = 1,
    MANY = ONE << 1
  };

public:
#pragma pack(push, 1)
  struct List {
    typedef typename std::vector<Vec>::size_type size_type;
    typedef T* iterator;
    typedef T const* const_iterator;

    T What;
    byte Which;

    List(): What(std::numeric_limits<T>::max()), Which(ZERO) {}
  };
#pragma pack(pop)

  typename List::size_type size(const List& l) const {
    switch (l.Which) {
    case ZERO:
      return 0;
    case ONE:
      return 1;
    default:
      return Store[l.What].size();
    }
  }

  void add(List& l, T e) {
    switch (l.Which) {
    case ZERO:
      l.Which = ONE;
      l.What = e;
      break;
    case ONE:
      {
        l.Which = MANY;
        Store.emplace_back(std::initializer_list<T>{l.What, e});
        l.What = Store.size() - 1;
      }
      break;
    default:
      Store[l.What].push_back(e);
    }
  }

  void insert(List& l, typename List::size_type i, T e) {
    switch (l.Which) {
    case ZERO:
      l.Which = ONE;
      l.What = e;
      break;
    case ONE:
      {
        l.Which = MANY;
        Store.emplace_back(
          i == 0 ?
          std::initializer_list<T>{e, l.What} :
          std::initializer_list<T>{l.What, e}
        );
        l.What = Store.size() - 1;
      }
      break;
    default:
      {
        Vec& elist(Store[l.What]);
        elist.insert(i < elist.size() ? elist.begin() + i : elist.end(), e);
      }
    }
  }

  void remove(List& l, T e) {
    switch (l.Which) {
    case ZERO:
      {
        THROW_RUNTIME_ERROR_WITH_OUTPUT(e << " not in list");
      }
    case ONE:
      if (l.What != e) {
        THROW_RUNTIME_ERROR_WITH_OUTPUT(e << " not in list");
      }

      l.Which = ZERO;
      break;
    default:
      {
        Vec& edlist(Store[l.What]);

        const typename Vec::iterator i(std::find(edlist.begin(), edlist.end(), e));
        if (i == edlist.end()) {
          THROW_RUNTIME_ERROR_WITH_OUTPUT(e << " not in list");
        }

        edlist.erase(i);

        if (edlist.size() == 1) {
          l.Which = ONE;
          l.What = edlist.front();
          edlist.clear();
        }
      }
    }
  }

  void clear(List& l) {
    switch (l.Which) {
    case MANY:
      Store[l.What].clear();
    case ONE:
      l.Which = ZERO;
    }
  }

  T& at(List& l, typename List::size_type i) {
    return const_cast<T&>(std::as_const(*this).at(l, i));
  }

  const T& at(const List& l, typename List::size_type i) const {
    switch (l.Which) {
    case ZERO:
      {
        THROW_RUNTIME_ERROR_WITH_OUTPUT(i << " out of bounds");
      }
    case ONE:
      return l.What;
    default:
      return Store[l.What][i];
    }
  }

  typename List::iterator find(List& l, T e) {
    return const_cast<typename List::iterator>(std::as_const(*this).find(l, e));
  }

  typename List::const_iterator find(const List& l, T e) const {
    switch (l.Which) {
    case ZERO:
      return end(l);
    case ONE:
      return l.What == e ? begin_few(l) : end_one(l);
    default:
      return std::find(begin_many(l), end_many(l), e);
    }
  }

  typename List::iterator begin(List& l) {
    return const_cast<typename List::iterator>(std::as_const(*this).begin(l));
  }

  typename List::const_iterator begin(const List& l) const {
    switch (l.Which) {
    case ZERO:
    case ONE:
      return begin_few(l);
    default:
      return begin_many(l);
    }
  }

  typename List::iterator end(List& l) {
    return const_cast<typename List::iterator>(std::as_const(*this).end(l));
  }

  typename List::const_iterator end(const List& l) const {
    switch (l.Which) {
    case ZERO:
      return end_zero(l);
    case ONE:
      return end_one(l);
    default:
      return end_many(l);
    }
  }

private:
  typename List::const_iterator begin_few(const List& l) const { return &l.What; }

  typename List::const_iterator begin_many(const List& l) const {
    return &Store[l.What].front();
  }

  typename List::const_iterator end_zero(const List& l) const { return &l.What; }

  typename List::const_iterator end_one(const List& l) const { return &l.What + 1; }

  typename List::const_iterator end_many(const List& l) const {
    return begin_many(l) + Store[l.What].size();
  }

  std::vector<Vec> Store;
};
