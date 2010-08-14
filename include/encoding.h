#pragma once

#include "basic.h"

class Encoding {
public:
  virtual uint32 maxByteLength() const = 0;
  virtual uint32 write(int ch, byte buf[]) const = 0;

  virtual ~Encoding() {}
};
