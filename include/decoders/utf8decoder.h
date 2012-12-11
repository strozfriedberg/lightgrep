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

#include <deque>

#include "decoders/decoder.h"
#include "decoders/utf8.h"
#include "decoders/utfdecoderbase.h"

class UTF8Decoder: public UTFDecoderBase {
public:
  UTF8Decoder(const Decoder& trans):
    UTFDecoderBase(trans)
  {}

  UTF8Decoder(std::unique_ptr<Decoder> trans):
    UTFDecoderBase(std::move(trans))
  {}

  UTF8Decoder(const UTF8Decoder&) = default;

  UTF8Decoder(UTF8Decoder&&) = default;

  UTF8Decoder& operator=(const UTF8Decoder&) = default;

  UTF8Decoder& operator=(UTF8Decoder&&) = default;

  virtual UTF8Decoder* clone() const {
    return new UTF8Decoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "UTF-8" << Trans->name();
    return ss.str();
  }

protected:
  virtual size_t decode(const byte* beg, const byte* end, int32_t& cp) {
    return utf8_to_cp(beg, end, cp);
  }
};
