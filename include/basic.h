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

#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <limits>
#include <cinttypes>
#include <cstring>

typedef unsigned char byte;

// typedef unsigned short uint16_t;

// typedef unsigned int uint32_t;
// typedef int int32_t;

// typedef unsigned long long uint64_t;
// typedef long long int64_t;

#define THROW_WITH_OUTPUT(exceptType, expression) \
  std::ostringstream buf; \
  buf << __FILE__ << ":" << __LINE__ << ": " << expression; \
  throw exceptType(buf.str())

#define THROW_RUNTIME_ERROR_WITH_OUTPUT(expression) THROW_WITH_OUTPUT(std::runtime_error, expression)

#define THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT(expression) \
  std::ostringstream buf; \
  buf << expression; \
  throw std::runtime_error(buf.str())

inline char* clone_c_str(const char* s) {
  try {
    return std::strcpy(new char[std::strlen(s) + 1], s);
  }
  catch (std::bad_alloc&) {
    return nullptr;
  }
}
