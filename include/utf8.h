#pragma once

#include "caching_encoder.h"
#include "utfbase.h"

class UTF8: public UTFBase {
public:
  virtual uint32 maxByteLength() const { return 4; }

  virtual std::string name() const { return "UTF-8"; }

  virtual uint32 write(int cp, byte buf[]) const;

  using UTFBase::write;

protected:
  virtual void collectRanges(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32& l, uint32 h, uint32 len, uint32 blimit) const;
};

class CachingUTF8: public CachingEncoder<UTF8> {
public:
  CachingUTF8(): CachingEncoder<UTF8>({
    // \p{Any}, .
    {
      {{0, 0xD800}, {0xE000, 0x110000}},
      {
        { {{0x00, 0x80}} },
        { {{0xC2, 0xE0}}, {{0x80, 0xC0}} },
        {   0xE0,         {{0xA0, 0xC0}}, {{0x80, 0xC0}} },
        {   0xED,         {{0x80, 0xA0}}, {{0x80, 0xC0}} },
        { {{0xE1,0xED}, {0xEE,0xF0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
        {   0xF0,         {{0x90, 0xC0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
        {   0xF4,         {{0x80, 0x90}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
        { {{0xF1, 0xF4}}, {{0x80, 0xC0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} }
      }
    }
  }) {}
};
