#pragma once

#include "automata.h"
#include "basic.h"
#include "encoder.h"
#include "fragment.h"

#include <unicode/ucnv.h>

class ASCII: public Encoder {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};

class UTF8: public Encoder {
public:
  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;
};

template <bool LE>
class UTF16: public Encoder {
public:
  virtual uint32 maxByteLength() const {
    return 4;
  }

  virtual uint32 write(int cp, byte buf[]) const {
    if (cp < 0) {
      // too small
      return 0;
    }
    else if (cp < 0xD800) {
      // direct representation
      buf[LE ? 0 : 1] = cp & 0xFF;
      buf[LE ? 1 : 0] = cp >> 8;
      return 2;
    }
    else if (cp < 0xE000) {
      // UTF-16 surrogates, invalid
      return 0;
    }
    else if (cp < 0x10000) {
      // direct representation
      buf[LE ? 0 : 1] = cp & 0xFF;
      buf[LE ? 1 : 0] = cp >> 8;
      return 2;
    }
    else if (cp < 0x110000) {
      // surrogate pair representation
      const uint16 lead = 0xD800 - (0x10000 >> 10) + (cp >> 10);
      const uint16 trail = 0xDC00 + (cp & 0x3FF);

      buf[LE ? 0 : 1] = lead & 0xFF;
      buf[LE ? 1 : 0] = lead >> 8;
      buf[LE ? 2 : 3] = trail & 0xFF;
      buf[LE ? 3 : 2] = trail >> 8;
      return 4;
    }
    else {
      // too large
      return 0;
    }
  }
};

typedef UTF16<true> UTF16LE;
typedef UTF16<false> UTF16BE;

template <bool LE>
class UTF32: public Encoder {
public:
  virtual uint32 maxByteLength() const {
    return 4;
  }

  virtual uint32 write(int cp, byte buf[]) const {
    if (cp < 0) {
      // too small
      return 0;
    }
    else if (cp < 0xD800) {
      buf[LE ? 0 : 3] =  cp        & 0xFF;
      buf[LE ? 1 : 2] = (cp >>  8) & 0xFF;
      buf[LE ? 2 : 1] = (cp >> 16) & 0xFF;
      buf[LE ? 3 : 0] = (cp >> 24) & 0xFF;
      return 4;
    }
    else if (cp < 0xE000) {
      // UTF-16 surrogates, invalid
      return 0;
    }
    else if (cp < 0x110000) {
      buf[LE ? 0 : 3] =  cp        & 0xFF;
      buf[LE ? 1 : 2] = (cp >>  8) & 0xFF;
      buf[LE ? 2 : 1] = (cp >> 16) & 0xFF;
      buf[LE ? 3 : 0] = (cp >> 24) & 0xFF;
      return 4;
    }
    else {
      // too large
      return 0;
    }
  }
};

typedef UTF32<true> UTF32LE;
typedef UTF32<false> UTF32BE;

class ICUEncoder: public Encoder {
public:
  ICUEncoder(const char* name);
  virtual ~ICUEncoder();

  virtual uint32 maxByteLength() const;
  virtual uint32 write(int cp, byte buf[]) const;

private:
  UConverter* src_conv;
  UConverter* dst_conv;
  UChar* pivot;
  uint32 max_bytes;
};
