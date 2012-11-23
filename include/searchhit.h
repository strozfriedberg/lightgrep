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

#include "basic.h"
#include "lightgrep_search_hit.h"

class SearchHit: public LG_SearchHit {
public:
  SearchHit() {}

  // note that this takes the length
  SearchHit(uint64_t start, uint64_t end, uint32_t lbl) {
    Start = start;
    End = end;
    KeywordIndex = lbl;
  }

  uint64_t length() const {
    return End - Start;
  }

  bool operator==(const SearchHit& x) const {
    return x.Start == Start && x.End == End && x.KeywordIndex == KeywordIndex;
  }

  bool operator<(const SearchHit& x) const {
    return Start < x.Start ||
          (Start == x.Start &&
          (End < x.End ||
          (End == x.End && KeywordIndex < x.KeywordIndex)));
  }
};

template <class OutStream>
OutStream& operator<<(OutStream& out, const SearchHit& hit) {
  out << '(' << hit.Start << ", " << hit.End << ", " << hit.KeywordIndex << ')';
  return out;
}

typedef LG_HITCALLBACK_FN HitCallback;
