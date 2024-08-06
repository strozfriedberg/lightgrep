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
