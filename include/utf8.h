#pragma once

#include "encoder.h"

class UTF8: public Encoder {
public:
  UTF8(): valid{{0, 0xD800}, {0xE000, 0x110000}} {}

  virtual uint32 maxByteLength() const { return 4; }

  virtual const UnicodeSet& validCodePoints() const { return valid; };

  virtual uint32 write(int cp, byte buf[]) const;
  using Encoder::write;

private:
  const UnicodeSet valid;
};
