/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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

  void slow_for_each(std::function<void(uint64_t)> callback) const {
    for (uint32_t i = 0; i < size(); i++) {
      if (this->test(i)) {
        callback(i);
      } 
    }
  }

  void fast_for_each(std::function<void(uint64_t)> callback) const {
    // This is evil.
    const uint64_t* words = reinterpret_cast<const uint64_t*>(this);
    for (int i = 0; i < 4; i++) {
      uint64_t word = words[i];
      while (word != 0) {
        // isolate least significant set bit
        uint64_t lsb = word & -word;
        // get the index of the set bit
        uint64_t index = (i << 6) + __builtin_ctzll(word);
        callback(index);
        // xor og word with lsb to get new word with the previous lsb unset
        word ^= lsb;
      }
    }
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

  ByteSet operator~() const {
    ByteSet ret(*this);
    ret.flip();
    return ret;
  }

  ByteSet operator-(const ByteSet& other) const {
    ByteSet ret(*this);
    ret -= other;
    return ret;
  }

  ByteSet& operator-=(const ByteSet& other) {
    *this &= ~other;
    return *this;
  }
};

std::ostream& operator<<(std::ostream& out, const ByteSet& bs);
