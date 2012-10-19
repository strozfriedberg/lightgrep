/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <algorithm>

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
    if (cp < 0x800 || (0xD7FF < cp && cp < 0xE000)) {
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

template <class Iterator>
int unicode_to_ascii(byte& b, Iterator& i, const Iterator& end) {
  if (i == end) {
    return -1;
  }

  const int cp = *i++;
  if (cp < 0 || 0xFF < cp) {
    return -1;
  }

  b = cp;
  return 1;
}

template <class Decoder, class InputIterator, class OutputIterator>
OutputIterator transform_to_unicode(InputIterator ibegin,
                                    InputIterator iend,
                                    OutputIterator obegin,
                                    Decoder decoder)
{
  int cp;
  while (ibegin != iend) {
    ibegin += decoder(cp, ibegin, iend);
    *obegin++ = cp;
  }
  return obegin;
}

template <class InputIterator, class OutputIterator>
OutputIterator transform_utf8_to_unicode(InputIterator ibegin,
                                         InputIterator iend,
                                         OutputIterator obegin)
{
  return transform_to_unicode(ibegin, iend, obegin,
                              utf8_to_unicode<InputIterator>);
}

/*
template <class InputIterator, class OutputIterator>
OutputIterator transform_unicode_to_ascii(InputIterator ibegin,
                                          InputIterator iend,
                                          OutputIterator obegin)
{
  byte b;
  int ret;
  while (ibegin != iend) {
    ret = unicode_to_ascii(b, ibegin, iend);
    if (ret < 0) {

    }
    ibegin += unicode_to_ascii(b, ibegin, iend);
    *obegin++ = b;
  }
  return obegin;
}
*/
