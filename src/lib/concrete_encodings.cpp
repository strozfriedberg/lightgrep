#include "concrete_encodings.h"
#include "encodings.h"

uint32 ASCII::maxByteLength() const {
  return 1;
}

uint32 ASCII::write(int cp, byte buf[]) const {
  if (cp < 256) {
    buf[0] = cp;
    return 1;
  }
  return 0;
}

uint32 UTF8::maxByteLength() const {
  return 4;
}

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

uint32 UCS16::maxByteLength() const {
  return 2;
}

uint32 UCS16::write(int cp, byte buf[]) const {
  if (-1 < cp && cp < 65536) {
    *(unsigned short*)buf = cp;
    return 2;
  }
  return 0;
}

/*
EncodingsCodeMap getEncodingsMap() {
  EncodingsCodeMap map;
  const uint32 num = sizeof(LG_SUPPORTED_ENCODINGS) / sizeof(const char*);
  for (uint32 i = 0; i < num; ++i) {
    map.insert(std::make_pair(LG_SUPPORTED_ENCODINGS[i], i));
  }
  map.insert(std::make_pair("ANSI_X3.4-1968", LG_ENC_ASCII));
  map.insert(std::make_pair("ASCII", LG_ENC_ASCII));
  return map;
}
*/
