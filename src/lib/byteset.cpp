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

#include "byteset.h"

#include <iomanip>

std::ostream& operator<<(std::ostream& out, const ByteSet& bs) {
  out << '[' << std::hex;

  int low = -1;
  bool first = true;
  for (int i = 0; i < 256; ++i) {
    if (bs.test(i)) {
      if (low < 0) {
        if (!first) {
          out << ',';
        }
        out << std::setfill('0') << std::setw(2) << i;
        low = i;
        first = false;
      }
    }
    else if (low >= 0) {
      if ((i-1) > low) {
        out << '-' << std::setfill('0') << std::setw(2) << (i-1);
      }
      low = -1;
    }
  }

  if (0 <= low && low < 255) {
    out << '-' << std::setfill('0') << std::setw(2) << 255;
  }

  out << ']' << std::dec;
  return out;
}
