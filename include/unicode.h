#pragma once

#include <algorithm>
#include <iterator>

#include <boost/iterator/iterator_facade.hpp>

#define CONTINUATION(i,cp) \
  b = *++i & 0xFF; \
  if (b < 0x80 || 0xBF < b) { \
    cp = -1; \
    return -1; \
  } \
  cp = (cp << 6) | (b & 0x3F)

template <class Iterator>
int utf8_to_unicode(int& cp, Iterator i, const Iterator& end) {

  if (i == end) {
    cp = -1;
    return -1;
  }

  cp = *i & 0xFF;

  // 1-byte sequence
  if (cp < 0x80) {
    return 1;
  }

  byte b;
  // 2-byte sequence
  if (cp < 0xE0) {
    // overlong
    if (cp < 0xC2) {
      cp = -1;
      return -1;
    }
    
    cp &= 0x1F;
    CONTINUATION(i, cp);

    return 2;
  }
  // 3-byte sequence
  else if (cp < 0xF0) {
    cp &= 0x0F;
    CONTINUATION(i, cp);
    CONTINUATION(i, cp);

    // check for overlong and UTF-16 surrogates
    if ((0x7FF < cp && cp < 0xD800) || cp > 0xDFFF) {
      return 3;
    }
    else {
      cp = -1;
      return -1;
    }
  }
  // 4-byte sequence
  else if (cp < 0xF5) {
    cp &= 0x07;
    CONTINUATION(i, cp);
    CONTINUATION(i, cp);
    CONTINUATION(i, cp);

    // check for overlong and too high
    if (cp < 0x10000 || cp > 0x10FFFF) {
      cp = -1;
      return -1;
    }
    else {
      return 4;
    }
  }
  else {
    // bad start byte
    cp = -1;
    return -1;
  }
} 

#undef CONTINUATION

template <typename C>
struct IsLeadByte {
  bool operator()(const C& c) const {
    const byte b = c & 0xFF;
    return b < 0x80 || (0xC1 < b && b < 0xF5);
  }
};

template <class Iterator>
class UTF8toUnicodeIterator:
public boost::iterator_facade<
  UTF8toUnicodeIterator<Iterator>,
  int const,
  std::random_access_iterator_tag,
  int>
{
public:
  UTF8toUnicodeIterator(): bbegin(), bend() {}

  UTF8toUnicodeIterator(const Iterator& base_begin,
                        const Iterator& base,
                        const Iterator& base_end):
    bi(base), bbegin(base_begin), bend(base_end) {}

private:
  friend class boost::iterator_core_access;

  // can't use Iterator::value_type directly, Iterator might be a pointer
  typedef typename std::iterator_traits<Iterator>::value_type ByteType;

  void increment() {
//    cp = -2;
    bi = std::find_if(++bi, bend, IsLeadByte<ByteType>());
  }

  void decrement() {
//    cp = -2;

/*
    std::reverse_iterator<Iterator> rbi(--bi);
    const std::reverse_iterator<Iterator> rbend(bbegin);
    bi = std::find_if(rbi, rbend, IsLeadByte<ByteType>()).base();
*/

    do {
      if (IsLeadByte<ByteType>()(*--bi)) {
        return;
      }
    } while (bi != bbegin);
  }

  void advance(typename std::iterator_traits<Iterator>::difference_type n) {
    if (n > 0) {
      for ( ; n > 0; --n) {
        increment();
      }
    }
    else if (n < 0) {
      for ( ; n < 0; ++n) {
        decrement();
      }
    }
  }

  int distance_to(const UTF8toUnicodeIterator<Iterator>& other) const {
    if (bi < other.bi) {
      return std::count_if(bi, other.bi, IsLeadByte<ByteType>());
    }
    else {
      return -std::count_if(other.bi, bi, IsLeadByte<ByteType>());
    }
  }

  bool equal(const UTF8toUnicodeIterator<Iterator>& other) const {
    return bi == other.bi && bbegin == other.bbegin && bend == other.bend;
  }

//  const int& dereference() const {
  int dereference() const {
/*
    if (cp < -1) {
      utf8_to_unicode(cp, bi, bend);
    }
    return cp;
*/
    int cp;
    utf8_to_unicode(cp, bi, bend);
    return cp;
  }

  Iterator bi;
  const Iterator bbegin, bend;
//  mutable int cp;
};
