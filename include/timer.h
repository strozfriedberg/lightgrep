#pragma once

#include <chrono>

class Timer {
public:
  double elapsed() const {
    return std::chrono::duration<double>(
      std::chrono::high_resolution_clock::now() - start
    ).count();
  }

private:
  const std::chrono::time_point<std::chrono::high_resolution_clock> start =
    std::chrono::high_resolution_clock::now();
};
