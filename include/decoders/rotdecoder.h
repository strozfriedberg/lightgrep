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
#include <sstream>

#include "decoders/decoder.h"

class RotDecoder: public Decoder {
public:
  RotDecoder(uint32_t rot, const Decoder& trans):
    Rot(rot),
    Trans(trans.clone())
  {}

  RotDecoder(uint32_t rot, std::unique_ptr<Decoder> trans):
    Rot(rot),
    Trans(std::move(trans))
  {}

  RotDecoder(const RotDecoder& other):
    Rot(other.Rot),
    Trans(other.Trans->clone())
  {}

  RotDecoder(RotDecoder&&) = default;

  RotDecoder& operator=(const RotDecoder& other) {
    Rot = other.Rot;
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    return *this;
  }

  RotDecoder& operator=(RotDecoder&&) = default;

  virtual RotDecoder* clone() const {
    return new RotDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "rot(" << Rot << ")|" << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    std::pair<int32_t,const byte*> cp = Trans->next();
    if ('A' <= cp.first && cp.first <= 'Z') {
      cp.first = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(cp.first-'A'+26-Rot) % 26];
    }
    else if ('a' <= cp.first && cp.first <= 'z') {
      cp.first = "abcdefghijklmnopqrstuvwxyz"[(cp.first-'a'+26-Rot) % 26];
    }
    return cp;
  }

  virtual void reset(const byte* beg, const byte* end) {
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // ROT is 1:1
    return Trans->maxByteLength();
  }

private:
  uint32_t Rot;
  std::unique_ptr<Decoder> Trans;
};
