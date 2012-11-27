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

#include <algorithm>
#include <cctype>
#include <string>

#include "c_api_util.h"
#include "lightgrep/util.h"
#include "lightgrep/transforms.h"
#include "lightgrep/encodings.h"

int find_trans_id(const LG_TRANS* beg, const LG_TRANS* end, const char* const name) {
  std::string ns(name);
  std::transform(ns.begin(), ns.end(), ns.begin(), ::tolower);

// TODO: encodings are sorted by name, so do a binary search
  const LG_TRANS* ptr = std::find_if(
    beg,
    end,
    [&](const LG_TRANS& t) -> bool {
      std::string ts(t.name);
// FIXME: why ::tolower instead of std::tolower?
// ::tolower() comes from cctype where std::tolower comes from <locale>
// I'm uncertain we should really be doing case-insensitive comparison here. -- JLS
      std::transform(ts.begin(), ts.end(), ts.begin(), ::tolower);
      return ns == ts;
    }
  );

  return ptr == end ? -1 : ptr->idx;
}

int lg_get_char_char_transformation_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_CHAR_CHAR_TRANSFORMATIONS,
        LG_CHAR_CHAR_TRANSFORMATIONS +
          sizeof(LG_CHAR_CHAR_TRANSFORMATIONS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

int lg_get_encoding_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_ENCODINGS,
        LG_ENCODINGS +
          sizeof(LG_ENCODINGS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}

int lg_get_byte_byte_transformation_id(const char* const name) {
  return trapWithRetval(
    [name](){
      return find_trans_id(
        LG_BYTE_BYTE_TRANSFORMATIONS,
        LG_BYTE_BYTE_TRANSFORMATIONS +
          sizeof(LG_BYTE_BYTE_TRANSFORMATIONS)/sizeof(LG_TRANS),
        name
      );
    },
    -1
  );
}
