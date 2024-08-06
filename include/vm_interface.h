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

#include "basic.h"
#include "fwd_pointers.h"
#include "searchhit.h"

class VmInterface {
public:
  virtual ~VmInterface() {}

  virtual void startsWith(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) = 0;
  virtual uint64_t search(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) = 0;
  virtual uint64_t searchResolve(const byte* const beg, const byte* const end, const uint64_t startOffset, HitCallback hitFn, void* userData) = 0;
  virtual void closeOut(HitCallback hitFn, void* userData) = 0;
  virtual void reset() = 0;

  #ifdef LBT_TRACE_ENABLED
  virtual void setDebugRange(uint64_t beg, uint64_t end) = 0;
  #endif

  static std::shared_ptr<VmInterface> create(ProgramPtr prog);
};
