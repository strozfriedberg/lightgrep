#pragma once

#include <algorithm>
#include <iterator>

#include <boost/iterator/iterator_facade.hpp>

#define CONTINUATION(cp, i, end, used) \
  if (++i == end) { \
    cp = -1; \
    return used; \
  } \
  b = *i & 0xFF; \
  if (b < 0x80 || 0xBF < b) { \
    cp = -1; \
    return used; \
  } \
  cp = (cp << 6) | (b & 0x3F)

template <class Iterator>
int utf8_to_unicode(int& cp, Iterator i, const Iterator& end) {

  if (i == end) {
    cp = -1;
    return 0;
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
      return 1;
    }
    
    cp &= 0x1F;
    CONTINUATION(cp, i, end, 2);

    return 2;
  }
  // 3-byte sequence
  else if (cp < 0xF0) {
    cp &= 0x0F;
    CONTINUATION(cp, i, end, 2);
    CONTINUATION(cp, i, end, 3);

    // check for overlong and UTF-16 surrogates
    if ((cp < 0x800 || 0xD7FF < cp) && cp < 0xE000) {
      cp = -1;
    }

    return 3;
  }
  // 4-byte sequence
  else if (cp < 0xF5) {
    cp &= 0x07;
    CONTINUATION(cp, i, end, 2);
    CONTINUATION(cp, i, end, 3);
    CONTINUATION(cp, i, end, 4);

    // check for overlong and too high
    if (cp < 0x10000 || cp > 0x10FFFF) {
      cp = -1;
    }

    return 4;
  }
  else {
    // bad start byte
    cp = -1;
    return 1;
  }
} 

#undef CONTINUATION

template <class InputIterator, class OutputIterator>
OutputIterator transform_utf8_to_unicode(InputIterator ibegin,
                                         InputIterator iend,
                                         OutputIterator obegin)
{
  int cp;
  while (ibegin != iend) {
    ibegin += utf8_to_unicode(cp, ibegin, iend);
    *obegin++ = cp;
  }
  return obegin;
}

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
  UTF8toUnicodeIterator(): bbegin(), bend(), cp(-2) {}

  UTF8toUnicodeIterator(const Iterator& base_begin,
                        const Iterator& base,
                        const Iterator& base_end):
    bi(base), bbegin(base_begin), bend(base_end), cp(-2) {}

  typedef typename std::iterator_traits<UTF8toUnicodeIterator<Iterator>>::difference_type difference_type;

private:
  friend class boost::iterator_core_access;

  // can't use Iterator::value_type directly, Iterator might be a pointer
  typedef typename std::iterator_traits<Iterator>::value_type ByteType;

  void increment() {
    cp = -2;
    bi = std::find_if(++bi, bend, IsLeadByte<ByteType>());
  }

  void decrement() {
    cp = -2;
    std::reverse_iterator<Iterator> rbi(bi);
    const std::reverse_iterator<Iterator> rbend(bbegin);
    bi = std::find_if(rbi, rbend, IsLeadByte<ByteType>()).base() - 1;
  }

  void advance(difference_type n) {
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

  difference_type distance_to(const UTF8toUnicodeIterator<Iterator>& o) const {
    if (bi < o.bi) {
      return std::count_if(bi, o.bi, IsLeadByte<ByteType>());
    }
    else {
      return -std::count_if(o.bi, bi, IsLeadByte<ByteType>());
    }
  }

  bool equal(const UTF8toUnicodeIterator<Iterator>& o) const {
    return bi == o.bi;
  }

  int dereference() const {
    if (cp < -1) {
      utf8_to_unicode(cp, bi, bend);
    }
    return cp;
  }

  Iterator bi;
  const Iterator bbegin, bend;
  mutable int cp;
};
