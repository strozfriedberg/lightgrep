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
#include "byteset.h"
#include "rangeset.h"

#include <vector>

class Encoder {
public:
  virtual ~Encoder() {}

  virtual Encoder* clone() const = 0;

  virtual uint32_t maxByteLength() const = 0;

  virtual std::string name() const = 0;

  virtual const UnicodeSet& validCodePoints() const = 0;

  virtual uint32_t write(int32_t cp, byte buf[]) const = 0;

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const = 0;

  virtual uint32_t write(const byte buf[], int32_t& cp) const = 0;
};
