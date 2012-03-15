#pragma once

#include "basic.h"
#include "encoding.h"

#include <unicode/ucnv.h>

class ICUEncoder: public Encoding {
public:
  ICUEncoder(const char* name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;

private:
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
};

class ASCII: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};

class UTF8: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};

class UCS16: public Encoding {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};
