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

#ifndef LIGHTGREP_C_TRANSFORMS_H_
#define LIGHTGREP_C_TRANSFORMS_H_

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

static const LG_TRANS LG_CHAR_CHAR_TRANSFORMATIONS[] = {
  { "identity", 0 }
};

static const char* const LG_CANONICAL_CHAR_CHAR_TRANSFORMATIONS[] = {
  "identity" // 0
};

// identity
static const int LG_CHAR_CHAR_IDENTITY = 0;


static const LG_TRANS LG_BYTE_BYTE_TRANSFORMATIONS[] = {
  { "identity", 0 },
  { "OCE",      1 }
};

static const char* const LG_CANONICAL_BYTE_BYTE_TRANSFORMATIONS[] = {
  "identity", // 0
  "OCE",      // 1
};

// identity
static const int LG_BYTE_BYTE_IDENTITY = 0;

// OCE
static const int LG_BYTE_BYTE_OCE = 1;


#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_TRANSFORMS_H_ */
