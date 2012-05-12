#pragma once

#include "encoder.h"

class UTF8: public Encoder {
public:
  UTF8(): valid{{0, 0xD800}, {0xE000, 0x110000}} {}

  virtual uint32 maxByteLength() const { return 4; }

  virtual const UnicodeSet& validCodePoints() const { return valid; };

  virtual uint32 write(int cp, byte buf[]) const;
  void write(std::vector<std::vector<ByteSet>>& va, const UnicodeSet& uset) const;
  using Encoder::write;

private:
  void writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32& l, uint32& h, byte* cur, uint32 len, uint32 blimit) const;

  const UnicodeSet valid;
};
