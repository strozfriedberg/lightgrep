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

#include <cstring>
#include <new>

#include "c_api_util.h"

LG_Error* makeError(
  const char* msg,
  const char* pattern,
  const char* encodingChain,
  const char* source,
  int index
) {
  try {
    return new LG_Error{
      clone_c_str(msg), // don't make messageless errors
      pattern ? clone_c_str(pattern) : nullptr,
      encodingChain ? clone_c_str(encodingChain) : nullptr,
      source ? clone_c_str(source) : nullptr,
      index,
      nullptr
    };
  }
  catch (const std::bad_alloc&) {
    // Insufficient memory to copy one of the strings. Everything is hosed.
  }
  catch (...) {
    // Should be impossible.
  }

  return nullptr;
}
