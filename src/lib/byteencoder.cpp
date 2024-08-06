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
