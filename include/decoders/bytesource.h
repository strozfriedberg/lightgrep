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
#include "decoders/decoder.h"

class ByteSource: public Decoder {
public:
  ByteSource(const byte* beg, const byte* end):
    Cur(beg), End(end)
  {}

  ByteSource(const ByteSource&) = default;

  ByteSource& operator=(const ByteSource&) = default;

  virtual ByteSource* clone() const {
    return new ByteSource(*this);
  }

  virtual std::string name() const {
    return "";
  }

  virtual std::pair<int32_t,const byte*> next() {
    if (Cur == End) {
      return std::make_pair(END, End);
    }
    else {
      const int32_t n = *Cur;
      return std::make_pair(n, Cur++);
    }
  }

  virtual void reset(const byte* beg, const byte* end) {
    Cur = beg;
    End = end;
  }

  virtual uint32_t maxByteLength() const {
    return 1;
  }

 private:
  const byte* Cur;
  const byte* End;
};
