#pragma once

#include <algorithm>
#include <set>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

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
  Duplicate<T> dup;
  list.erase(
    std::remove_if(
      list.begin(), list.end(),
      boost::bind(&Duplicate<T>::operator(), boost::ref(dup), _1)
    ),
    list.end()
  );
}
