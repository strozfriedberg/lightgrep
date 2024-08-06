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
