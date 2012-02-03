#pragma once

#include <bitset>
#include <cstring>

template <size_t N>
int lexcmp_bitset(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  // This is evil, and depends on std::bitset<N> being layed out as an
  // array of N/8 bytes. If it is not, this will fail catastrophically.
  return memcmp(&lbs, &rbs, sizeof(lbs));
}

template <size_t N>
bool operator<(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  return lexcmp_bitset(lbs, rbs) < 0;
}

template <size_t N>
bool operator>(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  return lexcmp_bitset(lbs, rbs) > 0;
}

template <size_t N>
bool operator<=(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  return lexcmp_bitset(lbs, rbs) <= 0;
}

template <size_t N>
bool operator>=(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  return lexcmp_bitset(lbs, rbs) >= 0;
}

template <size_t N>
bool operator==(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  return lexcmp_bitset(lbs, rbs) == 0;
}

template <size_t N>
bool operator!=(const std::bitset<N>& lbs, const std::bitset<N>& rbs) {
  return lexcmp_bitset(lbs, rbs) != 0;
}
