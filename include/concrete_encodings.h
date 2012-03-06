#pragma once

#include "basic.h"
#include "encoding.h"

class ASCII: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};

};

class UCS16: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};
