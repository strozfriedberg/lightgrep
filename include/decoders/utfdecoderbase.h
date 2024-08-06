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
