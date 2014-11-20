/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
