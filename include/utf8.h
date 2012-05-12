#pragma once

#include "utfbase.h"

class UTF8: public UTFBase {
public:
  virtual uint32 maxByteLength() const { return 4; }

  virtual uint32 write(int cp, byte buf[]) const;
  void write(std::vector<std::vector<ByteSet>>& va, const UnicodeSet& uset) const;
  using UTFBase::write;

protected:
  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32& l, uint32 h, uint32 len, uint32 blimit) const;
};
