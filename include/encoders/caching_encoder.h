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

#include "decorating_encoder.h"

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
