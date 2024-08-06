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

#include "ostream_join_iterator.h"

#include <algorithm>
#include <ostream>
#include <functional>

template <typename T,
          template <typename E, typename A = std::allocator<E>> class C>
std::ostream& operator<<(std::ostream& out, const C<T>& con) {
  out << '[';
  std::copy(con.begin(), con.end(), ostream_join_iterator<T>(out, ","));
  return out << ']';
}

template <typename T,
          template <typename K, typename C = std::less<K>, typename A = std::allocator<K>> class C>
std::ostream& operator<<(std::ostream& out, const C<T>& con) {
  out << '[';
  std::copy(con.begin(), con.end(), ostream_join_iterator<T>(out, ","));
  return out << ']';
}
