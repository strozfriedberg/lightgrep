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

#ifndef LIGHTGREP_C_SEARCH_HIT_H_
#define LIGHTGREP_C_SEARCH_HIT_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

// Basic Search Hit struct

  typedef struct {
    uint64_t  Start,        // starting offset of the hit
              End;          // one past the hit, i.e., End - Start = Length
    uint32_t  KeywordIndex; // index of keyword that hit
  } LG_SearchHit;

  // function you specify to handle the search hit, e.g.,
  // void gotASearchHit(void* userData, const LG_SearchHit const* hit) {
  //   print("hit at %d, ending %d, on keyword %d",
  //         hit->Start, hit->End, hit->KeywordIndex);
  // }
  typedef void (*LG_HITCALLBACK_FN)(void* userData, const LG_SearchHit* const hit);


#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_SEARCH_HIT_H_ */
