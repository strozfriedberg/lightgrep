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

#include <algorithm>
#include <sstream>
#include <type_traits>

class OCEEncoderBase {
public:
  // OCE: bytes -> bytes
  static const byte OCE[];
};

template <class BaseEncoder>
class OCEEncoder: public OCEEncoderBase, public BaseEncoder {
public:
  template <typename... BaseArgs>
  OCEEncoder(BaseArgs... args): BaseEncoder(args...) {
    // ensure that OCEEncoder is an Encoder
    static_assert(
      std::is_base_of<Encoder,OCEEncoder<BaseEncoder>>::value,
      "OCEEncoder is not an Encoder!"
    );
  }
  
  virtual std::string name() const {
    std::ostringstream ss;
    ss << "OCE(" << BaseEncoder::name() << ')';
    return ss.str();
  }

  virtual uint32 write(int cp, byte buf[]) const {
    const uint32 ret = BaseEncoder::write(cp, buf);
    std::transform(buf, buf+ret, buf, [](byte b){ return OCE[b]; });
    return ret;
  }

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const {
    std::vector<std::vector<ByteSet>> u;
    BaseEncoder::write(uset, u);

    for (const std::vector<ByteSet>& e : u) {
      v.emplace_back();

      for (const ByteSet& bs : e) {
        ByteSet oce_bs;
        for (uint32 i = 0; i < 256; ++i) {
          if (bs.test(i)) {
            oce_bs.set(OCE[i]);
          }
        }
        v.back().push_back(oce_bs);
      }
    }
  }
};
