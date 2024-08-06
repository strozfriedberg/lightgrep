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

#include "encoder.h"

class DecoratingEncoder: public Encoder {
public:
  DecoratingEncoder(std::unique_ptr<Encoder> enc):
    Encoder(),
    BaseEnc(std::move(enc))
  {}

  DecoratingEncoder(const Encoder& enc):
    Encoder(),
    BaseEnc(enc.clone())
  {}

  DecoratingEncoder(const DecoratingEncoder& other):
    Encoder(other),
    BaseEnc(other.BaseEnc->clone())
  {}

  DecoratingEncoder& operator=(const DecoratingEncoder& other) {
    Encoder::operator=(other);
    BaseEnc = std::unique_ptr<Encoder>(other.BaseEnc->clone());
    return *this;
  }

  DecoratingEncoder(DecoratingEncoder&&) = default;

  DecoratingEncoder& operator=(DecoratingEncoder&&) = default;

  virtual DecoratingEncoder* clone() const {
    return new DecoratingEncoder(*this);
  }

  virtual uint32_t maxByteLength() const {
    return BaseEnc->maxByteLength();
  }

  virtual std::string name() const {
    return BaseEnc->name();
  }

  virtual const UnicodeSet& validCodePoints() const {
    return BaseEnc->validCodePoints();
  }

  virtual uint32_t write(int32_t cp, byte buf[]) const {
    return BaseEnc->write(cp, buf);
  }

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& vo) const {
    BaseEnc->write(uset, vo);
  }

  virtual uint32_t write(const byte buf[], int32_t& cp) const {
    return BaseEnc->write(buf, cp);
  }

protected:
  std::unique_ptr<Encoder> BaseEnc;
};
