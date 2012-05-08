#pragma once

#include "encoder.h"

#include <unicode/ucnv.h>

class ICUEncoder: public Encoder {
public:
  ICUEncoder(const char* name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
  using Encoder::write;

private:
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
};
