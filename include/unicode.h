#pragma once

#include <iterator>

template <class Iterator>
int utf8_to_unicode(Iterator& i, const Iterator& end) {

  if (i == end) {
    return -1;
  }

  int cp = *i & 0xFF;

  // 1-byte sequence
  if (cp < 0x80) {
    ++i;
    return cp;
  }
  // 2-byte sequence
  else if (cp < 0xE0) {
    // overlong
    if (cp < 0xC2) {
      return -1;
    }
    
    cp &= 0x1F;

    // continuation 1
    cp <<= 6;
    
    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i++ & 0x3F);
    return cp;
  }
  // 3-byte sequence
  else if (cp < 0xF0) {
    cp &= 0x0F;

    // continuation 1
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i & 0x3F);

    // continuation 2
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i++ & 0x3F);

    // check for overlong and UTF-16 surrogates
    return (0x7FF < cp && cp < 0xD800) || cp > 0xDFFF ? cp : -1;
  }
  // 4-byte sequence
  else if (cp < 0xF5) {
    cp &= 0x07;

    // continuation 1
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i & 0x3F);

    // continuation 2
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }
    
    cp |= (*i & 0x3F);

    // continuation 3
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i++ & 0x3F);

    // check for overlong and too high
    return cp < 0x10000 || cp > 0x10FFFF ? -1 : cp;
  }
  else {
    // bad start byte
    return -1;
  }
} 

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
