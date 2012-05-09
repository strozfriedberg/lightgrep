#pragma once

#include "automata.h"
#include "basic.h"
#include "byteset.h"
#include "fragment.h"

#include <vector>

class Encoder {
public:
  virtual ~Encoder() {}

  virtual uint32 maxByteLength() const = 0;

  virtual const UnicodeSet& validCodePoints() const = 0;

  virtual uint32 write(int cp, byte buf[]) const = 0;

  virtual void write(const UnicodeSet& uset, NFA& g, Fragment& frag) const;

  virtual void write(std::vector<std::vector<ByteSet>>& v, const UnicodeSet& uset) const;
};
