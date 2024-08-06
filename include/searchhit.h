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

#include "lightgrep/search_hit.h"
#include "basic.h"

class SearchHit: public LG_SearchHit {
public:
  SearchHit() {}
  SearchHit(const LG_SearchHit& s): LG_SearchHit{s.Start, s.End, s.KeywordIndex} {} 

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
