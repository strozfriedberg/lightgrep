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

#include "encoders/encoderbase.h"

class CharEncoder: public EncoderBase {
public:
  CharEncoder(std::string&& name, std::unique_ptr<Encoder> enc):
    EncoderBase(),
    Name(std::forward<std::string>(name)),
    BaseEnc(std::move(enc)) {}

  CharEncoder(std::string&& name, const Encoder& enc):
    EncoderBase(),
    Name(std::forward<std::string>(name)),
    BaseEnc(enc.clone()) {}

  CharEncoder(const CharEncoder& other):
    EncoderBase(other),
    Name(other.Name),
    BaseEnc(other.BaseEnc->clone()) {}

  CharEncoder& operator=(const CharEncoder& other) {
    EncoderBase::operator=(other);
    Name = other.Name;
    BaseEnc = std::unique_ptr<Encoder>(other.BaseEnc->clone());
    return *this;
  }

  CharEncoder(CharEncoder&&) = default;

  CharEncoder& operator=(CharEncoder&&) = default;

  virtual std::string name() const;

  virtual uint32_t write(int32_t cp, byte buf[]) const;

  using EncoderBase::write;

  virtual uint32_t write(const byte buf[], int32_t& cp) const;

protected:
  virtual int32_t charTransform(int32_t cp) const = 0;
  virtual int32_t charUntransform(int32_t cp) const = 0;

  std::string Name;
  std::unique_ptr<Encoder> BaseEnc;
};
