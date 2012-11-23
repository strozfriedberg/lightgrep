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

#include "encoder.h"

#include <map>
#include <type_traits>

template <class BaseEncoder>
class CachingEncoder: public BaseEncoder {
public:
  typedef std::map<UnicodeSet,std::vector<std::vector<ByteSet>>> CacheType;

  template <typename... BaseArgs>
  CachingEncoder(CacheType&& cache, BaseArgs&&... args):
    BaseEncoder(std::forward<BaseArgs>(args)...),
    Cache(std::forward<CacheType>(cache))
  {
    // ensure that CachingEncoder is an Encoder
    static_assert(
      std::is_base_of<Encoder,CachingEncoder<BaseEncoder>>::value,
      "CachingEncoder is not an Encoder!"
    );
  }

  CachingEncoder(const CachingEncoder<BaseEncoder>&) = default;

  CachingEncoder(CachingEncoder<BaseEncoder>&&) = default;

  CachingEncoder<BaseEncoder>& operator=(const CachingEncoder<BaseEncoder>&) = default;

  CachingEncoder<BaseEncoder>& operator=(CachingEncoder<BaseEncoder>&&) = default;

  virtual CachingEncoder<BaseEncoder>* clone() const {
    return new CachingEncoder<BaseEncoder>(*this);
  }

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& vo) const {
    auto i = Cache.find(uset);
    if (i != Cache.end()) {
      vo = i->second;
    }
    else {
      BaseEncoder::write(uset, vo);
      Cache.insert(std::make_pair(uset, vo));
    }
  }

  using BaseEncoder::write;

private:
  mutable CacheType Cache;
};
