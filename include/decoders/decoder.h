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

#include <string>
#include <utility>

class Decoder {
public:
  virtual ~Decoder() {}

  virtual Decoder* clone() const = 0;

  virtual std::string name() const = 0;

  virtual std::pair<int32_t,const byte*> next() = 0;

  virtual void reset(const byte* beg, const byte* end) = 0;

  virtual uint32_t maxByteLength() const = 0;

  static const int32_t END;
};
