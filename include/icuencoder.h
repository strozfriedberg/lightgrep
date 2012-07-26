#pragma once

#include "caching_encoder.h"
#include "encoderbase.h"

#include <unicode/ucnv.h>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const char* const name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;

  virtual std::string name() const;

  virtual uint32 write(int cp, byte buf[]) const;
  using EncoderBase::write;

private:
  std::string enc_name;
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
};

class CachingICUEncoder: public CachingEncoder<ICUEncoder> {
public:
  CachingICUEncoder(const char* const name): CachingEncoder<ICUEncoder>({}, name) {}
};
