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

#include <stdexcept>
#include <string>
#include <sstream>
#include <memory>
#include <limits>
#include <cinttypes>

typedef unsigned char byte;

// typedef unsigned short uint16_t;

// typedef unsigned int uint32_t;
// typedef int int32_t;

// typedef unsigned long long uint64_t;
// typedef long long int64_t;

#define THROW_WITH_OUTPUT(exceptType, expression) \
  std::stringstream buf; \
  buf << __FILE__ << ":" << __LINE__ << ": " << expression; \
  throw exceptType(buf.str())

#define THROW_RUNTIME_ERROR_WITH_OUTPUT(expression) THROW_WITH_OUTPUT(std::runtime_error, expression)

#define THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT(expression) \
  std::stringstream buf; \
  buf << expression; \
  throw std::runtime_error(buf.str())
