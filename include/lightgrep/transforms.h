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


#ifndef LIGHTGREP_C_TRANSFORMS_H_
#define LIGHTGREP_C_TRANSFORMS_H_

#include "util.h"

#ifdef __cplusplus
extern "C" {
#endif

static const LG_TRANS LG_CHAR_TRANSFORMS[] = {
  { "identity", 0 }
};

static const char* const LG_CANONICAL_CHAR_TRANSFORMS[] = {
  "identity" // 0
};

// identity
static const int LG_CHAR_TRANSFORM_IDENTITY = 0;

static const LG_TRANS LG_BYTE_TRANSFORMS[] = {
  { "identity", 0 },
  { "OCE",      1 }
};

static const char* const LG_CANONICAL_BYTE_TRANSFORMS[] = {
  "identity", // 0
  "OCE",      // 1
};

// identity
static const int LG_BYTE_TRANSFORM_IDENTITY = 0;

// Outlook Compressible Encryption
static const int LG_BYTE_TRANSFORM_OUTLOOK = 1;

#ifdef __cplusplus
}
#endif

#endif /* LIGHTGREP_C_TRANSFORMS_H_ */
