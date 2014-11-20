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

#include <algorithm>
#include <deque>

#include "icuconverter.h"
#include "decoders/decoder.h"

class ICUDecoder: public Decoder {
public:
  ICUDecoder(const char* name, const Decoder& trans):
    Trans(trans.clone()),
    Conv(name)
  {}

  ICUDecoder(const char* name, std::unique_ptr<Decoder> trans):
    Trans(std::move(trans)),
    Conv(name)
  {}

  ICUDecoder(const ICUDecoder& other):
    Trans(other.Trans->clone()),
    In(other.In),
    Conv(other.Conv)
  {}

  ICUDecoder(ICUDecoder&&) = default;

  ICUDecoder& operator=(const ICUDecoder& other) {
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    In = other.In;
    Conv = other.Conv;
    return *this;
  }

  ICUDecoder& operator=(ICUDecoder&&) = default;

  virtual ICUDecoder* clone() const {
    return new ICUDecoder(*this);
  }

  virtual std::string name() const {
    std::ostringstream ss;
    ss << Conv.name() << Trans->name();
    return ss.str();
  }

  virtual std::pair<int32_t,const byte*> next() {
    // find the first invalid element in the queue
    auto i = std::find_if(
      In.cbegin(), In.cend(),
      [](const std::pair<int32_t,const byte*>& v){
        return v.first < 0 || 0xFF < v.first;
      }
    );

    if (i == In.cend()) {
      // no invalid elements yet, pump until we hit one
      std::pair<int32_t,const byte*> n;
      do {
        n = Trans->next();
        In.push_back(n);
      } while (0 <= n.first && n.first < 0x100);
      i = In.cend() - 1;
    }

    if (i == In.cbegin()) {
      // first element is invalid, return it
      const std::pair<int32_t,const byte*> n = *i;
      In.pop_front();
      return n;
    }

    // dump the leading sequence of valid elements into our byte buffer
    Buf.clear();
    std::transform(
      In.cbegin(), i, std::back_inserter(Buf),
      [](const std::pair<int32_t,const byte*>& v){ return v.first; }
    );

    std::pair<int32_t,const byte*> cp;

    // try to decode the bytes
    size_t consumed =
      Conv.bytes_to_cp(Buf.data(), Buf.data() + Buf.size(), cp.first);

    if (consumed == 0) {
      // no valid bytes consumed, return the first raw byte as an error
      cp = In.front();
      In.pop_front();
      cp.first = -cp.first-1;
    }
    else {
      // otherwise, get the offset from the first byte
      cp.second = In.front().second;

      // then drop the consumed bytes from the queue
      do {
        In.pop_front();
      } while (--consumed);
    }

    return cp;
  }

  virtual void reset(const byte* beg, const byte* end) {
    In.clear();
    Buf.clear();
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // gearing is the product of what we consume and what our input consumes
    return Conv.maxByteLength() * Trans->maxByteLength();
  }

private:
  std::unique_ptr<Decoder> Trans;
  std::deque<std::pair<int32_t,const byte*>> In;
  std::vector<byte> Buf;
  ICUConverter Conv;
};
