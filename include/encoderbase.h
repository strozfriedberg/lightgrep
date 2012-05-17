#pragma once

#include "encoder.h"

class EncoderBase: public Encoder {
public:
  virtual const UnicodeSet& validCodePoints() const { return Valid; };

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const;

  using Encoder::write;

protected:
  EncoderBase(const UnicodeSet& valid = UnicodeSet()): Valid(valid) {}

  EncoderBase(const EncoderBase& other): Valid(other.Valid) {}

  virtual void collectRanges(const UnicodeSet& user, std::vector<std::vector<ByteSet>>& v) const;

  const UnicodeSet Valid;
};
