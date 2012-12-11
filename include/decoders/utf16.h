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

template <bool LE, typename B>
size_t utf16_to_cp(const B buf, const B end, int32_t& cp) {
  if (end - buf < 2) {
    // invalid, too few bytes
    return 0;
  }

  cp = buf[LE ? 0 : 1] | (buf[LE ? 1 : 0] << 8);

  if (cp < 0xD800) {
    // direct representation
    return 2;
  }
  else if (cp < 0xDC00) {
    // found lead of UTF-16 surrogate pair
    const uint16_t lead = cp;

    if (end - buf < 4) {
      // invalid, too few bytes
      return 0;
    }

    const uint16_t trail = buf[LE ? 2 : 3] | (buf[LE ? 3 : 2] << 8);
    if (trail < 0xDC00) {
      // invalid
      return 0;
    }
    else if (trail < 0xE000) {
      // found trail of UTF-16 surrogate pair
      cp = ((lead - (0xD800 - (0x10000 >> 10))) << 10) | (trail - 0xDC00);
      return 4;
    }
    else {
      // invalid
      return 0;
    }
  }
  else if (cp < 0xE000) {
    // invalid
    return 0;
  }
  else {
    // direct representation
    return 2;
  }
}

template <bool LE, typename B>
size_t cp_to_utf16(int32_t cp, B& buf) {
  if (cp < 0) {
    // too small
    return 0;
  }
  else if (cp < 0xD800) {
    // direct representation
    buf[LE ? 0 : 1] = cp & 0xFF;
    buf[LE ? 1 : 0] = cp >> 8;
    return 2;
  }
  else if (cp < 0xE000) {
    // UTF-16 surrogates, invalid
    return 0;
  }
  else if (cp < 0x10000) {
    // direct representation
    buf[LE ? 0 : 1] = cp & 0xFF;
    buf[LE ? 1 : 0] = cp >> 8;
    return 2;
  }
  else if (cp < 0x110000) {
    // surrogate pair representation
    const uint16_t lead = 0xD800 - (0x10000 >> 10) + (cp >> 10);
    const uint16_t trail = 0xDC00 + (cp & 0x3FF);

    buf[LE ? 0 : 1] = lead & 0xFF;
    buf[LE ? 1 : 0] = lead >> 8;
    buf[LE ? 2 : 3] = trail & 0xFF;
    buf[LE ? 3 : 2] = trail >> 8;
    return 4;
  }
  else {
    // too large
    return 0;
  }
}
