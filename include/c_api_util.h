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

#include "basic.h"
#include "lightgrep/api.h"

void fillError(LG_Error** err, const char* msg);

template <typename F>
auto trapWithRetval(F func, decltype(func()) fail, LG_Error** err) -> decltype(func()) {
  try {
    return func();
  }
  catch (const std::exception& e) {
    fillError(err, e.what());
  }
  catch (...) {
    fillError(err, "Unspecified exception");
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
    fillError(err, e.what());
  }
  catch (...) {
    fillError(err, "Unspecified exception");
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
