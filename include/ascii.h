#pragma once

#include "encoderbase.h"

class ASCII: public EncoderBase {
public:
  ASCII(): Valid(0, 0x100) {}

  virtual uint32 maxByteLength() const { return 1; }

  virtual const UnicodeSet& validCodePoints() const { return Valid; };

  virtual uint32 write(int cp, byte buf[]) const;

  virtual void write(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

private:
  const UnicodeSet Valid;
};
