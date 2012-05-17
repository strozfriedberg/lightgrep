#pragma once

#include <bitset>
#include <cstring>
#include <initializer_list>
#include <ostream>

class ByteSet: public std::bitset<256> {
public:
  ByteSet(): std::bitset<256>() {}

  ByteSet(unsigned char val): std::bitset<256>() {
    set(val);
  }

  ByteSet(std::initializer_list<unsigned char> init) {
    for (unsigned char b : init) {
      set(b);
    }
  }

  ByteSet(std::initializer_list<std::pair<size_t,size_t>> init) {
    for (const std::pair<size_t,size_t>& p : init) {
      set(p.first, p.second, true);
    }
  }

  int compare(const ByteSet& other) const {
    // This is evil, and depends on std::bitset<256> being laid out as an
    // array of 32 bytes. If it is not, this will fail catastrophically.
    //
    // Note that this is NOT a lexicographical comparison unless we are on
    // a big-endian architecture (or one which has 1-bit bytes and thus has
    // no endianness!), because memcmp operates on register-sized blocks.
    return memcmp(this, &other, sizeof(ByteSet));
  }

  ByteSet& set(size_t beg, size_t end, bool value) {
    // This is evil, and depends on std::bitset<256> being laid out as an
    // array of 32 bytes and having no other state. If this is not the case,
    // this will fail catastrophically.
    for ( ; beg < end && beg % 8 > 0; ++beg) {
      set(beg, value);
    }

    if ((end-beg)/8 > 0) {
      unsigned char* buf = reinterpret_cast<unsigned char*>(this);
      std::fill(buf + beg/8, buf + end/8, value ? 0xFF : 0);
      beg = (end/8)*8;
    }

    for ( ; beg < end; ++beg) {
      set(beg, value);
    }

    return *this;
  }

  using std::bitset<256>::set;

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

std::ostream& operator<<(std::ostream& out, const ByteSet& bs);
