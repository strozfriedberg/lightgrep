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
size_t utf32_to_cp(const B buf, const B end, int32_t& cp) {
  if (end - buf < 4) {
    // invalid, too few bytes
    return 0;
  }

  cp = (buf[LE ? 0 : 3]      ) |
       (buf[LE ? 1 : 2] <<  8) |
       (buf[LE ? 2 : 1] << 16) |
       (buf[LE ? 3 : 0] << 24);

  if (cp < 0 || (0xD800 <= cp && cp < 0xE000) || 0x110000 <= cp) {
    // out of range
    cp = -1;
    return 0;
  }
  else {
    return 4;
  }
}

template <bool LE, typename B>
size_t cp_to_utf32(int32_t cp, B& buf) {
  if (cp < 0) {
    // too small
    return 0;
  }
  else if (cp < 0xD800) {
    buf[LE ? 0 : 3] =  cp        & 0xFF;
    buf[LE ? 1 : 2] = (cp >>  8) & 0xFF;
    buf[LE ? 2 : 1] = (cp >> 16) & 0xFF;
    buf[LE ? 3 : 0] = (cp >> 24) & 0xFF;
    return 4;
  }
  else if (cp < 0xE000) {
    // UTF-16 surrogates, invalid
    return 0;
  }
  else if (cp < 0x110000) {
    buf[LE ? 0 : 3] =  cp        & 0xFF;
    buf[LE ? 1 : 2] = (cp >>  8) & 0xFF;
    buf[LE ? 2 : 1] = (cp >> 16) & 0xFF;
    buf[LE ? 3 : 0] = (cp >> 24) & 0xFF;
    return 4;
  }
  else {
    // too large
    return 0;
  }
}
