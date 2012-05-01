#pragma once

#include "basic.h"

class Encoder {
public:
  virtual uint32 maxByteLength() const = 0;
  virtual uint32 write(int cp, byte buf[]) const = 0;

  virtual ~Encoder() {}
};
