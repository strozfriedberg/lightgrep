#pragma once

#include "encoder.h"

#include <map>

template <class BaseEncoder>
class CachingEncoder: public BaseEncoder {
public:
  CachingEncoder(
    const std::map<UnicodeSet,std::vector<std::vector<ByteSet>>> cache =
          std::map<UnicodeSet,std::vector<std::vector<ByteSet>>>()
  ): Cache(cache) {}

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
  mutable std::map<UnicodeSet,std::vector<std::vector<ByteSet>>> Cache;
};
