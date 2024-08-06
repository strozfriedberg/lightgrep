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

#include <bitset>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <utility>
#include <boost/smart_ptr.hpp>

typedef unsigned char byte;

typedef unsigned int uint32;
typedef int int32;

typedef unsigned long long uint64;
typedef long long int64;

typedef std::bitset<256> ByteSet;

#define THROW_WITH_OUTPUT(exceptType, expression) \
  std::ostringstream buf; \
  buf << __FILE__ << ":" << __LINE__ << ": " << expression; \
  throw exceptType(buf.str())

#define THROW_RUNTIME_ERROR_WITH_OUTPUT(expression) THROW_WITH_OUTPUT(std::runtime_error, expression)
