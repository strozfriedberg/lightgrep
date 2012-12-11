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
#include "decoders/utf16.h"
#include "decoders/utfdecoderbase.h"

template <bool LE>
class UTF16Decoder: public UTFDecoderBase {
public:
  UTF16Decoder(const Decoder& trans):
    UTFDecoderBase(trans)
  {}

  UTF16Decoder(std::unique_ptr<Decoder> trans):
    UTFDecoderBase(std::move(trans))
  {}

  UTF16Decoder(const UTF16Decoder&) = default;

  UTF16Decoder(UTF16Decoder&&) = default;

  UTF16Decoder& operator=(const UTF16Decoder&) = default; 

  UTF16Decoder& operator=(UTF16Decoder&&) = default;

  virtual UTF16Decoder* clone() const {
    return new UTF16Decoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "UTF-16" << (LE ? "LE" : "BE") << Trans->name();
    return ss.str();
  }

protected:
  virtual size_t decode(const byte* beg, const byte* end, int32_t& cp) {
    return utf16_to_cp<LE>(beg, end, cp);
  }
};

typedef UTF16Decoder<true>  UTF16LEDecoder;
typedef UTF16Decoder<false> UTF16BEDecoder;
