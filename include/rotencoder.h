/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

#include "basic.h"
#include "charencoder.h"

#include <boost/lexical_cast.hpp>

class ROTEncoder: public CharEncoder {
public:
  ROTEncoder(uint32_t rot, std::unique_ptr<Encoder> enc):
    CharEncoder("rot" + boost::lexical_cast<std::string>(rot), std::move(enc)),
    Rot(rot) {}

  ROTEncoder(uint32_t rot, const Encoder& enc):
    CharEncoder("rot" + boost::lexical_cast<std::string>(rot), enc),
    Rot(rot) {}

  ROTEncoder(const ROTEncoder&) = default;

  ROTEncoder& operator=(const ROTEncoder&) = default;

  ROTEncoder(ROTEncoder&&) = default;

  ROTEncoder& operator=(ROTEncoder&&) = default;

  virtual ROTEncoder* clone() const {
    return new ROTEncoder(*this);
  }

  virtual uint32_t maxByteLength() const { return BaseEnc->maxByteLength(); }

  virtual const UnicodeSet& validCodePoints() const {
    return BaseEnc->validCodePoints();
  }

protected:
  virtual int charTransform(int cp) const {
    return
      ('A' <= cp && cp <= 'Z') ?
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[(cp-'A'+Rot) % 26] :
      ('a' <= cp && cp <= 'z') ?
        "abcdefghijklmnopqrstuvwxyz"[(cp-'a'+Rot) % 26] :
      cp;
  }

private:
  uint32_t Rot;
};
