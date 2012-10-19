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

#include "ascii.h"

uint32 ASCII::write(int cp, byte buf[]) const {
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
  for (const UnicodeSet::range& r : uset) {
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
