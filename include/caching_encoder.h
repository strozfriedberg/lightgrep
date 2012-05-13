#pragma once

#include "encoder.h"

#include <map>

template <class BaseEncoder>
class CachingEncoder: public BaseEncoder {
public:
  template <typename... BaseArgs>
  CachingEncoder(
    const std::map<UnicodeSet,std::vector<std::vector<ByteSet>>> cache,
    BaseArgs... args
  ): BaseEncoder(args...), Cache(cache) {}

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
