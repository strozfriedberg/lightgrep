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
