#pragma once

#include <iterator>

struct Tab {
  int cmask;
  int cval;
  int shift;
  int lmask;
  int lval;
};

static const
Tab tab[] =
{
  { 0x80, 0x00, 0*6, 0x7F,     0       }, /* 1-byte sequence */
  { 0xE0, 0xC0, 1*6, 0x7FF,    0x80    }, /* 2-byte sequence */
  { 0xF0, 0xE0, 2*6, 0xFFFF,   0x800   }, /* 3-byte sequence */
  { 0xF8, 0xF0, 3*6, 0x1FFFFF, 0x10000 }, /* 4-byte sequence */
  { 0,    0,    0,   0,        0       }  /* end of table */
};

// FIXME: check that iterator is properly incremented
template <class Iterator>
int utf8_to_unicode_thompson(Iterator& i, const Iterator& end) {

  if (i == end) {
    return -1;
  }

  const typename std::iterator_traits<Iterator>::difference_type n(std::distance(i, end));

  int l, c0, c, nc;

  nc = 0;
  l = c0 = *i & 0xFF;

  for(const Tab* t = tab; t->cmask; ++t) {
    ++nc;
    if ((c0 & t->cmask) == t->cval) {
      l &= t->lmask;
      if (l < t->lval) {
        return -1;
      }
      else if (nc == 3 && 0xD7FF < l && l < 0xE000) {
        // UTF-16 surrogate cutout
        return -1;
      }
      else {
        return l; 
      }
//      return l < t->lval ? -1 : l;
    }

    if(n <= nc) {
      return -1;
    }

    ++i;
    c = (*i ^ 0x80) & 0xFF;
    if (c & 0xC0) {
      return -1;
    }

    l = (l << 6) | c;
  }

  return -1;
}

template <class Iterator>
int utf8_to_unicode_naive(Iterator& i, const Iterator& end) {

  if (i == end) {
    return -1;
  }

  int cp = *i;

  // 1-byte sequence
  if (cp < 0x80) {
    ++i;
    return cp;
  }
  // 2-byte sequence
  else if (cp < 0xE0) {
    if (cp < 0xC2) {
      return -1;
    }
    
    cp &= 0x1F;
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
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i & 0x3F);
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i++ & 0x3F);

    return (0x7FF < cp && cp < 0xD800) || cp > 0xDFFF ? cp : -1;
  }
  // 4-byte sequence
  else if (cp < 0xF5) {
    cp &= 0x07;
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i & 0x3F);
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }
    
    cp |= (*i & 0x3F);
    cp <<= 6;

    ++i;
    if (*i < 0x80 || 0xBF < *i) {
      return -1;
    }

    cp |= (*i++ & 0x3F);
    return cp < 0x10000 || cp > 0x10FFFF ? -1 : cp;
  }
  else {
    return -1;
  }
} 

/*
static const byte UTF8TailLengths[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,4,4,4,4,5,5,0,0
};

struct UTF8Lookup {
	uint32 mOverlongMinimum, mMagicSubtraction;
} const UTF8Lookups[6] = {
	{ 0x00000000, 0x00000000 },
	{ 0x00000080, 0x00003080 },
	{ 0x00000800, 0x000E2080 },
	{ 0x00010000, 0x03C82080 },
	{ 0x00200000, 0xFA082080 },
	{ 0x04000000, 0x82082080 },
};

const unsigned char UTF8InvalidTailBits[4] = {
	1,1,0,1,
};

const unsigned int UTF8InvalidOffset[32] = {
	0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
};

template <class Iterator>
int utf8_to_unicode_tables(Iterator& i, const Iterator& end) {
  int c = *i++;
	
  if (c < 0x80) {
		return c;
  }

	uint32 tail = UTF8TailLengths[c];
	if (!tail || (i + tail > end)) {
		return -1;
  }

  c &= 0x3f >> tail;

  unsigned int mask = 0;
  for (unsigned int x = 0; x < tail; ++x) {
	  c = (c << 6) + i[x];
  	mask = (mask << 1) | UTF8InvalidTailBits[i[x] >> 6];
  }

  i += tail;
  if (mask) {
  	i -= UTF8InvalidOffset[mask];
  	return -1;
  }

  const UTF8Lookup& lookup = UTF8Lookups[tail];
  c -= lookup.mMagicSubtraction;
  if (c < lookup.mOverlongMinimum) {
    return -1;
  }

  if (c >= 0xD800 && c <= 0xDFFF) {
    return -1;
  }

  if (c > 0x10FFFF) {
    return -1;
  }

  return c;
}
*/

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
