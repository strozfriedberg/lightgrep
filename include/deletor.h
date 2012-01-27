#pragma once

// FIXME: Replace with std::default_delete in C++11
template <typename T>
struct Deletor {
  void operator()(T* ptr) const { delete ptr; }
};
