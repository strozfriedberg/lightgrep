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
