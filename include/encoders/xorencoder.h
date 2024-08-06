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

#include <algorithm>
#include <memory>

#include "boost_lexical_cast.h"

#include "encoders/byteencoder.h"

class XOREncoder: public ByteEncoder {
public:
  XOREncoder(byte key, std::unique_ptr<Encoder> enc):
    ByteEncoder("XOR" + boost::lexical_cast<std::string>((uint32_t) key), std::move(enc)),
    Key(key) {}

  XOREncoder(byte key, const Encoder& enc):
    ByteEncoder("XOR" + boost::lexical_cast<std::string>((uint32_t) key), enc),
    Key(key) {}

  XOREncoder(const XOREncoder&) = default;

  XOREncoder& operator=(const XOREncoder&) = default;

  XOREncoder(XOREncoder&&) = default;

  XOREncoder& operator=(XOREncoder&&) = default;

  virtual XOREncoder* clone() const {
    return new XOREncoder(*this);
  }

protected:
  virtual void byteTransform(byte buf[], uint32_t blen) const {
    const byte key = Key;
    std::transform(buf, buf+blen, buf, [key](byte b){ return b ^ key; });
  }

  virtual void byteUntransform(byte buf[], uint32_t blen) const {
    byteTransform(buf, blen);
  }

private:
  byte Key;
};
