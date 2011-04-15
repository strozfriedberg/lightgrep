#pragma once

#include "basic.h"
#include "encoding.h"

class Ascii: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int ch, byte buf[]) const;

  virtual ~Ascii() {}
};

class UCS16: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int ch, byte buf[]) const;

  virtual ~UCS16() {}
};
