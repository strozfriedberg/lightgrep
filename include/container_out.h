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
