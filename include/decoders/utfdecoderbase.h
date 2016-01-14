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

#include <deque>

#include "decoders/decoder.h"

class UTFDecoderBase: public Decoder {
public:
  UTFDecoderBase(const Decoder& trans):
    Trans(trans.clone())
  {}

  UTFDecoderBase(std::unique_ptr<Decoder> trans):
    Trans(std::move(trans))
  {}

  UTFDecoderBase(const UTFDecoderBase& other):
    Trans(other.Trans->clone()),
    In(other.In)
  {}

  UTFDecoderBase(UTFDecoderBase&&) = default;

  UTFDecoderBase& operator=(const UTFDecoderBase& other) {
    Trans = std::unique_ptr<Decoder>(other.Trans->clone());
    In = other.In;
    return *this;
  }

  UTFDecoderBase& operator=(UTFDecoderBase&&) = default;

  virtual std::pair<int32_t,const byte*> next() {
    // fill queue up to four elements
    while (In.size() < 4) {
      In.push_back(Trans->next());
    }

    // convert the queue to be all bytes, stopping when we hit a non-byte
    byte buf[4];
    size_t i = 0;
    for ( ; i < 4; ++i) {
      if (In[i].first < 0 || 0xFF < In[i].first) {
        break;
      }
      buf[i] = In[i].first;
    }

    std::pair<int32_t,const byte*> cp;

    if (i == 0) {
      // first element is an error, return it unchanged
      cp = In.front();
      In.pop_front();
    }
    else {
      // try to decode the bytes
      size_t consumed = decode(buf, buf+i, cp.first);

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
    }

    return cp;
  }

  virtual void reset(const byte* beg, const byte* end) {
    In.clear();
    Trans->reset(beg, end);
  }

  virtual uint32_t maxByteLength() const {
    // UTF-8, -16, and -32 are all up to 4:1
    return 4*Trans->maxByteLength();
  }

protected:
  virtual size_t decode(const byte* beg, const byte* end, int32_t& cp) = 0;

  std::unique_ptr<Decoder> Trans;

private:
  std::deque<std::pair<int32_t,const byte*>> In;
};
