#pragma once

#include "basic.h"
#include "byteset.h"

#include <vector>

class Encoder {
public:
  virtual ~Encoder() {}

  virtual uint32 maxByteLength() const = 0;

  virtual std::string name() const = 0;

  virtual const UnicodeSet& validCodePoints() const = 0;

  virtual uint32 write(int cp, byte buf[]) const = 0;

  virtual void write(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& v) const = 0;
};
