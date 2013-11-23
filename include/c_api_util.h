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

#pragma once

#include "lightgrep/api.h"
#include "basic.h"

LG_Error* makeError(
  const char* msg,
  const char* pattern = nullptr,
  const char* encodingChain = nullptr,
  const char* source = nullptr,
  int index = -1
);

template <typename F>
auto trapWithRetval(F func, decltype(func()) fail, LG_Error** err) -> decltype(func()) {
  try {
    return func();
  }
  catch (const std::exception& e) {
    if (err) {
      *err = makeError(e.what());
    }
  }
  catch (...) {
    if (err) {
      *err = makeError("Unspecified exception");
    }
  }

  return fail;
}

template <typename F>
auto trapWithRetval(F func, decltype(func()) fail) -> decltype(func()) {
  try {
    return func();
  }
  catch (...) {
    return fail;
  }
}

template <typename R, typename F>
R trapWithVals(F func, R succ, R fail, LG_Error** err) {
  try {
    func();
    return succ;
  }
  catch (const std::exception& e) {
    if (err) {
      *err = makeError(e.what());
    }
  }
  catch (...) {
    if (err) {
      *err = makeError("Unspecified exception");
    }
  }

  return fail;
}

template <typename R, typename F>
R trapWithVals(F func, R succ, R fail) {
  try {
    func();
    return succ;
  }
  catch (...) {
    return fail;
  }
}
