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

#include "lightgrep/encodings.h"

#include <algorithm>
#include <string>

int lg_get_encoding_id(const char* const name) {
  const LG_SUPPORTED_ENCODING* beg = LG_SUPPORTED_ENCODINGS;
  const LG_SUPPORTED_ENCODING* end =
    LG_SUPPORTED_ENCODINGS +
    sizeof(LG_SUPPORTED_ENCODINGS) / sizeof(LG_SUPPORTED_ENCODING);

  std::string ns(name);
  std::transform(ns.begin(), ns.end(), ns.begin(), tolower);

// TODO: encodings are sorted by name, so do a binary search
  const LG_SUPPORTED_ENCODING* ptr = std::find_if(
    beg,
    end,
    [&](const LG_SUPPORTED_ENCODING& e) -> bool {
      std::string es(e.name);
      std::transform(es.begin(), es.end(), es.begin(), tolower);
      return ns == es;
    }
  );

  return ptr == end ? -1 : ptr->idx;
}
