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
#include "rangeset.h"

#include <string>
#include <memory>

#include <unicode/ucnv.h>

class ICUConverter {
public:
  ICUConverter(const char* encname);

  ICUConverter(const std::string& encname);

  ICUConverter(const ICUConverter& other);

  ICUConverter& operator=(const ICUConverter& other);

  ICUConverter(ICUConverter&&) = default;

  ICUConverter& operator=(ICUConverter&&) = default;

  size_t maxByteLength() const { return max_bytes; }

  std::string name() const { return Name; }

  UnicodeSet validCodePoints() const;

  size_t bytes_to_cp(const byte* beg, const byte* end, int32_t& cp) const;

  size_t cp_to_bytes(int32_t cp, byte buf[]) const;

private:
  void init();

  std::string Name;

  size_t max_bytes;

  std::unique_ptr<UConverter,void(*)(UConverter*)> bytes_conv, cp_conv;
  std::unique_ptr<UChar[]> bytes_pivot, cp_pivot;
};
