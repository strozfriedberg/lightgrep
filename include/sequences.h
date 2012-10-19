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

#include <algorithm>
#include <functional>
#include <set>

template <typename T>
struct Duplicate {
  bool operator()(const T& a) {
    return !seen.insert(a).second;
  }

  std::set<T> seen;
};

template <typename T,
          template <typename E, typename A = std::allocator<E>> class C>
void removeRightDuplicates(C<T>& list) {
  using namespace std::placeholders;

  Duplicate<T> dup;
  list.erase(
    std::remove_if(
      list.begin(), list.end(),
      std::bind(&Duplicate<T>::operator(), std::ref(dup), _1)
    ),
    list.end()
  );
}
