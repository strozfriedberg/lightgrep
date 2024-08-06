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

#include <deque>

#include "decoders/decoder.h"
#include "decoders/utf8.h"
#include "decoders/utfdecoderbase.h"

class UTF8Decoder: public UTFDecoderBase {
public:
  UTF8Decoder(const Decoder& trans):
    UTFDecoderBase(trans)
  {}

  UTF8Decoder(std::unique_ptr<Decoder> trans):
    UTFDecoderBase(std::move(trans))
  {}

  UTF8Decoder(const UTF8Decoder&) = default;

  UTF8Decoder(UTF8Decoder&&) = default;

  UTF8Decoder& operator=(const UTF8Decoder&) = default;

  UTF8Decoder& operator=(UTF8Decoder&&) = default;

  virtual UTF8Decoder* clone() const {
    return new UTF8Decoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "UTF-8" << Trans->name();
    return ss.str();
  }

protected:
  virtual size_t decode(const byte* beg, const byte* end, int32_t& cp) {
    return utf8_to_cp(beg, end, cp);
  }
};
