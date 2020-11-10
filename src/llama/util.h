#pragma once

#include <memory>
#include <type_traits>

template <class T, class D>
std::unique_ptr<T, D> make_unique_del(T* p, D&& deleter) {
  return std::unique_ptr<T, D>{p, std::forward<D>(deleter)};
}

template <typename F>
struct function_traits;

template <typename R, typename A>
struct function_traits<R (&)(A)> {
  using result_type = R;
  using arg_type    = A;
};

template <class F>
using ArgOf = typename std::remove_pointer<typename function_traits<F>::arg_type>::type;

template <class D>
std::unique_ptr<ArgOf<D>, D> make_unique_del(std::nullptr_t, D&& deleter) {
  return make_unique_del<ArgOf<D>, D>(nullptr, std::forward<D>(deleter));
}
