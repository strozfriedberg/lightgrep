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

#include <memory>
#include <sstream>

#include "encoders/byteencoder.h"

uint32_t ByteEncoder::maxByteLength() const {
  return BaseEnc->maxByteLength();
}

std::string ByteEncoder::name() const {
  std::ostringstream ss;
  ss << BaseEnc->name() << '|' << Name;
  return ss.str();
}

const UnicodeSet& ByteEncoder::validCodePoints() const {
  return BaseEnc->validCodePoints();
}

uint32_t ByteEncoder::write(int32_t cp, byte buf[]) const {
  const uint32_t ret = BaseEnc->write(cp, buf);
  byteTransform(buf, ret);
  return ret;
}

uint32_t ByteEncoder::write(const byte[], int32_t& cp) const {
  // FIXME - Joel revisit this, note that first arg is unused
  std::unique_ptr<byte[]> tmp(new byte[maxByteLength()]);
  byteUntransform(tmp.get(), maxByteLength());
  return BaseEnc->write(tmp.get(), cp);
}
