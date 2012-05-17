#include "utf8.h"

uint32 UTF8::write(int cp, byte buf[]) const {
  if (cp < 0) {
    // too small
    return 0;
  }
  else if (cp < 0x80) {
    // one byte
    buf[0] = (byte) cp;
    return 1;
  }
  else if (cp < 0x800) {
    // two bytes
    buf[0] = 0xC0 | ((cp >> 6) & 0x1F);
    buf[1] = 0x80 | ( cp       & 0x3F);
    return 2;
  }
  else if (cp < 0xD800) {
    // three bytes
    buf[0] = 0xE0 | ((cp >> 12) & 0x0F);
    buf[1] = 0x80 | ((cp >>  6) & 0x3F);
    buf[2] = 0x80 | ( cp        & 0x3F);
    return 3;
  }
  else if (cp < 0xE000) {
    // UTF-16 surrogates, invalid
    return 0;
  }
  else if (cp < 0x10000) {
    // three bytes
    buf[0] = 0xE0 | ((cp >> 12) & 0x0F);
    buf[1] = 0x80 | ((cp >>  6) & 0x3F);
    buf[2] = 0x80 | ( cp        & 0x3F);
    return 3;
  }
  else if (cp < 0x110000) {
    // four bytes
    buf[0] = 0xF0 | ((cp >> 18) & 0x07);
    buf[1] = 0x80 | ((cp >> 12) & 0x3F);
    buf[2] = 0x80 | ((cp >>  6) & 0x3F);
    buf[3] = 0x80 | ( cp        & 0x3F);
    return 4;
  }
  else {
    // too large
    return 0;
  }
}

void UTF8::collectRanges(const UnicodeSet& uset, std::vector<std::vector<ByteSet>>& va) const {
  auto i = uset.begin();
  const auto iend = uset.end();
  if (i == iend) {
    return;
  }

  uint32 l = i->first, h = i->second;
  byte cur[4];

  // handle one-byte encodings
  writeRange(va, i, iend, l, h, cur, 1, 0x80);

  // handle two-byte encodings
  writeRange(va, i, iend, l, h, cur, 2, 0x800);

  // handle low three-byte encodings
  writeRange(va, i, iend, l, h, cur, 3, 0xD800);

  // skip the UTF-16 surrogates
  skipRange(i, iend, l, h, 0xE000);

  // handle high three-byte encodings
  writeRange(va, i, iend, l, h, cur, 3, 0x10000);

  // handle four-byte encodings
  writeRange(va, i, iend, l, h, cur, 4, 0x110000);
}

void UTF8::writeRangeBlock(std::vector<ByteSet>& v, uint32& l, uint32 h, uint32 len, uint32 blimit) const {
  if (len == 1) {
    // the one-byte encodings form a single contiguous block
    const uint32 m = std::min(h, blimit);
    v[len-1].set(l, m, true);
    l = m;
  }
  else if (l < std::min(h, blimit) && l % 64 > 0) {
    const uint32 m = std::min({ h, blimit, (l/64+1)*64 });
    v[len-1].set((l & 0x3F) | 0x80, (((m-1) & 0x3F) | 0x80)+1, true);
    l = m;
  }
}
