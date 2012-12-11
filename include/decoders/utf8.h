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

#define CONTINUATION(cp, i, end) \
  if (++i == end) { \
    return 0; \
  } \
  b = *i & 0xFF; \
  if (b < 0x80 || 0xBF < b) { \
    return 0; \
  } \
  cp = (cp << 6) | (b & 0x3F)


template <typename B>
size_t utf8_to_cp(B i, B end, int32_t& cp) {
  if (i == end) {
    // no bytes
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
      return 0;
    }

    cp &= 0x1F;
    CONTINUATION(cp, i, end);

    return 2;
  }
  // 3-byte sequence
  else if (cp < 0xF0) {
    cp &= 0x0F;
    CONTINUATION(cp, i, end);
    CONTINUATION(cp, i, end);

    // check for overlong and UTF-16 surrogates
    if (cp < 0x800 || (0xD7FF < cp && cp < 0xE000)) {
      return 0;
    }

    return 3;
  }
  // 4-byte sequence
  else if (cp < 0xF5) {
    cp &= 0x07;
    CONTINUATION(cp, i, end);
    CONTINUATION(cp, i, end);
    CONTINUATION(cp, i, end);

    // check for overlong and too high
    if (cp < 0x10000 || cp > 0x10FFFF) {
      return 0;
    }

    return 4;
  }
  else {
    // bad start byte
    return 0;
  }
}

#undef CONTINUATION

template <typename B>
size_t cp_to_utf8(int32_t cp, B& buf) {
  if (cp < 0) {
    // too small
    return 0;
  }
  else if (cp < 0x80) {
    // one byte
    buf[0] = (byte) cp;
    return 1;
  }
  else if (cp < 0x800) {
    // two bytes
    buf[0] = 0xC0 | ((cp >> 6) & 0x1F);
    buf[1] = 0x80 | ( cp       & 0x3F);
    return 2;
  }
  else if (cp < 0xD800) {
    // three bytes
    buf[0] = 0xE0 | ((cp >> 12) & 0x0F);
    buf[1] = 0x80 | ((cp >>  6) & 0x3F);
    buf[2] = 0x80 | ( cp        & 0x3F);
    return 3;
  }
  else if (cp < 0xE000) {
    // UTF-16 surrogates, invalid
    return 0;
  }
  else if (cp < 0x10000) {
    // three bytes
    buf[0] = 0xE0 | ((cp >> 12) & 0x0F);
    buf[1] = 0x80 | ((cp >>  6) & 0x3F);
    buf[2] = 0x80 | ( cp        & 0x3F);
    return 3;
  }
  else if (cp < 0x110000) {
    // four bytes
    buf[0] = 0xF0 | ((cp >> 18) & 0x07);
    buf[1] = 0x80 | ((cp >> 12) & 0x3F);
    buf[2] = 0x80 | ((cp >>  6) & 0x3F);
    buf[3] = 0x80 | ( cp        & 0x3F);
    return 4;
  }
  else {
    // too large
    return 0;
  }
}
