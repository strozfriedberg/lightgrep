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
