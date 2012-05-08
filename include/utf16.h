#pragma once

#include "encoder.h"

template <bool LE>
class UTF16Base: public Encoder {
public:
  virtual uint32 maxByteLength() const { return 4; }

  virtual uint32 write(int cp, byte buf[]) const {
    if (cp < 0) {
      // too small
      return 0;
    }
    else if (cp < 0xD800) {
      // direct representation
      buf[LE ? 0 : 1] = cp & 0xFF;
      buf[LE ? 1 : 0] = cp >> 8;
      return 2;
    }
    else if (cp < 0xE000) {
      // UTF-16 surrogates, invalid
      return 0;
    }
    else if (cp < 0x10000) {
      // direct representation
      buf[LE ? 0 : 1] = cp & 0xFF;
      buf[LE ? 1 : 0] = cp >> 8;
      return 2;
    }
    else if (cp < 0x110000) {
      // surrogate pair representation
      const uint16 lead = 0xD800 - (0x10000 >> 10) + (cp >> 10);
      const uint16 trail = 0xDC00 + (cp & 0x3FF);

      buf[LE ? 0 : 1] = lead & 0xFF;
      buf[LE ? 1 : 0] = lead >> 8;
      buf[LE ? 2 : 3] = trail & 0xFF;
      buf[LE ? 3 : 2] = trail >> 8;
      return 4;
    }
    else {
      // too large
      return 0;
    }
  }

  using Encoder::write;
};

class UTF16LE: public UTF16Base<true> {
protected:
  virtual void collectEncodings(std::vector<std::vector<ByteSet>>& va, const UnicodeSet& uset) const;
};

typedef UTF16Base<false> UTF16BE;
