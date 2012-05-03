#pragma once

#include "automata.h"
#include "basic.h"
#include "fragment.h"

class Encoder {
public:
  virtual uint32 maxByteLength() const = 0;
  virtual uint32 write(int cp, byte buf[]) const = 0;
//  virtual void write(const UnicodeSet& uset, NFA& g, Fragment& f) const = 0;
  virtual void write(const UnicodeSet&, NFA&, Fragment&) const;

  virtual ~Encoder() {}
};
