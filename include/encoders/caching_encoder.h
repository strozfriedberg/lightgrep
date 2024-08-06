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

#include "encoders/decorating_encoder.h"

#include <map>

class CachingEncoder: public DecoratingEncoder {
public:
  typedef std::map<UnicodeSet,std::vector<std::vector<ByteSet>>> CacheType;

  CachingEncoder(std::unique_ptr<Encoder> enc):
    DecoratingEncoder(std::move(enc))
  {}

  CachingEncoder(std::unique_ptr<Encoder> enc, CacheType&& cache):
    DecoratingEncoder(std::move(enc)),
    Cache(std::forward<CacheType>(cache))
  {}

  CachingEncoder(const Encoder& enc):
    DecoratingEncoder(enc)
  {}

  CachingEncoder(const Encoder& enc, CacheType&& cache):
    DecoratingEncoder(enc),
    Cache(std::forward<CacheType>(cache))
  {}

  CachingEncoder(const CachingEncoder&) = default;

  CachingEncoder& operator=(const CachingEncoder&) = default;

  CachingEncoder(CachingEncoder&&) = default;

  CachingEncoder& operator=(CachingEncoder&&) = default;

  virtual CachingEncoder* clone() const {
    return new CachingEncoder(*this);
  }

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& vo) const {
    auto i = Cache.find(uset);
    if (i != Cache.end()) {
      vo = i->second;
    }
    else {
      BaseEnc->write(uset, vo);
      Cache.insert(std::make_pair(uset, vo));
    }
  }

private:
  mutable CacheType Cache;
};
