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

/*
template <class BaseIterator>
class UTF8toUnicodeIterator:
public std::iterator<std::forward_iterator_tag,int>
{
pubilc:
  UTF8toUnicodeIterator(): bi() {
  }
  
  UTF8toUnicodeIterator(BaseIterator base): bi(base) {
  }

  int operator*() const {

  }

  UTF8toUnicodeIterator& operator++() {

  }

  UTF8toUnicodeIterator& operator++(int) {

  }

  bool operator==(const UTF8toUnicodeIterator& other) const {
    return pos == other.pos;
  }

  bool operator!=(const UTF8toUnicodeIterator& other) const {
    return pos != other.pos;
  }
  
private:
  BaseIterator bi; 
};
*/
