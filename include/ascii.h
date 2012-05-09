#pragma once

#include "encoder.h"

class ASCII: public Encoder {
public:
  ASCII(): valid(0, 0x100) {}

  virtual uint32 maxByteLength() const { return 1; }

  virtual const UnicodeSet& validCodePoints() const { return valid; };

  virtual uint32 write(int cp, byte buf[]) const;
  using Encoder::write;

private:
  const UnicodeSet valid;
};
