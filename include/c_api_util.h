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
auto trapWithRetval(F&& func, decltype(func()) fail, LG_Error** err) -> decltype(func()) {
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
auto trapWithRetval(F&& func, decltype(func()) fail) -> decltype(func()) {
  try {
    return func();
  }
  catch (...) {
    return fail;
  }
}

template <typename R, typename F>
R trapWithVals(F&& func, R succ, R fail, LG_Error** err) {
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
R trapWithVals(F&& func, R succ, R fail) {
  try {
    func();
    return succ;
  }
  catch (...) {
    return fail;
  }
}
