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

#include "encoders/ascii.h"

uint32_t ASCII::write(int32_t cp, byte buf[]) const {
  if (cp < 0) {
    return 0;
  }
  else if (cp < 0x80) {
    buf[0] = cp;
    return 1;
  }
  else {
    return 0;
  }
}

void ASCII::write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const {
  v.emplace_back(1);
  for (const UnicodeSet::range r : uset) {
    if (r.first > 0x7F) {
      break;
    }
    else if (r.second > 0x7F) {
      v[0][0].set(r.first, 0x80, true);
      break;
    }
    else {
      v[0][0].set(r.first, r.second, true);
    }
  }
}

uint32_t ASCII::write(const byte buf[], int32_t& cp) const {
  if (buf[0] < 0x80) {
    cp = buf[0];
    return 1;
  }
  else {
    cp = -1;
    return 0;
  }
}
