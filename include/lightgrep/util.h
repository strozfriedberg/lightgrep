/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

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

#ifndef LIGHTGREP_C_UTIL_H
#define LIGHTGREP_C_UTIL_H

#include <stddef.h>  // for size_t

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  const char* const name;
  unsigned int idx;
} LG_TRANS;

int lg_get_char_transform_id(const char* const name);

int lg_get_encoding_id(const char* const name);

int lg_get_byte_transform_id(const char* const name);

// Opaque handle
struct DecoderHandle;

typedef struct DecoderHandle* LG_HDECODER;

LG_HDECODER lg_create_decoder();

void lg_destroy_decoder(LG_HDECODER hDec);

typedef struct {
  uint64_t begin,
           end;
} LG_Window;

static const int32_t LG_WINDOW_END = -0x110001;

unsigned int lg_read_window(LG_HDECODER hDec,
                            const char* bufStart,
                            const char* bufEnd,
                            uint64_t dataOffset,
                            const LG_Window* hit,
                            const char* encoding,
                            size_t preContext,
                            size_t postContext,
                            int32_t** characters,
                            size_t** offsets,
                            size_t* clen,
                            LG_Window* decodedHit,
                            LG_Error** err);

unsigned int lg_hit_context(LG_HDECODER hDec,
                            const char* bufStart,
                            const char* bufEnd,
                            uint64_t dataOffset,
                            const LG_Window* inner,
                            const char* encoding,
                            size_t windowSize,
                            uint32_t replacement,
                            const char** utf8,
                            LG_Window* outer,
                            LG_Window* decodedHit,
                            LG_Error** err);

void lg_free_window_characters(int32_t* characters);

void lg_free_window_offsets(size_t* offsets);

void lg_free_hit_context_string(const char* utf8);

#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_UTIL_H */
