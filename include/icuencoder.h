#pragma once

#include "encoderbase.h"

#include <unicode/ucnv.h>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const char* name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;

  virtual uint32 write(int cp, byte buf[]) const;
  using EncoderBase::write;

private:
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
  UnicodeSet valid;
};
