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

#include "decoders/decoder.h"

class ASCIIDecoder: public Decoder {
public:
  ASCIIDecoder(const Decoder& trans):
    Trans(trans.clone())
  {}

  ASCIIDecoder(std::unique_ptr<Decoder> trans):
    Trans(std::move(trans))
  {}

  ASCIIDecoder(const ASCIIDecoder& other):
    Trans(other.Trans->clone())
  {}

  ASCIIDecoder(ASCIIDecoder&&) = default;

  ASCIIDecoder& operator=(const ASCIIDecoder& other) {
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    return *this;
  }

  ASCIIDecoder& operator=(ASCIIDecoder&&) = default;

  virtual ASCIIDecoder* clone() const {
    return new ASCIIDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "ASCII" << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    std::pair<int32_t,const byte*> n = Trans->next();
    if (n.first >= 0x80) {
      n.first = -n.first-1;
    }
    return n;
  }

  virtual void reset(const byte* beg, const byte* end) {
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // ASCII is 1:1
    return Trans->maxByteLength();
  }

private:
  std::unique_ptr<Decoder> Trans;
};
