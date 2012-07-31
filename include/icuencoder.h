#pragma once

#include "caching_encoder.h"
#include "encoderbase.h"

#include <string>

#include <unicode/ucnv.h>

class ICUEncoder: public EncoderBase {
public:
  ICUEncoder(const char* const name);
  ICUEncoder(const std::string& name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;

  virtual std::string name() const;

  virtual uint32 write(int cp, byte buf[]) const;
  using EncoderBase::write;

private:
  void init(const char* const name);

  std::string enc_name;
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
};

class CachingICUEncoder: public CachingEncoder<ICUEncoder> {
public:
  CachingICUEncoder(const char* const name):
    CachingEncoder<ICUEncoder>({}, name) {}

  CachingICUEncoder(const std::string& name):
    CachingEncoder<ICUEncoder>({}, name) {}
};
