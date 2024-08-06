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

#include <memory>

#include "encoders/byteencoder.h"

class OCEEncoder: public ByteEncoder {
public:
  OCEEncoder(std::unique_ptr<Encoder> enc):
    ByteEncoder("OCE", std::move(enc)) {}

  OCEEncoder(const Encoder& enc):
    ByteEncoder("OCE", enc) {}

  OCEEncoder(const OCEEncoder&) = default;

  OCEEncoder& operator=(const OCEEncoder&) = default;

  OCEEncoder(OCEEncoder&&) = default;

  OCEEncoder& operator=(OCEEncoder&&) = default;

  virtual OCEEncoder* clone() const {
    return new OCEEncoder(*this);
  }

  // OCE: bytes -> bytes
  static const byte OCE[], unOCE[];

protected:
  virtual void byteTransform(byte buf[], uint32_t blen) const;
  virtual void byteUntransform(byte buf[], uint32_t blen) const;
};
