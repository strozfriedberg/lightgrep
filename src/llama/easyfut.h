#pragma once

#include <future>

#include "boost_asio.h"

template <typename ValueType>
struct easy_fut {
  easy_fut() : Promise(), Fut(Promise.get_future()) {}

  template <typename ExecutorType, typename Callable>
  easy_fut(ExecutorType& exec, Callable functor)
      : Promise(), Fut(Promise.get_future()) {
    run(exec, functor);
  }

  ValueType get() { return Fut.get(); }

  std::promise<ValueType> Promise;
  std::future<ValueType> Fut;

  template <typename ExecutorType, typename Callable>
  void run(ExecutorType& exec, Callable functor) {
    boost::asio::post(exec, [=]() {
      try {
        this->Promise.set_value(functor());
      }
      catch (...) {
        this->Promise.set_exception(std::current_exception());
      }
    });
  }
};

template <typename ExecutorType, typename Callable>
auto make_future(ExecutorType& exec, Callable functor) {
  return easy_fut<decltype(functor())>(exec, functor);
}
