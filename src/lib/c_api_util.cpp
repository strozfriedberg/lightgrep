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

#include <cstring>
#include <new>

#include "c_api_util.h"

namespace {
  // Our own strdup, using new.
  char* dup(const char* s) {
    return std::strcpy(new char[std::strlen(s)+1], s);
  }
}

LG_Error* makeError(
  const char* msg,
  const char* pattern,
  const char* encodingChain,
  const char* source,
  int index
) {
  try {
    return new LG_Error{
      dup(msg), // don't make messageless errors
      pattern ? dup(pattern) : nullptr,
      encodingChain ? dup(encodingChain) : nullptr,
      source ? dup(source) : nullptr,
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
