#pragma once

#include "encoderbase.h"

class ASCII: public EncoderBase {
public:
  ASCII(): EncoderBase(UnicodeSet{{0, 0x80}}) {}

  virtual uint32 maxByteLength() const { return 1; }

  virtual std::string name() const { return "ASCII"; }

  virtual uint32 write(int cp, byte buf[]) const;

  virtual void write(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;
};
