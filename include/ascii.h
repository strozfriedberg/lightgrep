#pragma once

#include "encoder.h"

class ASCII: public Encoder {
public:
  virtual uint32 maxByteLength() const { return 1; }
  virtual uint32 write(int cp, byte buf[]) const;
  using Encoder::write;
};
