#pragma once

#include "encoder.h"

class UTFBase: public Encoder {
public:
  UTFBase(): valid{{0, 0xD800}, {0xE000, 0x110000}} {}

  virtual const UnicodeSet& validCodePoints() const { return valid; };

  using Encoder::write;

protected:
  virtual void writeRangeBlock(std::vector<ByteSet>& v, uint32& l, uint32 h, uint32 len, uint32 blimit) const = 0;

  virtual void writeRange(std::vector<std::vector<ByteSet>>& va, UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32& l, uint32& h, byte* cur, uint32 len, uint32 blimit) const;

  virtual void skipRange(UnicodeSet::const_iterator& i, const UnicodeSet::const_iterator& iend, uint32& l, uint32& h, uint32 ubound) const; 

private:
  const UnicodeSet valid;
};
