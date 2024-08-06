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
#include <string>

#include "encoders/encoderbase.h"

// FIXME: Inheriting from EncoderBase means we have a Valid member which
// we don't use. We could avoid this by moving the Valid member into a
// subclass of EncoderBase (what to call it?).
class ByteEncoder: public EncoderBase {
public:
  ByteEncoder(std::string&& name, std::unique_ptr<Encoder> enc):
    EncoderBase(),
    Name(std::forward<std::string>(name)),
    BaseEnc(std::move(enc)) {}

  ByteEncoder(std::string&& name, const Encoder& enc):
    EncoderBase(),
    Name(std::forward<std::string>(name)),
    BaseEnc(enc.clone()) {}

  ByteEncoder(const ByteEncoder& other):
    EncoderBase(other),
    Name(other.Name),
    BaseEnc(other.BaseEnc->clone()) {}

  ByteEncoder& operator=(const ByteEncoder& other) {
    EncoderBase::operator=(other);
    Name = other.Name;
    BaseEnc = std::unique_ptr<Encoder>(other.BaseEnc->clone());
    return *this;
  }

  ByteEncoder(ByteEncoder&&) = default;

  ByteEncoder& operator=(ByteEncoder&&) = default;

  virtual uint32_t maxByteLength() const;

  virtual std::string name() const;

  virtual const UnicodeSet& validCodePoints() const;

  virtual uint32_t write(int32_t cp, byte buf[]) const;

  using EncoderBase::write;

  virtual uint32_t write(const byte buf[], int32_t& cp) const;

protected:
  virtual void byteTransform(byte buf[], uint32_t blen) const = 0;
  virtual void byteUntransform(byte buf[], uint32_t blen) const = 0;

  std::string Name;
  std::unique_ptr<Encoder> BaseEnc;
};
