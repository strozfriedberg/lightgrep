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
#include "decoders/utf32.h"
#include "decoders/utfdecoderbase.h"

template <bool LE>
class UTF32Decoder: public UTFDecoderBase {
public:
  UTF32Decoder(const Decoder& trans):
    UTFDecoderBase(trans)
  {}

  UTF32Decoder(std::unique_ptr<Decoder> trans):
    UTFDecoderBase(std::move(trans))
  {}

  UTF32Decoder(const UTF32Decoder&) = default;

  UTF32Decoder(UTF32Decoder&&) = default;

  UTF32Decoder& operator=(const UTF32Decoder&) = default;

  UTF32Decoder& operator=(UTF32Decoder&&) = default;

  virtual UTF32Decoder* clone() const {
    return new UTF32Decoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << "UTF-32" << (LE ? "LE" : "BE") << Trans->name();
    return ss.str();
  }

protected:
  virtual size_t decode(const byte* beg, const byte* end, int32_t& cp) {
    return utf32_to_cp<LE>(beg, end, cp);
  }
};

typedef UTF32Decoder<true>  UTF32LEDecoder;
typedef UTF32Decoder<false> UTF32BEDecoder;
