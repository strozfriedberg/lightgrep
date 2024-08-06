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
#include "decoders/utf32.h"
#include "decoders/utfdecoderbase.h"

template <bool LE>
class UTF32Decoder: public UTFDecoderBase {
public:
  UTF32Decoder(const Decoder& trans):
    UTFDecoderBase(trans)
  {}

  UTF32Decoder(std::unique_ptr<Decoder> trans):
    UTFDecoderBase(std::move(trans))
  {}

  UTF32Decoder(const UTF32Decoder&) = default;

  UTF32Decoder(UTF32Decoder&&) = default;

  UTF32Decoder& operator=(const UTF32Decoder&) = default;

  UTF32Decoder& operator=(UTF32Decoder&&) = default;

  virtual UTF32Decoder* clone() const {
    return new UTF32Decoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "UTF-32" << (LE ? "LE" : "BE") << Trans->name();
    return ss.str();
  }

protected:
  virtual size_t decode(const byte* beg, const byte* end, int32_t& cp) {
    return utf32_to_cp<LE>(beg, end, cp);
  }
};

typedef UTF32Decoder<true>  UTF32LEDecoder;
typedef UTF32Decoder<false> UTF32BEDecoder;
