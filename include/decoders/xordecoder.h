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

#include <iomanip>
#include <memory>
#include <sstream>

#include "basic.h"
#include "decoders/decoder.h"

class XORDecoder: public Decoder {
public:
  XORDecoder(byte key, const Decoder& trans):
    Key(key),
    Trans(trans.clone())
  {}

  XORDecoder(byte key, std::unique_ptr<Decoder> trans):
    Key(key),
    Trans(std::move(trans))
  {}

  XORDecoder(const XORDecoder& other):
    Key(other.Key),
    Trans(other.Trans->clone())
  {}

  XORDecoder(XORDecoder&&) = default;

  XORDecoder& operator=(const XORDecoder& other) {
    Key = other.Key;
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    return *this;
  }

  XORDecoder& operator=(XORDecoder&&) = default;

  virtual XORDecoder* clone() const {
    return new XORDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "XOR("
       << std::hex << std::setw(2) << std::setfill('0') << std::uppercase
       << ((uint32_t) Key) << ")|" << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    std::pair<int32_t,const byte*> n = Trans->next();
    if (n.first < 0) {
      // do nothing
    }
    else if (n.first < 0x100) {
      n.first ^= Key;
    }
    else {
      n.first = -n.first-1;
    }

    return n;
  }

  virtual void reset(const byte* beg, const byte* end) {
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // XOR is 1:1
    return Trans->maxByteLength();
  }

private:
  byte Key;
  std::unique_ptr<Decoder> Trans;
};
