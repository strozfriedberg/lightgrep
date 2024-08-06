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

#include "basic.h"
#include "encoders/charencoder.h"

#include "boost_lexical_cast.h"

class RotEncoder: public CharEncoder {
public:
  RotEncoder(uint32_t rot, std::unique_ptr<Encoder> enc):
    CharEncoder("rot" + boost::lexical_cast<std::string>(rot), std::move(enc)),
    Rot(rot) {}

  RotEncoder(uint32_t rot, const Encoder& enc):
    CharEncoder("rot" + boost::lexical_cast<std::string>(rot), enc),
    Rot(rot) {}

  RotEncoder(const RotEncoder&) = default;

  RotEncoder& operator=(const RotEncoder&) = default;

  RotEncoder(RotEncoder&&) = default;

  RotEncoder& operator=(RotEncoder&&) = default;

  virtual RotEncoder* clone() const {
    return new RotEncoder(*this);
  }

  virtual uint32_t maxByteLength() const { return BaseEnc->maxByteLength(); }

  virtual const UnicodeSet& validCodePoints() const {
    return BaseEnc->validCodePoints();
  }

protected:
  virtual int32_t charTransform(int32_t cp) const {
    return
      ('A' <= cp && cp <= 'Z') ?
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(cp-'A'+Rot) % 26] :
      ('a' <= cp && cp <= 'z') ?
        "abcdefghijklmnopqrstuvwxyz"[(cp-'a'+Rot) % 26] :
      cp;
  }

  virtual int32_t charUntransform(int32_t cp) const {
    return
      ('A' <= cp && cp <= 'Z') ?
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(cp-'A'+26-Rot) % 26] :
      ('a' <= cp && cp <= 'z') ?
        "abcdefghijklmnopqrstuvwxyz"[(cp-'a'+26-Rot) % 26] :
      cp;
  }

private:
  uint32_t Rot;
};
