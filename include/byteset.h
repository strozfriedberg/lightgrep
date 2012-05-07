#pragma once

#include <bitset>
#include <cstring>

class ByteSet: public std::bitset<256> {
public:
  ByteSet(): std::bitset<256>() {}

  ByteSet(unsigned long val): std::bitset<256>(val) {}

  int compare(const ByteSet& other) const {
    // This is evil, and depends on std::bitset<256> being laid out as an
    // array of 32 bytes. If it is not, this will fail catastrophically.
    //
    // Note that this is NOT a lexicographical comparison unless we are on
    // a big-endian architecture (or one which has 1-bit bytes and thus has
    // no endianness!), because memcmp operates on register-sized blocks.
    return memcmp(this, &other, sizeof(ByteSet));
  }

  bool operator<(const ByteSet& other) const {
    return compare(other) < 0;
  }

  bool operator>(const ByteSet& other) const {
    return compare(other) > 0;
  }

  bool operator<=(const ByteSet& other) const {
    return compare(other) <= 0;
  }

  bool operator>=(const ByteSet& other) const {
    return compare(other) >= 0;
  }

  bool operator==(const ByteSet& other) const {
    return compare(other) == 0;
  }

  bool operator!=(const ByteSet& other) const {
    return compare(other) != 0;
  }
};
